#include <rclcpp/rclcpp.hpp>

#include <ds4_driver_msgs/msg/status.hpp>
#include <ds4_driver_msgs/msg/report.hpp>

class ArmJoyStickControl : public rclcpp::Node {

public:
  ArmJoyStickControl();

private:
  void joystickStatusSubCallback(const ds4_driver_msgs::msg::Status& status_msg);
  void joystickReportSubCallback(const ds4_driver_msgs::msg::Report& report_msg);
  void subscriptionMonitor();

  rclcpp::Subscription<ds4_driver_msgs::msg::Status>::SharedPtr _joystick_status_sub;
  rclcpp::Subscription<ds4_driver_msgs::msg::Report>::SharedPtr _joystick_report_sub;

  rclcpp::TimerBase::SharedPtr _monitor_timer;

  ds4_driver_msgs::msg::Status _joystick_status_msg;
  ds4_driver_msgs::msg::Report _joystick_report_msg;
};
