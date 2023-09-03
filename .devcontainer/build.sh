#!/bin/bash

# building schemas
cd common/autogen
chmod +x compile.py
./compile.py spring_defs.json
protoc -I=schemas/spring/proto3 --cpp_out=./schemas/spring/proto3 spring.proto

cd ../..

# compile fprime_ws
rm -rf fprime_ws/spring/build-artifacts fprime_ws/spring/build-fprime-automatic-native
cd fprime_ws/spring
fprime-util generate
fprime-util build 

cd ../..

# compiling ros workspace
rm -rf ros_ws/build/ ros_ws/log/ ros_ws/install/
. /opt/ros/humble/setup.sh
cd ros_ws
colcon build
echo "source /workspaces/ros2_fprime_bridge/ros_ws/install/local_setup.bash" >> ~/.bashrc