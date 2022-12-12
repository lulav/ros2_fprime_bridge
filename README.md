# ROS2-FPrime Bridge

This repository provides a simple and convenient way to bridge the gap between FPrime and ROS2 when such integration is required. This solution enables a complete decoupling between the two frameworks, and actually can be used to integrate FPrime or ROS2 with any other framework.

The user needs to define the messages going back and forth between the two frameworks by writing cpp headers that define the structures that make up the messages.

The cpp headers are used as the source by which all communication messages are defined for all interface description languages. A python script parses the headers, and generates schema files for:
- F` (.fpp)
- ROS (.msg)
- [Protobuf](https://developers.google.com/protocol-buffers) (.proto, version 2 and 3)

For further details of the usage of the python script see the dedicated [README](common/autogen/README.md).

The user needs to define an FPrime component and a ROS node that will act as the two ends of the bridge. Communication between the FPrime component and the ROS node is performed via either UDP or named pipes (FIFO), for which simple wrapper classes are provided. Alternatively, you may choose any other relevant protocol.

ProtoBuf serialization + deserialization takes (much) less than 100 microseconds (even for large messages with dozens of fields). On each end of the bridge, message fields are “translated” seriatim between Protobuf and ROS/FPrime. The python script also provides automatic code generation for the translator functions (currently FPrime-ProtoBuf only).  

## The spring example
The repository also provides an example project called `spring_mass_dumper`, which, as the name suggests, is a simple example of a spring mass dumper, in which the spring controller implementation resides inside an FPrime component, and the simulation that drives it resides inside a ROS2 node. This example may be used as a boilerplate for your project, since the basic functionality will likely stay the same, the only changes being the specific messages between ROS2 and FPrime.

The project provides a header file named [io_structs.hpp](examples/spring_mass_dumper/include/io_structs.hpp) in which the messages between the simulation and controller are defined, and which is used as the input for the python script.

This example uses UDP as the underlying communication protocol and creates a two way channel (each side has a client and a server). A simple ROS node ("scheduler") drives the entire system at 100Hz. 

Further details about the internal implementation of the spring project (which may be compiled as a stand-alone project) can be found in its [README](examples/spring_mass_dumper/README.md) file. 

![design](png/design.png "high level design")

## Prerequisites 
since everything is run inside a Docker container, the only two prerequisites are:
- [Visual Studio Code](https://code.visualstudio.com/download)
- [Docker](https://www.docker.com/)

## Build the spring example
### clone the repository to your local machine:
                
    git clone https://github.com/lulav/ros2_fprime_bridge.git

### open the repository in VScode:

    cd ~/ros2_fprime_bridge
    code .

Before you begin, make sure that within Visual Studio Code, you've opened the working directory inside a [Dev Container](https://code.visualstudio.com/docs/devcontainers/containers) by choosing the `reopen in container` option.

### generate schema files and ProtoBuf code:

    cd common/autogen
    python3 compile.py spring_defs.json
    protoc -I=schemas/spring/proto3 --cpp_out=./schemas/spring/proto3 spring.proto
**Note**: the protoc compiler actually runs automatically as part of the build process in the spring example (both on the FPrime and ROS2 builds). See the `CMakeLists.txt` files of the bridge component/node.

### build the ROS2 project:

    cd ros_ws
    source install/local_setup.bash
    colcon build
### build the FPrime project:

    cd fprime_ws/spring
    fprime-utils generate
    fprime-utils build

## Run the spring example
1. Run the Fprime GDS:

        cd fprime_ws/spring
        fprime-gds
    a browser with the GDS GUI should come up at this point (may take a few seconds). If it doesn't, just open it manually (on `127.0.0.1:5000`).
2. Run the ROS2 project:

        cd ros_ws
        ros2 launch scheduler simulator.launch.py

At this point, if you open the charts tab in the GDS GUI and choose `the_controller.u` from the dropdown menu, you should see something similar to the following telemetry:

![GDS screenshot](png/screenshot_gds.png "spring mass dumper")

In addition, if you open a ROS2 viewer, e.g. [Foxglove](https://foxglove.dev/download), you should also see a similar visualization:

![Foxglove screenshot](png/screenshot_foxglove.png "spring mass dumper")

# Feedback
Please send your questions, bug reports and suggestions to `shalev@lulav.space`.

Your flattery and hard earned cash are also welcome ;) 