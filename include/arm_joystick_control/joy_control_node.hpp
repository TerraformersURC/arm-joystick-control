#include <rclcpp/rclcpp.hpp>

#include <sensor_msgs/msg/joy.hpp>
#include <sensor_msgs/msg/joint_state.hpp>

class ArmJoyControl : public rclcpp::Node {

public:
  ArmJoyControl();

private:
  void joySubCallback(const sensor_msgs::msg::Joy& joy_msg);
  void publishJointState();
  float mapRange(float value, float min_in = -1, float max_in = 1, float min_out = -1, float max_out = 1)
  {
    return (value - min_in) * (max_out - min_out) / (max_in - min_in) + min_out;
  };

  rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr _joy_sub;

  rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr _joint_state_pub;

  rclcpp::TimerBase::SharedPtr _publisher_timer;

  sensor_msgs::msg::Joy _joy_msg;

};
