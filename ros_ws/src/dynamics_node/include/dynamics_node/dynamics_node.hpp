#ifndef DYNAMICS_HPP_
#define DYNAMICS_HPP_

#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <thread>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/bool.hpp"
#include "dynamics_node/msg/state.hpp"
#include "dynamics_node/msg/control_signal.hpp"

#include "../../../../../common/lulav_comm/udp/src/udp_client_server.hpp"
#include "../../../../../examples/spring_mass_dumper/include/dynamics.hpp"
#include "../../../../../common/autogen/schemas/spring/proto3/spring.pb.h"

#define STATE_MESSAGE_SIZE 32
#define CONTROL_MESSAGE_SIZE 24

#define SERVER_PORT 42000
#define CLIENT_PORT 69000

using namespace std::chrono_literals;

class DynamicsNode : public rclcpp::Node
{

  public:
      DynamicsNode();
      ~DynamicsNode();

  private:

    size_t _count;

    Dynamics _dynamics;

    bool first_step = true;

    std::shared_ptr<lulav::comm::udp::client> _udp_client;
    std::shared_ptr<lulav::comm::udp::server> _udp_server;

    char _controller_buff[CONTROL_MESSAGE_SIZE];
    char _dynamics_buff[STATE_MESSAGE_SIZE];

    void init_ros();
    void init_parameters();
    void dynamics_first_step();
    void cb_enable(const std_msgs::msg::Bool::SharedPtr msg);
    void publish_to_ros(state &dynamics_output, control_signal &dynamics_input);

    rclcpp::Parameter _m;
    rclcpp::Parameter _k;
    rclcpp::Parameter _c;
    rclcpp::Parameter _r0;
    rclcpp::Parameter _v0;
    
    rclcpp::Publisher<dynamics_node::msg::State>::SharedPtr _pub_state;
    rclcpp::Publisher<dynamics_node::msg::ControlSignal>::SharedPtr _pub_controller;
    rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr _sub_enable;
};

#endif