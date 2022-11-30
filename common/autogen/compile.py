"""
filename: compile.py
author: Shalev Mintz
contact: shalev@lulav.space
description: compiles Simulink generated .h (C++ header) files into their 
             corresponding .fpp (F-Prime), .proto (ProtoBuffers version 2 and 3),
             and .msg (ROS2) files. 

             command line usage:
                python3 compile.py <json input file name>
"""

#------------------------- general global definitions -------------------------

import json
import sys
import re
from pathlib import Path

# list of tupples of the form (<struct name>, <type-value list>, <is enum>)
parsed_data = []

struct_set = set(())

header_lines = []

#------------------------------- parse headers --------------------------------

def find_type(line):
    """
        Return the variable type from a decleration line,
        taking into account the possibility of one type being 
        a substring of another, e.g. int and unsigned int.
    """
    candidates = []
    for tp in g_input["type_dict"]:
        if tp in line:
           candidates.append(tp)
    return max(candidates, key=len) if candidates else ""


def parse_struct_field(line, type_val_list):
    tp = find_type(line)
    type_val = []

    # integral type
    if tp:
        type_val.append(tp)
        type_val.append(line.strip()[line.find(tp)+len(tp)-1:].split(';', 1)[0])
    
    # struct or enum
    else:
        type_val = line.strip().split(' ')[0:2]
        type_val[1] = type_val[1].split(';', 1)[0]

    type_val_list.append(type_val)
    return type_val[0]


def parse_enum_field(line, type_val_list):
    if "=" in line:
        type_val = line.strip().split('=', 1)
        type_val[0] = type_val[0].strip()
        type_val[1] = type_val[1].strip().split(',', 1)[0]
    elif "," in line:
        type_val = line.strip().split(',', 1)
        type_val[1] = ""
    else: # last value - no comma
        type_val = []
        type_val.append(line.strip())
        type_val.append("") 

    type_val_list.append(type_val)


def is_whole_word(search_string, input_string):
  raw_search_string = r"\b" + search_string + r"\b"

  match_output = re.search(raw_search_string, input_string)

  return False if match_output is None else True


def parse_struct(struct_name):
    """
        Parses a cpp struct recursively.
    """
    if(struct_name in struct_set):
        # avoid duplicate struct definitions
        return

    struct_set.add(struct_name)
    in_struct = False
    in_enum = False
    type_val_list = []
    full_struct_name = g_input["struct_decl"] + struct_name
    full_enum_name = g_input["enum_decl"] + struct_name

    for line in header_lines: 
        if not in_struct and full_struct_name in line:
            # struct names might be substrings of other struct names.
            if is_whole_word(full_struct_name, line):
                in_struct = True
            continue
        elif in_struct:
            if g_input["decl_end"] in line:
                parsed_data.append((struct_name, type_val_list, False))
                return
            elif "{" in line:
                continue
            elif not line or line.isspace():
                continue
            elif line.strip().startswith("//"):
                continue

            type_name = parse_struct_field(line, type_val_list)
            
            if not type_name in g_input["type_dict"]:
                # recursive call
                parse_struct(type_name)
                
        elif not in_enum and full_enum_name in line:
            in_enum = True
            continue
        elif in_enum:
            if g_input["decl_end"] in line:
                parsed_data.append((struct_name, type_val_list, True))
                return
            if ":" in line or "{" in line:
                continue

            parse_enum_field(line, type_val_list)

#----------------------------------- proto ------------------------------------

def get_file_name(format):
    return "{}.{}".format(g_input["base_out_name"], format)


def write_proto_boilerplate(version, proto_file):
    boilerplate = """
syntax = "proto{}";

// uncomment and link with protobuf-lite *instead* of protobuf 
// for optimized performance with less features, e.g. no DebugString.
// option optimize_for = LITE_RUNTIME;

// namespace of generated code
package {};

""".format(str(version), g_input["schemas"]["proto"]["package"])
    proto_file.write(boilerplate)


def get_multiplicity(val, with_brackets):
    if not "[" in val:
        return val, ""
    else:
        if with_brackets:
            left = val.find("[")
            right = val.find("]")
            return val[0:left], val[left:right+1]
        else:
            left = val.find("[") + 1
            right = val.find("]")
            return val[0:left-1], val[left:right]


def write_message_line(version, type_val, id, proto_file):
    type_name = ""
    prefix = ""

    if type_val[0] in g_input["type_dict"]:
        type_name = g_input["type_dict"][type_val[0]]["proto"]
    else:
        type_name = type_val[0]

    field_name, mult = get_multiplicity(type_val[1], False)

    if not mult:
        if version == 2:
            prefix = "  optional "
        else: # version 3
            prefix = "  "
    else:
        prefix = "  repeated "

    proto_file.write(prefix + 
                     type_name + " " + field_name +
                     " = {};\n".format(str(id)))


