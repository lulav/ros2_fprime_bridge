#include "../include/ros2_udp_bridge/bridge.hpp"

using namespace lulav::comm::udp;

Bridge::Bridge(): 
Node("bridge"), _count(0)
{
    RCLCPP_INFO(get_logger(), "Initiating Bridge node.");

    init_ros();
    
    RCLCPP_INFO(get_logger(), "ros2_bridge: opening UDP sockets... ");
    _udp_client = std::make_shared<client>("0.0.0.0", CLIENT_PORT);
    _udp_server = std::make_shared<server>("0.0.0.0", SERVER_PORT);
    RCLCPP_INFO(get_logger(), "Done. listening on port %d\n", SERVER_PORT);
}

Bridge::~Bridge()
{
  return;
}

void Bridge::init_ros()
{
    _sub_state = this->create_subscription<dynamics_node::msg::State>("/state",
                      1, std::bind(&Bridge::_ros_to_udp, this, std::placeholders::_1));

    _pub_controller = this->create_publisher<dynamics_node::msg::ControlSignal>("/control_signal",
                      1);
}


void Bridge::_udp_to_ros()
{
      dynamics_node::msg::ControlSignal ctrl_msg;
      proto_spring::control_signal proto_u;

      _udp_server->recv(_controller_buff, CONTROL_MESSAGE_SIZE);
      proto_u.ParseFromArray(_controller_buff, CONTROL_MESSAGE_SIZE);
      ctrl_msg.u = proto_u.u();

      _pub_controller.get()->publish(ctrl_msg);
}

void Bridge::_ros_to_udp(const dynamics_node::msg::State::SharedPtr msg)
{

    proto_spring::state proto_state;
    proto_state.Clear();

    proto_state.set_r(msg.get()->r);
    proto_state.set_v(msg.get()->v);

    proto_state.SerializeToArray(_dynamics_buff, STATE_MESSAGE_SIZE);

    _udp_client->send(_dynamics_buff, STATE_MESSAGE_SIZE);
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Bridge>());
  rclcpp::shutdown();
  return 0;
}