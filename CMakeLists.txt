cmake_minimum_required(VERSION 3.8)
project(arm_joystick_control)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(PACKAGE_DEPENDENCIES
  ament_cmake
  rclcpp
  rclcpp_components
  ds4_driver
  ds4_driver_msgs
  sensor_msgs
)

foreach(dependency IN ITEMS ${PACKAGE_DEPENDENCIES})
  find_package(${dependency} REQUIRED)
endforeach()

add_executable(joystick_control_node src/joystick_control_node.cpp)
ament_target_dependencies(joystick_control_node ${PACKAGE_DEPENDENCIES})
target_include_directories(joystick_control_node
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

install(TARGETS
  joystick_control_node
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