def write_proto(version):
    dir = proto2_output_dir if version == 2 else proto3_output_dir
    name = get_file_name("proto")

    with open('{}{}'.format(dir, name), 'w') as proto_file:  
        write_proto_boilerplate(version, proto_file)

        for tpl in parsed_data:
            id = 1
            if not tpl[2]: # message
                proto_file.write("message " + tpl[0] + " {\n")
                for field in tpl[1]:
                    write_message_line(version, field, id, proto_file)
                    id += 1
                proto_file.write("}\n\n")

            else: # enum
                proto_file.write("enum " + tpl[0] + " {\n")
                val = tpl[1][0][1] # base value, default
                id = int(val) if val != "" else 0
                for field in tpl[1]:
                    proto_file.write("  " + field[0] + " = {};\n".format(str(id)))
                    id += 1
                proto_file.write("}\n\n")

#------------------------------------- fpp ------------------------------------

def write_fpp_boilerplate(fpp_file):
    fpp_file.write("module {} {{\n\n".format(g_input["schemas"]["fpp"]["module"]))


def write_fpp_struct_line(type_val, fpp_file):
    type_name = ""
    if type_val[0] in g_input["type_dict"]:
        type_name = g_input["type_dict"][type_val[0]]["fpp"]
    else:
        type_name = type_val[0]

    field_name, array_size = get_multiplicity(type_val[1], True)

    fpp_file.write("    " + field_name + " : " + array_size + " " + type_name + "\n")


def write_fpp_enum_line(type_val, fpp_file, idx):
    annotation = ""
    if(idx > 0):
        annotation = ""
    else:
        annotation = "                @< Default value"

    # Note: We ignore the parsed enum default integer values (namely type_val[1]), 
    #       and assume the first is the base value to which the rest are incremented.
    #       This works because the standard simulink output behaviour is
    #       to only explicitly assign an integer value (0) to the first enum value.
    fpp_file.write("    " + type_val[0] + " = " + str(idx) + annotation + "\n")


def write_fpp():
    with open('{}{}'.format(fpp_output_dir, get_file_name("fpp")), 'w') as fpp_file:
        write_fpp_boilerplate(fpp_file)

        for tpl in parsed_data:
            if not tpl[2]: # struct
                fpp_file.write("  struct " + tpl[0] + " {\n")
                for field in tpl[1]:
                    write_fpp_struct_line(field, fpp_file)
                fpp_file.write("  }\n\n")
            
            else: # enum
                fpp_file.write("  enum " + tpl[0] + " : I32{\n")
                first = tpl[1][0]
                dflt = first[0] # first value is default
                idx = int(first[1])
                for field in tpl[1]:
                    write_fpp_enum_line(field, fpp_file, idx)
                    idx += 1
                fpp_file.write("  } default " + dflt + "\n\n")
        
        fpp_file.write("}") # module scope

#-------------------------------------- msg -----------------------------------

def to_camel_case(str):
    parsed = str.split('_')
    parsed = [word.lower() for word in parsed]
    parsed = [word.replace(word[0], word[0].upper()) for word in parsed]
    return "".join(parsed)


def write_msg_struct_line(type_val, msg_file):
    type_name = ""
    if type_val[0] in g_input["type_dict"]:
        type_name = g_input["type_dict"][type_val[0]]["msg"]
    else:
        type_name = g_input["schemas"]["msg"]["base_dir"] + to_camel_case(type_val[0])

    field_name, array_size = get_multiplicity(type_val[1], True)

    msg_file.write(type_name + array_size + " " + field_name.lower() + "\n")


def write_ros2_msg():
    for tpl in parsed_data:
        if not tpl[2]: # struct
            msg_file_name = to_camel_case(tpl[0]) + ".msg"
            with open('{}{}'.format(msg_output_dir, msg_file_name), 'w') as msg_file: 
                for field in tpl[1]:
                    write_msg_struct_line(field, msg_file)
        
        else: # enum - just a single generic field, since ROS2 doesn't support enums.
            msg_file_name = tpl[0] + ".msg"
            with open('{}{}'.format(msg_output_dir, msg_file_name), 'w') as msg_file:
                msg_file.write(g_input["schemas"]["msg"]["enum_type"] + " e\n")

#------------------------------- generate schemas -----------------------------

def generate_protobuf2():
    if g_input["output_dict"]["proto2"]:
        Path(proto2_output_dir).mkdir(parents=True, exist_ok=True)
        write_proto(2)
        print("proto2 done.")
    else:
        print("proto2 skipped.")


