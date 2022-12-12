#include "../include/dynamics_node/dynamics_node.hpp"

DynamicsNode::DynamicsNode(): 
Node("dynamics"), _count(0)
{
    RCLCPP_INFO(get_logger(), "Initiating Dynamics node.");

    init_ros();
    init_parameters();

    _dynamics.set_parameters(_m.as_double(), 
                             _k.as_double(), 
                             _c.as_double(), 
                             _r0.as_double(), 
                             _v0.as_double());
    RCLCPP_INFO(get_logger(), 
                "Parameters: [m, k, c, r0, v0] = [%.2f, %.2f, %.2f, %.2f, %.2f]",
                            _m.as_double(), 
                            _k.as_double(), 
                            _c.as_double(), 
                            _r0.as_double(), 
                            _v0.as_double());
}

DynamicsNode::~DynamicsNode()
{
  return;
}

void DynamicsNode::init_ros()
{
    _pub_state = this->create_publisher<dynamics_node::msg::State>("/state", 1);
    _sub_controller = this->create_subscription<dynamics_node::msg::ControlSignal>("/control_signal",1, std::bind(&DynamicsNode::cb_get_control_signal, this, std::placeholders::_1));
    _sub_enable = this->create_subscription<std_msgs::msg::Bool>("/enable",1, std::bind(&DynamicsNode::cb_get_enable_signal, this, std::placeholders::_1));
}

void DynamicsNode::init_parameters()
{
    this->declare_parameter("m", 1.0);
    this->declare_parameter("k", 2.5);
    this->declare_parameter("c", 0.3);
    this->declare_parameter("r0", -1.0);
    this->declare_parameter("v0", 0.0);

    _m = this->get_parameter("m");
    _k = this->get_parameter("k");
    _c = this->get_parameter("c");
    _r0 = this->get_parameter("r0");
    _v0 = this->get_parameter("v0");
}

void DynamicsNode::dynamics_first_step()
{
    state dynamics_output;
    control_signal dynamics_input;

    dynamics_input.u = 0.0;

    _dynamics.set_inputs(dynamics_input);
    _dynamics.step();
    _dynamics.get_outputs(dynamics_output);

}

void DynamicsNode::publish_to_ros(state &dynamics_output)
{
    dynamics_node::msg::State dyn_msg;

    dyn_msg.r = dynamics_output.r;
    dyn_msg.v = dynamics_output.v;

    _pub_state.get()->publish(dyn_msg);
}

void DynamicsNode::cb_get_control_signal(const dynamics_node::msg::ControlSignal::SharedPtr msg)
{
    _u = msg.get()->u;
}

void DynamicsNode::cb_get_enable_signal(const std_msgs::msg::Bool::SharedPtr msg)
{
    state dynamics_output;
    control_signal dynamics_input;

    if (first_step)
    {
      dynamics_first_step();
      first_step = false;
      return;
    }

    dynamics_input.u = _u;
    
    _dynamics.set_inputs(dynamics_input);
    _dynamics.step();
    _dynamics.get_outputs(dynamics_output);

    publish_to_ros(dynamics_output);
    
    RCL_UNUSED(msg);
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<DynamicsNode>());
  rclcpp::shutdown();
  return 0;
}