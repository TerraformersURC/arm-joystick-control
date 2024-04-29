#include "arm_joystick_control/joy_control_node.hpp"

using namespace std::chrono_literals;

ArmJoyControl::ArmJoyControl()
: rclcpp::Node("joy_control_node")
{
  _joy_sub = this->create_subscription<sensor_msgs::msg::Joy>(
    "/joy",
    rclcpp::SensorDataQoS(),
    std::bind(&ArmJoyControl::joySubCallback, this, std::placeholders::_1));

  _publisher_timer = this->create_wall_timer(
    100ms, std::bind(&ArmJoyControl::publishJointState, this));

  _joint_state_pub = this->create_publisher<sensor_msgs::msg::JointState>(
    "/arm_pose",
    rclcpp::SensorDataQoS());
}

void ArmJoyControl::joySubCallback(const sensor_msgs::msg::Joy& joy_msg)
{
  _joy_msg = joy_msg;
}

void ArmJoyControl::publishJointState()
{
  if (_joy_msg.axes.size() < 5)
    return;

  // auto left_analog_x {*_joy_msg.axes.begin()};
  auto left_analog_y {*(_joy_msg.axes.begin() + 1)};
  // auto right_analog_y {*(_joy_msg.axes.begin() + 2)};
  // auto right_analog_x {*(_joy_msg.axes.begin() + 3)};
  auto right_analog_y {*(_joy_msg.axes.begin() + 4)};

  sensor_msgs::msg::JointState pub_msg;
  pub_msg.set__position(
    {mapRange(left_analog_y, -1, 1, 0, 255), mapRange(right_analog_y, -1, 1, 0, 255)});

  _joint_state_pub->publish(pub_msg);
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ArmJoyControl>());
  rclcpp::shutdown();
  return 0;
}