def generate_protobuf3():
    if g_input["output_dict"]["proto3"]:
        Path(proto3_output_dir).mkdir(parents=True, exist_ok=True)
        write_proto(3)
        print("proto3 done.")
    else:
        print("proto3 skipped.")


def generate_fprime():
    if g_input["output_dict"]["fpp"]:
        Path(fpp_output_dir).mkdir(parents=True, exist_ok=True)
        write_fpp()   
        print("fpp done.")  
    else:
        print("fpp skipped.")


def generate_ros2():
    if g_input["output_dict"]["msg"]:
        Path(msg_output_dir).mkdir(parents=True, exist_ok=True)
        write_ros2_msg()   
        print("msg done.")  
    else:
        print("msg skipped.") 

#----------------------- generate proto to fpp translator ---------------------

def get_struct_tupple(struct_name):
    return [tupple for tupple in parsed_data if tupple[0] == struct_name][0]


def is_enum(struct_name):
    return get_struct_tupple(struct_name)[2]


def get_proto_arg(direction):
    if direction == "proto2fpp":
        return g_input["translators"]["proto2fpp"]["proto_from"]
    else:
        return g_input["translators"]["fpp2proto"]["proto_to"]


def get_accessor(parent_name, direction):
    parent_is_arg_name = parent_name == get_proto_arg(direction)
    return "." if parent_is_arg_name else "->"


def get_prefixes(parent_name, direction):
    parent_is_arg_name = parent_name == get_proto_arg(direction)
    fpp_prefix = "" if parent_is_arg_name else "fpp_"
    proto_prefix = "" if parent_is_arg_name else "proto_"
    return fpp_prefix, proto_prefix


def get_proto_ptr_line(field_type, field_name, parent_name, direction):
    parent_is_arg_name = parent_name == get_proto_arg(direction)
    prefix = "" if parent_is_arg_name else "proto_"
    accessor = "." if parent_is_arg_name else "->"
    clear = "    proto_{}->Clear();\n\n".format(field_name) if parent_is_arg_name and direction == "fpp2proto" else ""
    return "    {}::{}* proto_{} = {}{}{}mutable_{}();\n{}".format(proto_ns, field_type, field_name, 
                                                                   prefix, parent_name, 
                                                                   accessor,
                                                                   str.lower(field_name),
                                                                   clear)


def get_fpp_ref_line(field_type, field_name, dynasty):
    push_parent(field_name, dynasty)
    return "    {}::{}& fpp_{} = const_cast<{}::{}&>({});\n".format(fpp_ns, field_type, field_name,
                                                                    fpp_ns, field_type, dynasty[0])


def push_parent(parent, dynasty):
    dynasty[0] = dynasty[0] + ".get{}()".format(parent)


def pop_parent(dynasty):
    s = dynasty[0]
    start = s.rfind(".get")
    dynasty[0] = s.replace(s[start:], "")


def proto2fpp_field_assigenment(fpp_parent_name, field_name, proto_parent_name, mult):
    fpp_prefix, proto_prefix = get_prefixes(proto_parent_name, "proto2fpp")

    if not mult:
        return "    {}{}.set{}({}{}->{}());\n".format(fpp_prefix, 
                                                      fpp_parent_name,
                                                      field_name, 
                                                      proto_prefix,
                                                      proto_parent_name,
                                                      str.lower(field_name))
    else:
        return "    {}{}.set{}({}{}->{}().data(), {});\n".format(fpp_prefix,
                                                                 fpp_parent_name,
                                                                 field_name, 
                                                                 proto_prefix,
                                                                 proto_parent_name,
                                                                 str.lower(field_name),
                                                                 mult)


def proto2fpp_enum_assigenment(fpp_parent_name, field_name, proto_parent_name, enum_type):
    fpp_prefix, proto_prefix = get_prefixes(proto_parent_name, "proto2fpp")

    return "    {}{}.set{}(({}::{}){}{}->{}());\n".format(fpp_prefix, 
                                                          fpp_parent_name,
                                                          field_name, 
                                                          fpp_ns,
                                                          enum_type,
                                                          proto_prefix,
                                                          proto_parent_name,
                                                          str.lower(field_name))


