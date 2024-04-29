#include <memory>

#include <rclcpp/rclcpp.hpp>

#include <sensor_msgs/msg/joint_state.hpp>

void subscriptionCallback(const sensor_msgs::msg::JointState& msg)
{
  std::stringstream info_stream;

  info_stream << '\n';
  info_stream << "Received joint position values: " << '\n';

  for (const auto& joint_value: msg.position)
    info_stream << joint_value << '\n';
  info_stream << '\n';

  RCLCPP_INFO_STREAM(rclcpp::get_logger("demo_armpose_sub"), info_stream.str());
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  auto armpose_sub_node {std::make_shared<rclcpp::Node>("demo_armpose_sub")};

  auto joint_state_sub = armpose_sub_node->create_subscription<sensor_msgs::msg::JointState>(
    "/arm_pose",
    rclcpp::SystemDefaultsQoS(),
    std::bind(&subscriptionCallback, std::placeholders::_1));

  rclcpp::spin(armpose_sub_node);
  rclcpp::shutdown();
  return 0;
}
