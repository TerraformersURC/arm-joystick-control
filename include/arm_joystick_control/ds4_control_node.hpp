#include <rclcpp/rclcpp.hpp>

#include <ds4_driver_msgs/msg/status.hpp>
#include <ds4_driver_msgs/msg/report.hpp>
#include <sensor_msgs/msg/joint_state.hpp>

class ArmDS4Control : public rclcpp::Node {

public:
  ArmDS4Control();

private:
  void statusSubCallback(const ds4_driver_msgs::msg::Status& status_msg);
  void reportSubCallback(const ds4_driver_msgs::msg::Report& report_msg);
  void publishJointState();
  float mapRange(float value, float min_in = -1, float max_in = 1, float min_out = -1, float max_out = 1)
  {
    return (value - min_in) * (max_out - min_out) / (max_in - min_in) + min_out;
  };

  rclcpp::Subscription<ds4_driver_msgs::msg::Status>::SharedPtr _ds4_status_sub;
  rclcpp::Subscription<ds4_driver_msgs::msg::Report>::SharedPtr _ds4_report_sub;

  rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr _joint_state_pub;

  rclcpp::TimerBase::SharedPtr _publisher_timer;

  ds4_driver_msgs::msg::Status _ds4_status_msg;
  ds4_driver_msgs::msg::Report _ds4_report_msg;

};