def proto2fpp_recursive(cpp_file, struct_type, proto_parent_name, fpp_parent_name, dynasty):
    """
    recursively generates the cpp code for a protobuff-to-fprime translator function.
        dynasty - a singleton list, so its single element can be passed by reference.
                  describes the hierarchical call order with some necessary boilerplate code.
    """

    tpl = get_struct_tupple(struct_type)

    for type_val in tpl[1]:
        field_name, mult = get_multiplicity(type_val[1], False)
        field_type = type_val[0]

        # integral type
        if field_type in g_input["type_dict"]:
            cpp_file.write(proto2fpp_field_assigenment(fpp_parent_name, 
                                                       field_name, 
                                                       proto_parent_name, 
                                                       mult))
        # enum
        elif is_enum(field_type):
            cpp_file.write(proto2fpp_enum_assigenment(fpp_parent_name, 
                                                      field_name, 
                                                      proto_parent_name, 
                                                      field_type))
        # struct
        else:
            cpp_file.write("\n")
            cpp_file.write(get_proto_ptr_line(field_type, field_name, proto_parent_name, "proto2fpp"))
            cpp_file.write(get_fpp_ref_line(field_type, field_name, dynasty))
            cpp_file.write("\n")

            # recursive call - handle the next level down
            proto2fpp_recursive(cpp_file, field_type, field_name, field_name, dynasty)

            # the string in dynasty "behaves" like a stack
            pop_parent(dynasty)

    
def write_proto2fpp_boilerplate(cpp_file, top_struct, proto_from, fpp_to):
    proto_ns = g_input["schemas"]["proto"]["package"]
    fpp_ns = g_input["schemas"]["fpp"]["module"]

    signiture = """
// autogenerated by compile.py

void proto2fpp({}::{}& {},
               {}::{}& {})
{{
""".format(
        proto_ns, top_struct, proto_from, fpp_ns, top_struct, fpp_to)

    cpp_file.write(signiture)


def generate_proto2fpp(top_struct):

    proto_from = g_input["translators"]["proto2fpp"]["proto_from"]
    fpp_to = g_input["translators"]["proto2fpp"]["fpp_to"]

    with open('{}{}'.format(translators_dir, top_struct+"_proto2fpp.cpp"), 'w') as cpp_file:
        write_proto2fpp_boilerplate(cpp_file, top_struct, proto_from, fpp_to)

        proto2fpp_recursive(cpp_file, top_struct, proto_from, fpp_to, [fpp_to])

        cpp_file.write("}\n")

    print("{}: proto2fpp generation done.".format(top_struct))

#----------------------- generate fpp to proto translator ---------------------

def get_local_array_types(struct_type, array_types):
    tpl = get_struct_tupple(struct_type)

    for type_val in tpl[1]:
        field_name, mult = get_multiplicity(type_val[1], False)
        field_type = type_val[0]

        # integral type
        if field_type in g_input["type_dict"]:
            if mult:
                array_types.add(field_type)
        # enum
        elif is_enum(field_type):
            return #TODO
        # struct
        else:
            get_local_array_types(field_type, array_types)


def write_fpp2proto_boilerplate(cpp_file, top_struct, fpp_from, proto_to):
    proto_ns = g_input["schemas"]["proto"]["package"]
    fpp_ns = g_input["schemas"]["fpp"]["module"]

    array_types = set(())
    get_local_array_types(top_struct, array_types)

    dummy = "    NATIVE_INT_TYPE dummy;\n" if array_types else ""

    signiture = """
// autogenerated by compile.py

void fpp2proto(const {}::{}& {},
               {}::{}& {})
{{
""".format(
        fpp_ns, top_struct, fpp_from, proto_ns, top_struct, proto_to)

    cpp_file.write(signiture)
    cpp_file.write(dummy)
    
    for t in array_types:
        t_cpp = g_input["type_dict"][t]["cpp"]
        t_fpp = g_input["type_dict"][t]["fpp"]
        cpp_file.write("    const {}* {}arr;\n".format(t_cpp, t_fpp))


def fpp2proto_field_assigenment(fpp_parent_name, field_type, field_name, proto_parent_name, mult):
    fpp_prefix, proto_prefix = get_prefixes(proto_parent_name, "fpp2proto")
    accessor = get_accessor(proto_parent_name, "fpp2proto")

    if not mult:
        return "    {}{}{}set_{}({}{}.get{}());\n".format(proto_prefix, 
                                                          proto_parent_name,
                                                          accessor,
                                                          str.lower(field_name), 
                                                          fpp_prefix,
                                                          fpp_parent_name,
                                                          field_name)
    else:
        arr = g_input["type_dict"][field_type]["fpp"] + "arr"
        return """
    {} = {}{}.get{}(dummy);
    for(int i = 0; i < {}; ++i)
      {}{}{}add_{}({}[i]);\n\n""".format(arr,
                                         fpp_prefix,
                                         fpp_parent_name,
                                         field_name, 
                                         mult,
                                         proto_prefix,
                                         proto_parent_name,
                                         accessor,
                                         str.lower(field_name), 
                                         arr)


