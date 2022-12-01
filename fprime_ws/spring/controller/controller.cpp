// ======================================================================
// \title  controller.cpp
// \author dev
// \brief  cpp file for controller component implementation class
// ======================================================================


#include <spring/controller/controller.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace spring {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  controller ::
    controller(
        const char *const compName
    ) : controllerComponentBase(compName)
  {

  }

  void controller ::
    init(
        const NATIVE_INT_TYPE queueDepth,
        const NATIVE_INT_TYPE instance
    )
  {
    controllerComponentBase::init(queueDepth, instance);
  }

  controller ::
    ~controller()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void controller ::
    state_in_handler(
        const NATIVE_INT_TYPE portNum,
        const spring::state &state_input
    )
  {
    // TODO
  }

} // end namespace spring
