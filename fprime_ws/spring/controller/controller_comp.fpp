module spring {

  @ The controller component
  active component controller_comp {

    # ----------------------------------------------------------------------
    # General ports
    # ----------------------------------------------------------------------

    @ Port for receiving input from dynamics
    async input port state_in: from_dynamics

    @ Port for passing the output to dynamics.
    output port control_out: to_dynamics

    # ----------------------------------------------------------------------
    # Special ports
    # ----------------------------------------------------------------------

    # @ Command receive
    command recv port cmdIn

    @ Command registration
    command reg port cmdRegOut

    @ Command response
    command resp port cmdResponseOut

    @ Event
    event port eventOut

    # @ Parameter get
    #param get port prmGetOut

    # @ Parameter set
    #param set port prmSetOut

    @ Telemetry
    telemetry port tlmOut

    @ Text event
    text event port textEventOut

    @ Time get
    time get port timeGetOut

    
    # ----------------------------------------------------------------------
    # Telemetry
    # ----------------------------------------------------------------------

    telemetry r: F32
    telemetry v: F32
    telemetry u: F32
  }

}