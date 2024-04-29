#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <chrono>

#include "arm_joystick_control/ds4_control_node.hpp"

using namespace std::chrono_literals;

ArmDS4Control::ArmDS4Control()
: rclcpp::Node("ds4_control_node")
{
  _ds4_status_sub = this->create_subscription<ds4_driver_msgs::msg::Status>(
    "/status",
    rclcpp::SystemDefaultsQoS(),
    std::bind(&ArmDS4Control::statusSubCallback, this, std::placeholders::_1));

  _ds4_report_sub = this->create_subscription<ds4_driver_msgs::msg::Report>(
    "/raw_report",
    rclcpp::SensorDataQoS(),
    std::bind(&ArmDS4Control::reportSubCallback, this, std::placeholders::_1));

  _publisher_timer = this->create_wall_timer(
    250ms, std::bind(&ArmDS4Control::publishJointState, this));

  _joint_state_pub = this->create_publisher<sensor_msgs::msg::JointState>(
    "/arm_pose",
    rclcpp::SensorDataQoS());
}

void ArmDS4Control::statusSubCallback(const ds4_driver_msgs::msg::Status& status_msg)
{
  _ds4_status_msg = status_msg;
}

void ArmDS4Control::reportSubCallback(const ds4_driver_msgs::msg::Report& report_msg)
{
  _ds4_report_msg = report_msg;
}

void ArmDS4Control::publishJointState()
{
  std::stringstream info_stream;

  // int left_analog_x = _ds4_report_msg.left_analog_x;
  float left_analog_y = _ds4_report_msg.left_analog_y;
  // int right_analog_x = _ds4_report_msg.right_analog_x;
  float right_analog_y = _ds4_report_msg.right_analog_y;

  sensor_msgs::msg::JointState pub_msg;
  pub_msg.set__position({left_analog_y, right_analog_y});

  _joint_state_pub->publish(pub_msg);
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ArmDS4Control>());
  rclcpp::shutdown();
  return 0;
}
