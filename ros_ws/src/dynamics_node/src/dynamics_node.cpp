#include "../include/dynamics_node/dynamics_node.hpp"

DynamicsNode::DynamicsNode(): 
Node("dynamics"), _count(0)
{
    RCLCPP_INFO(get_logger(), "Initiate Dynamics node ...");
    init_ros();
}

DynamicsNode::~DynamicsNode()
{
  return;
}

void DynamicsNode::init_ros()
{
    _pub_state = this->create_publisher<dynamics_node::msg::State>("/state", 1);
    _pub_controller = this->create_publisher<dynamics_node::msg::ControlSignal>("/control_signal", 1);
    _sub_enable = this->create_subscription<std_msgs::msg::Bool>("/enable",1, std::bind(&DynamicsNode::_cb_enable, this, std::placeholders::_1));
}

void DynamicsNode::dynamics_first_step()
{
    Dynamics dynamics;
    // state dynamics_output;
    // control_signal dynamics_input;
    // Dynamics::parameters dynamics_parameters;

    // dynamics_node::msg::State dyn_msg;
    // dynamics_node::msg::ControlSignal ctrl_msg;

    // dynamics_input.u = 0.0;

    // dynamics.set_inputs(dynamics_input);
    // dynamics.step();
    // dynamics.get_outputs(dynamics_output);

    // dyn_msg.r = dynamics_output.r;
    // dyn_msg.v = dynamics_output.v;
    // ctrl_msg.u = dynamics_input.u;

    // _pub_state.get()->publish(dyn_msg);
    // _pub_controller.get()->publish(ctrl_msg);
}

void DynamicsNode::_cb_enable(const std_msgs::msg::Bool::SharedPtr msg)
{
    if (first_step)
    {
      dynamics_first_step();
      first_step = false;
    }

}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<DynamicsNode>());
  rclcpp::shutdown();
  return 0;
}