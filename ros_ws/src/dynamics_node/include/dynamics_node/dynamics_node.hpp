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

#include "../../../../../examples/spring_mass_dumper/include/dynamics.hpp"

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

    float _u;

    void init_ros();
    void init_parameters();
    void dynamics_first_step();
    void cb_get_enable_signal(const std_msgs::msg::Bool::SharedPtr msg);
    void cb_get_control_signal(const dynamics_node::msg::ControlSignal::SharedPtr msg);
    void publish_to_ros(state &dynamics_output);

    rclcpp::Parameter _m;
    rclcpp::Parameter _k;
    rclcpp::Parameter _c;
    rclcpp::Parameter _r0;
    rclcpp::Parameter _v0;
    
    rclcpp::Publisher<dynamics_node::msg::State>::SharedPtr _pub_state;
    rclcpp::Subscription<dynamics_node::msg::ControlSignal>::SharedPtr _sub_controller;
    rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr _sub_enable;
};

#endif