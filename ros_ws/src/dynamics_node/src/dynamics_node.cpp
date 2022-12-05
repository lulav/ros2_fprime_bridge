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
    Dynamics dynamics;
    state dynamics_output;
    control_signal dynamics_input;
    Dynamics::parameters dynamics_parameters;

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

    _publish_to_ros(dynamics_output, dynamics_input);

    proto_state.set_r(dynamics_output.r);
    proto_state.set_v(dynamics_output.v);

    proto_state.SerializeToArray(_dynamics_buff, STATE_MESSAGE_SIZE);

    _udp_client.get()->send(_dynamics_buff, STATE_MESSAGE_SIZE);

    proto_state.Clear();
    proto_u.Clear();
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<DynamicsNode>());
  rclcpp::shutdown();
  return 0;
}