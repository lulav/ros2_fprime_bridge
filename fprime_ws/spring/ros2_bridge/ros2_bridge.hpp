// ======================================================================
// \title  ros2_bridge.hpp
// \author dev
// \brief  hpp file for ros2_bridge component implementation class
// ======================================================================

#ifndef ros2_bridge_HPP
#define ros2_bridge_HPP

#include "spring/ros2_bridge/ros2_bridgeComponentAc.hpp"

#include "../../../common/autogen/schemas/spring/proto3/spring.pb.h"
#include "../../../common/lulav_comm/udp/src/udp_client_server.hpp"

#include <functional>
#include <thread>
#include <memory>

#define STATE_MESSAGE_SIZE 32
#define CONTROL_MESSAGE_SIZE 24

#define CLIENT_PORT 42000
#define SERVER_PORT 69000

namespace spring {

  class ros2_bridge :
    public ros2_bridgeComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object ros2_bridge
      //!
      ros2_bridge(
          const char *const compName /*!< The component name*/
      );

      //! Initialize object ros2_bridge
      //!
      void init(
          const NATIVE_INT_TYPE queueDepth, /*!< The queue depth*/
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object ros2_bridge
      //!
      ~ros2_bridge();

    private:

    std::shared_ptr<std::thread> _reader_thread;

    std::shared_ptr<lulav::comm::udp::client> _udp_client;
    std::shared_ptr<lulav::comm::udp::server> _udp_server;

    char _controller_buff[CONTROL_MESSAGE_SIZE];
    char _dynamics_buff[STATE_MESSAGE_SIZE];

    bool _keep_reading = true;

    void reading_work();
    void dynamics_read();

    // auto generated code by compile.py
    void proto2fpp(proto_spring::state& dynamics_output,
                   spring::state& controller_input);

    // auto generated code by compile.py
    void fpp2proto(const spring::control_signal& controller_output,
                   proto_spring::control_signal& dynamics_input);

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for control_in
      //!
      void control_in_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          const spring::control_signal &control_output /*!< 
      output from controller
      */
      );


    };

} // end namespace spring

#endif
