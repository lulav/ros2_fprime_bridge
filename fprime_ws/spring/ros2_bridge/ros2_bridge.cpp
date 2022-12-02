// ======================================================================
// \title  ros2_bridge.cpp
// \author dev
// \brief  cpp file for ros2_bridge component implementation class
// ======================================================================


#include <spring/ros2_bridge/ros2_bridge.hpp>
#include "Fw/Types/BasicTypes.hpp"

using namespace lulav::comm::udp;

namespace spring {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  ros2_bridge ::
    ros2_bridge(
        const char *const compName
    ) : ros2_bridgeComponentBase(compName)
  {
    _reader_thread = std::make_shared<std::thread>(std::bind(&ros2_bridge::reading_work, this));
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
    _keep_reading = false;

    if(_reader_thread->joinable())
      _reader_thread->join();
  }

  void ros2_bridge::reading_work()
  {
    printf("ros2_bridge::opening UDP sockets...\n");
    _udp_client = std::make_shared<client>("0.0.0.0", 42000);
    _udp_server = std::make_shared<server>("0.0.0.0", 69000);
    printf("Done. listening on port 69000\n");
    
    while(_keep_reading)
    {
      dynamics_read();
    }
  }

  void ros2_bridge::dynamics_read()
  {
    proto_spring::state dynamics_output;
    spring::state controller_input;

    // read from UDP socket (blocking)
    _udp_server->recv(_dynamics_buff, STATE_MESSAGE_SIZE);

    // parse proto message
    dynamics_output.ParseFromArray(_dynamics_buff, STATE_MESSAGE_SIZE);
    
    // copy to F` message
    proto2fpp(dynamics_output, controller_input);

    // send message to F` GNC component
    this->state_out_out(0, controller_input);
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
    proto_spring::control_signal dynamics_input;

    // copy F` message to proto message
    fpp2proto(control_output, dynamics_input);

    // serialize proto message
    dynamics_input.SerializeToArray(_controller_buff, CONTROL_MESSAGE_SIZE);
    
    // write to UDP socket
    _udp_client->send(_controller_buff,CONTROL_MESSAGE_SIZE);
  }

  void ros2_bridge::proto2fpp(proto_spring::state& dynamics_output,
                              spring::state& controller_input)
  {
      controller_input.setr(dynamics_output.r());
      controller_input.setv(dynamics_output.v());
  }

  void ros2_bridge::fpp2proto(const spring::control_signal& controller_output,
                              proto_spring::control_signal& dynamics_input)
  {
      dynamics_input.set_u(controller_output.getu());
  }

} // end namespace spring