def fpp2proto_enum_assigenment(fpp_parent_name, enum_type, field_name, proto_parent_name):
    fpp_prefix, proto_prefix = get_prefixes(proto_parent_name, "fpp2proto")
    accessor = get_accessor(proto_parent_name, "fpp2proto")

    return "    {}{}{}set_{}(({}::{}){}{}.get{}().e);\n".format(proto_prefix, 
                                                                proto_parent_name,
                                                                accessor,
                                                                str.lower(field_name), 
                                                                proto_ns,
                                                                enum_type,
                                                                fpp_prefix,
                                                                fpp_parent_name,
                                                                field_name)


def fpp2proto_recursive(cpp_file, struct_type, fpp_from, proto_to, dynasty):
    tpl = get_struct_tupple(struct_type)

    for type_val in tpl[1]:
        field_name, mult = get_multiplicity(type_val[1], False)
        field_type = type_val[0]

        # integral type
        if field_type in g_input["type_dict"]:
            cpp_file.write(fpp2proto_field_assigenment(fpp_from, 
                                                       field_type,
                                                       field_name, 
                                                       proto_to, 
                                                       mult))
        # enum
        elif is_enum(field_type):
            cpp_file.write(fpp2proto_enum_assigenment(fpp_from, 
                                                      field_type, 
                                                      field_name, 
                                                      proto_to))
        # struct
        else:
            cpp_file.write("\n")
            cpp_file.write(get_proto_ptr_line(field_type, field_name, proto_to, "fpp2proto"))
            cpp_file.write(get_fpp_ref_line(field_type, field_name, dynasty))
            cpp_file.write("\n")

            # recursive call - handle the next level down
            fpp2proto_recursive(cpp_file, field_type, field_name, field_name, dynasty)

            # the string in dynasty "behaves" like a stack
            pop_parent(dynasty)


def generate_fpp2proto(top_struct):   

    fpp_from = g_input["translators"]["fpp2proto"]["fpp_from"]
    proto_to = g_input["translators"]["fpp2proto"]["proto_to"]

    with open('{}{}'.format(translators_dir, top_struct+"_fpp2proto.cpp"), 'w') as cpp_file:
        write_fpp2proto_boilerplate(cpp_file, top_struct, fpp_from, proto_to)

        fpp2proto_recursive(cpp_file, top_struct, fpp_from, proto_to, [fpp_from])

        cpp_file.write("}\n")

    print("{}: fpp2proto generation done.".format(top_struct))

#----------------------------------  main -------------------------------------

def set_globals(input_file):
    global g_input
    f = open(input_file, "r")
    g_input = json.load(f)

    global proto2_output_dir
    global proto3_output_dir
    global fpp_output_dir
    global msg_output_dir
    global translators_dir
    
    base_output_dir = g_input["base_output_dir"]
    proto2_output_dir = base_output_dir + "proto2/"
    proto3_output_dir = base_output_dir + "proto3/"
    fpp_output_dir = base_output_dir + "fpp/"
    msg_output_dir = base_output_dir + "msg/"
    translators_dir = base_output_dir + "translators/"

    global proto_ns
    global fpp_ns
    proto_ns = g_input["schemas"]["proto"]["package"]
    fpp_ns = g_input["schemas"]["fpp"]["module"]


def parse_headers():
    for header in g_input["header_files"]:
        if not Path(g_input["header_dir"] + header).exists():
            print("The header file {} was not found in {}\n Aborting.".format(header, g_input["header_dir"]))
            sys.exit(2)

        with open('{}{}'.format(g_input["header_dir"], header), 'r') as input_file:
            for line in input_file:
                header_lines.append(line)

    for top_struct in g_input["top_structs"]:
        parse_struct(top_struct)


def generate_schemas():
    generate_protobuf2()
    generate_protobuf3()
    generate_fprime()
    generate_ros2()


def generate_translators():
    Path(translators_dir).mkdir(parents=True, exist_ok=True)
    
    for ts in g_input["top_structs"]:
        if g_input["output_dict"]["proto2fpp"]:
            generate_proto2fpp(ts)
        else:
            print("{}: proto2fpp skipped".format(ts))
        if g_input["output_dict"]["fpp2proto"]:
            generate_fpp2proto(ts)
        else:
            print("{}: fpp2proto skipped".format(ts))


def main(argv):

    set_globals(argv[0])

    parse_headers()

    generate_schemas()

    generate_translators()


# entry point
if __name__ == "__main__":
    main(sys.argv[1:])
