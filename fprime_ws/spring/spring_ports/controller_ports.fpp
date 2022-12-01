module spring {

  @ Port for controller input from dynamics
  port from_dynamics(
                    state_input: state @< input from dynamics
                    )

  @ Port for controller output back to dynamics
  port to_dynamics(
                    control_output: control_signal @< output from controller 
                  )

}