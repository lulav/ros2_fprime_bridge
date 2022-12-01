module spring {

  @ The component in charge of the communication bridge to the ROS2 framework.
  active component ros2_bridge {

    # ----------------------------------------------------------------------
    # General ports
    # ----------------------------------------------------------------------

    @ Port for receiving control signals from the controller so they can be passed to ros2 dynamics.
    async input port control_in: to_dynamics

    @ Port for sending the state input from ros2 dynamics to the controller.
    output port state_out: from_dynamics

    # ----------------------------------------------------------------------
    # Special ports
    # ----------------------------------------------------------------------

    @ Text event
    text event port textEventOut

    @ Time get
    time get port timeGetOut

  }

}