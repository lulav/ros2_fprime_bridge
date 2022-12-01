// ======================================================================
// \title  ros2_bridge.cpp
// \author dev
// \brief  cpp file for ros2_bridge component implementation class
// ======================================================================


#include <spring/ros2_bridge/ros2_bridge.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace spring {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  ros2_bridge ::
    ros2_bridge(
        const char *const compName
    ) : ros2_bridgeComponentBase(compName)
  {

  }

  void ros2_bridge ::
    init(
        const NATIVE_INT_TYPE queueDepth,
        const NATIVE_INT_TYPE instance
    )
  {
    ros2_bridgeComponentBase::init(queueDepth, instance);
  }

  ros2_bridge ::
    ~ros2_bridge()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void ros2_bridge ::
    control_in_handler(
        const NATIVE_INT_TYPE portNum,
        const spring::control_signal &control_output
    )
  {
    // TODO
  }

} // end namespace spring
