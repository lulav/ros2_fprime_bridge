To generate the schema files and translators:
- for the controller:   
`python3 compile.py controller_defs.json`
- for the dynamics:     
`python3 compile.py dynamics_defs.json`

To generate ProtoBuff code from the proto files generated in the previous step:
- for the controller:   
`protoc -I=schemas/controller/proto3 --cpp_out=./schemas/controller/proto3 controller.proto`
- for the dynamics:     
`protoc -I=schemas/dynamics/proto3 --cpp_out=./schemas/dynamics/proto3 dynamics.proto`