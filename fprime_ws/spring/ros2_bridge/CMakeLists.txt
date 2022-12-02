set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/ros2_bridge.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/ros2_bridge.cpp"
  
  # communication protocol of choice:
  "${CMAKE_CURRENT_LIST_DIR}/../../../common/lulav_comm/udp/src/udp_client.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/../../../common/lulav_comm/udp/src/udp_server.cpp"
)

# Protocol Buffers library
find_package(Protobuf REQUIRED)

set(SCHEMAS_AUTOGEN "${CMAKE_CURRENT_LIST_DIR}/../../../common/autogen/schemas")
set(PROTO_VERSION "proto3")

set(PROTO_SPRING "${SCHEMAS_AUTOGEN}/spring/${PROTO_VERSION}/*.proto")

# generate and build the protobuf messages
file(GLOB_RECURSE ProtoFiles "${PROTO_SPRING}")
PROTOBUF_GENERATE_CPP(ProtoSources ProtoHeaders ${ProtoFiles})
add_library(proto STATIC ${ProtoSources} ${ProtoHeaders})
target_link_libraries(proto ${PROTOBUF_LIBRARY})
target_link_libraries(${spring_ros2_bridge} proto)

set(MOD_DEPS proto)

register_fprime_module()
