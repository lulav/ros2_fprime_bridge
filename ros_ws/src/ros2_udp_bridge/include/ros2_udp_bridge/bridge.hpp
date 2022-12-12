#ifndef BRIDGE_HPP_
#define BRIDGE_HPP_

#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <thread>

#include "rclcpp/rclcpp.hpp"
#include "dynamics_node/msg/state.hpp"
#include "dynamics_node/msg/control_signal.hpp"

#include "../../../../../common/lulav_comm/udp/src/udp_client_server.hpp"
#include "../../../../../common/autogen/schemas/spring/proto3/spring.pb.h"

#define STATE_MESSAGE_SIZE 32
#define CONTROL_MESSAGE_SIZE 24

#define SERVER_PORT 42000
#define CLIENT_PORT 69000

#define BRIDGE_WORKING_TIME 10ms

using namespace std::chrono_literals;

class Bridge : public rclcpp::Node
{

  public:
      Bridge();
      ~Bridge();

  private:

    size_t _count;

    std::shared_ptr<lulav::comm::udp::client> _udp_client;
    std::shared_ptr<lulav::comm::udp::server> _udp_server;

    std::shared_ptr<std::thread> _reader_thread;

    bool _keep_reading = true;

    char _controller_buff[CONTROL_MESSAGE_SIZE];
    char _dynamics_buff[STATE_MESSAGE_SIZE];

    void init_ros();
    void _proto_to_ros();
    void _ros_to_proto(const dynamics_node::msg::State::SharedPtr msg);
    void reading_work();
    
    rclcpp::Subscription<dynamics_node::msg::State>::SharedPtr _sub_state;
    rclcpp::Publisher<dynamics_node::msg::ControlSignal>::SharedPtr _pub_controller;
};

#endif