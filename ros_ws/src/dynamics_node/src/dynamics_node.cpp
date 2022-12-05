#include "../include/dynamics_node/dynamics_node.hpp"

DynamicsNode::DynamicsNode(): 
Node("dynamics"), _count(0)
{
    RCLCPP_INFO(get_logger(), "Initiate Dynamics node ...");

    _init_ros();

    _get_parameters();

    dynamics.set_parameters(_m.as_double(), _k.as_double(), _c.as_double(), _r0.as_double(), _v0.as_double());

}

DynamicsNode::~DynamicsNode()
{
  return;
}

void DynamicsNode::_init_ros()
{
    _pub_state = this->create_publisher<dynamics_node::msg::State>("/state", 1);
    _pub_controller = this->create_publisher<dynamics_node::msg::ControlSignal>("/control_signal", 1);
    _sub_enable = this->create_subscription<std_msgs::msg::Bool>("/enable",1, std::bind(&DynamicsNode::_cb_enable, this, std::placeholders::_1));
}

void DynamicsNode::_get_parameters()
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

void DynamicsNode::_dynamics_first_step(Dynamics &dynamics, state &dynamics_output, control_signal &dynamics_input)
{
    dynamics_input.u = 0.0;

    dynamics.set_inputs(dynamics_input);
    dynamics.step();
    dynamics.get_outputs(dynamics_output);
}

void DynamicsNode::_publish_to_ros(state &dynamics_output, control_signal &dynamics_input)
{
      dynamics_node::msg::State dyn_msg;
      dynamics_node::msg::ControlSignal ctrl_msg;

      dyn_msg.r = dynamics_output.r;
      dyn_msg.v = dynamics_output.v;
      ctrl_msg.u = dynamics_input.u;

      _pub_state.get()->publish(dyn_msg);
      _pub_controller.get()->publish(ctrl_msg);
}

void DynamicsNode::_cb_enable(const std_msgs::msg::Bool::SharedPtr msg)
{
    state dynamics_output;
    control_signal dynamics_input;

    proto_spring::control_signal proto_u;
    proto_spring::state proto_state;

    if (first_step)
    {
      _dynamics_first_step(dynamics, dynamics_output, dynamics_input);

      proto_state.set_r(dynamics_output.r);
      proto_state.set_v(dynamics_output.v);

      proto_state.SerializeToArray(_dynamics_buff, STATE_MESSAGE_SIZE);

      _udp_client.get()->send(_dynamics_buff, STATE_MESSAGE_SIZE);

      first_step = false;
      return;
    }

    _udp_server.get()->recv(_controller_buff, CONTROL_MESSAGE_SIZE);

    proto_u.ParseFromArray(_controller_buff, CONTROL_MESSAGE_SIZE);

    dynamics_input.u = proto_u.u();
    
    dynamics.set_inputs(dynamics_input);
    dynamics.step();
    dynamics.get_outputs(dynamics_output);

    proto_state.set_r(dynamics_output.r);
    proto_state.set_v(dynamics_output.v);

    proto_state.SerializeToArray(_dynamics_buff, STATE_MESSAGE_SIZE);

    _udp_client.get()->send(_dynamics_buff, STATE_MESSAGE_SIZE);
    _publish_to_ros(dynamics_output, dynamics_input);

    proto_state.Clear();
    proto_u.Clear();
    
    RCL_UNUSED(msg);
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<DynamicsNode>());
  rclcpp::shutdown();
  return 0;
}