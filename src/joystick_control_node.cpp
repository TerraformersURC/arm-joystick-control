#include <chrono>

#include "arm_joystick_control/joystick_control_node.hpp"

using namespace std::chrono_literals;

ArmJoyStickControl::ArmJoyStickControl()
: rclcpp::Node("arm_joystick_control_node")
{
  _joystick_status_sub = this->create_subscription<ds4_driver_msgs::msg::Status>(
    "/status",
    rclcpp::SystemDefaultsQoS(),
    std::bind(&ArmJoyStickControl::joystickStatusSubCallback, this, std::placeholders::_1));

  _joystick_report_sub = this->create_subscription<ds4_driver_msgs::msg::Report>(
    "/raw_report",
    rclcpp::SensorDataQoS(),
    std::bind(&ArmJoyStickControl::joystickReportSubCallback, this, std::placeholders::_1));

  _monitor_timer = this->create_wall_timer(
    250ms, std::bind(&ArmJoyStickControl::subscriptionMonitor, this));
}

void ArmJoyStickControl::joystickStatusSubCallback(const ds4_driver_msgs::msg::Status& status_msg)
{
  _joystick_status_msg = status_msg;
}

void ArmJoyStickControl::joystickReportSubCallback(const ds4_driver_msgs::msg::Report& report_msg)
{
  _joystick_report_msg = report_msg;
}

void ArmJoyStickControl::subscriptionMonitor()
{
  std::stringstream info_stream;

  info_stream << '\n';
  info_stream << "Left stick x: " << static_cast<int>(_joystick_report_msg.left_analog_x) << '\n';
  info_stream << "Left stick y: " << static_cast<int>(_joystick_report_msg.left_analog_y) << '\n';
  info_stream << "Right stick x: " << static_cast<int>(_joystick_report_msg.right_analog_x) << '\n';
  info_stream << "Right stick y: " << static_cast<int>(_joystick_report_msg.right_analog_y) << '\n';

  RCLCPP_INFO_STREAM(this->get_logger(), info_stream.str());
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ArmJoyStickControl>());
  rclcpp::shutdown();
  return 0;
}
