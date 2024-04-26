import os

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch_xml.launch_description_sources import XMLLaunchDescriptionSource
from launch_ros.actions import Node

def generate_launch_description():
  ds4_driver = IncludeLaunchDescription(
    XMLLaunchDescriptionSource([os.path.join(
      get_package_share_directory('ds4_driver'), 'launch'),
      '/ds4_driver.launch.xml']),
    launch_arguments={'use_standard_msgs': 'true'}.items(),
  )

  joystick_control_node = Node(
    package='arm_joystick_control',
    executable='joystick_control_node',
    name='joystick_control_node'
  )

  return LaunchDescription([
    ds4_driver,
    joystick_control_node
  ])
