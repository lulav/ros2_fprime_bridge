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

#define STATE_MESSAGE_SIZE 32
#define CONTROL_MESSAGE_SIZE 24

#define SERVER_PORT 42000
#define CLIENT_PORT 69000

using namespace std::chrono_literals;

class DynamicsNode : public rclcpp::Node
{

  public:

      void init_ros();
      
      DynamicsNode();
      ~DynamicsNode();

      bool first_step = false;

  private:

    size_t _count;

    void _cb_enable(const std_msgs::msg::Bool::SharedPtr msg);
    void dynamics_first_step();

    rclcpp::Publisher<dynamics_node::msg::State>::SharedPtr _pub_state;
    rclcpp::Publisher<dynamics_node::msg::ControlSignal>::SharedPtr _pub_controller;
    rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr _sub_enable;
};

#endif