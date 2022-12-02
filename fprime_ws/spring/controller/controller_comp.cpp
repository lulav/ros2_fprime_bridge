// ======================================================================
// \title  controller_comp.cpp
// \author dev
// \brief  cpp file for controller_comp component implementation class
// ======================================================================


#include <spring/controller/controller_comp.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace spring {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  controller_comp ::
    controller_comp(
        const char *const compName
    ) : controller_compComponentBase(compName)
  {

  }

  void controller_comp ::
    init(
        const NATIVE_INT_TYPE queueDepth,
        const NATIVE_INT_TYPE instance
    )
  {
    controller_compComponentBase::init(queueDepth, instance);
  }

  controller_comp ::
    ~controller_comp()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void controller_comp ::
    state_in_handler(
        const NATIVE_INT_TYPE portNum,
        const spring::state &state_input
    )
  {
    ::state controller_input;
    ::control_signal controller_output;
    spring::control_signal dynamics_input;

    copy_to_controller_input(state_input, controller_input);

    _controller.set_inputs(controller_input);

    _controller.step();

    _controller.get_outputs(controller_output);

    copy_from_controller_output(controller_output, dynamics_input);

    // send control signal to the bridge component.
    this->control_out_out(0, dynamics_input);

    write_telemetry(dynamics_input);
  }

  void controller_comp::copy_to_controller_input(const spring::state &state_input,
                                                 ::state controller_input)
  {
    controller_input.r = state_input.getr();
    controller_input.v = state_input.getv();
  }

  void controller_comp::copy_from_controller_output(const ::control_signal& controller_output,
                                                    spring::control_signal& dynamics_input)
  {
    dynamics_input.setu(controller_output.u);
  }

  void controller_comp::write_telemetry(const spring::control_signal& dynamics_input)
  {
    tlmWrite_u(dynamics_input.getu());
  }

} // end namespace spring
