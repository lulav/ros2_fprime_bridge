#include "../include/dynamics_node/dynamics_node.hpp"

using namespace lulav::comm::udp;

DynamicsNode::DynamicsNode(): 
Node("dynamics"), _count(0)
{
    RCLCPP_INFO(get_logger(), "Initiating Dynamics node.");

    init_ros();
    init_parameters();

    RCLCPP_INFO(get_logger(), 
                "Parameters: [m, k, c, r0, v0] = [%.2f, %.2f, %.2f, %.2f, %.2f]",
                _m.as_double(), 
                _k.as_double(), 
                _c.as_double(), 
                _r0.as_double(), 
                _v0.as_double());

    _dynamics.set_parameters(_m.as_double(), 
                             _k.as_double(), 
                             _c.as_double(), 
                             _r0.as_double(), 
                             _v0.as_double());
    
    RCLCPP_INFO(get_logger(), "ros2_bridge: opening UDP sockets... ");
    _udp_client = std::make_shared<client>("0.0.0.0", CLIENT_PORT);
    _udp_server = std::make_shared<server>("0.0.0.0", SERVER_PORT);
    RCLCPP_INFO(get_logger(), "Done. listening on port %d\n", SERVER_PORT);
}

DynamicsNode::~DynamicsNode()
{
  return;
}

void DynamicsNode::init_ros()
{
    _pub_state = this->create_publisher<dynamics_node::msg::State>("/state", 1);
    _pub_controller = this->create_publisher<dynamics_node::msg::ControlSignal>("/control_signal", 1);
    _sub_enable = this->create_subscription<std_msgs::msg::Bool>("/enable",1, std::bind(&DynamicsNode::cb_enable, this, std::placeholders::_1));
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
    proto_spring::state proto_state;

    proto_state.Clear();

    dynamics_input.u = 0.0;

    _dynamics.set_inputs(dynamics_input);
    _dynamics.step();
    _dynamics.get_outputs(dynamics_output);

    proto_state.set_r(dynamics_output.r);
    proto_state.set_v(dynamics_output.v);

    proto_state.SerializeToArray(_dynamics_buff, STATE_MESSAGE_SIZE);

    _udp_client->send(_dynamics_buff, STATE_MESSAGE_SIZE);
}

void DynamicsNode::publish_to_ros(state &dynamics_output, control_signal &dynamics_input)
{
      dynamics_node::msg::State dyn_msg;
      dynamics_node::msg::ControlSignal ctrl_msg;

      dyn_msg.r = dynamics_output.r;
      dyn_msg.v = dynamics_output.v;
      ctrl_msg.u = dynamics_input.u;

      _pub_state.get()->publish(dyn_msg);
      _pub_controller.get()->publish(ctrl_msg);
}

void DynamicsNode::cb_enable(const std_msgs::msg::Bool::SharedPtr msg)
{
    state dynamics_output;
    control_signal dynamics_input;

    proto_spring::control_signal proto_u;
    proto_spring::state proto_state;

    proto_state.Clear();
    proto_u.Clear();
    
    if (first_step)
    {
      dynamics_first_step();
      first_step = false;
      return;
    }

    _udp_server->recv(_controller_buff, CONTROL_MESSAGE_SIZE);

    proto_u.ParseFromArray(_controller_buff, CONTROL_MESSAGE_SIZE);

    dynamics_input.u = proto_u.u();
    
    _dynamics.set_inputs(dynamics_input);
    _dynamics.step();
    _dynamics.get_outputs(dynamics_output);

    proto_state.set_r(dynamics_output.r);
    proto_state.set_v(dynamics_output.v);

    proto_state.SerializeToArray(_dynamics_buff, STATE_MESSAGE_SIZE);

    _udp_client->send(_dynamics_buff, STATE_MESSAGE_SIZE);

    publish_to_ros(dynamics_output, dynamics_input);
    
    RCL_UNUSED(msg);
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<DynamicsNode>());
  rclcpp::shutdown();
  return 0;
}