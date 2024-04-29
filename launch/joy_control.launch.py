import os

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node

def generate_launch_description():
  joy_driver = IncludeLaunchDescription(
    PythonLaunchDescriptionSource([os.path.join(
      get_package_share_directory('teleop_twist_joy'), 'launch'),
      '/teleop-launch.py']),
    launch_arguments={'joy_config': 'xbox'}.items(),
  )

  joy_control_node = Node(
    package='arm_joystick_control',
    executable='joy_control_node',
    name='joy_control_node'
  )

  return LaunchDescription([
    joy_driver,
    joy_control_node
  ])
