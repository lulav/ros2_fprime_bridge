To generate the schema files and translators:
- for the spring example:   
`python3 compile.py spring_defs.json`

To generate ProtoBuff code from the proto files generated in the previous step:
- for the spring example:   
`protoc -I=schemas/spring/proto3 --cpp_out=./schemas/spring/proto3 spring.proto`