#include "../include/ros2_udp_bridge/bridge.hpp"

using namespace lulav::comm::udp;

Bridge::Bridge(): 
Node("bridge"), _count(0)
{
    RCLCPP_INFO(get_logger(), "Initiating Bridge node.");

    init_ros();

    _reader_thread = std::make_shared<std::thread>(std::bind(&Bridge::reading_work, this));
}

Bridge::~Bridge()
{
  _keep_reading = false;

  if(_reader_thread->joinable())
    _reader_thread->join();
}

void Bridge::reading_work()
{
    printf("ros2_bridge: opening UDP sockets... ");
    _udp_client = std::make_shared<client>("0.0.0.0", CLIENT_PORT);
    _udp_server = std::make_shared<server>("0.0.0.0", SERVER_PORT);
    printf("Done. listening on port %d\n", SERVER_PORT);
    
    while(_keep_reading)
    {
      proto_to_ros();
    }
}

void Bridge::proto_to_ros()
{
      dynamics_node::msg::ControlSignal msg_ctrl;
      proto_spring::control_signal proto_ctrl;

      _udp_server->recv(_controller_buff, CONTROL_MESSAGE_SIZE);
      proto_ctrl.ParseFromArray(_controller_buff, CONTROL_MESSAGE_SIZE);
      msg_ctrl.u = proto_ctrl.u();

      _pub_controller.get()->publish(msg_ctrl);
}

void Bridge::init_ros()
{
    _sub_state = this->create_subscription<dynamics_node::msg::State>("/state",
                      1, std::bind(&Bridge::ros_to_proto, this, std::placeholders::_1));

    _pub_controller = this->create_publisher<dynamics_node::msg::ControlSignal>("/control_signal",
                      1);
}

void Bridge::ros_to_proto(const dynamics_node::msg::State::SharedPtr msg)
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