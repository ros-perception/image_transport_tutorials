cmake_minimum_required(VERSION 3.8)
project(image_transport_tutorials)

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(image_transport REQUIRED)
find_package(OpenCV REQUIRED COMPONENTS highgui imgcodecs imgproc videoio)
find_package(pluginlib REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)

include_directories(include)

# add the resized image message
set(msg_files
  "msg/ResizedImage.msg"
)
rosidl_generate_interfaces(${PROJECT_NAME}
  ${msg_files}
  DEPENDENCIES sensor_msgs
)

rosidl_get_typesupport_target(cpp_typesupport_target "${PROJECT_NAME}" "rosidl_typesupport_cpp")

# add the publisher example
add_executable(my_publisher src/my_publisher.cpp)
target_link_libraries(my_publisher PRIVATE
  cv_bridge::cv_bridge
  image_transport::image_transport
  opencv_imgcodecs
  rclcpp::rclcpp
)

# add the subscriber example
add_executable(my_subscriber src/my_subscriber.cpp)
target_link_libraries(my_subscriber
  cv_bridge::cv_bridge
  image_transport::image_transport
  opencv_highgui
  rclcpp::rclcpp
)

# add the plugin example
add_library(resized_plugins src/manifest.cpp src/resized_publisher.cpp src/resized_subscriber.cpp)
target_link_libraries(resized_plugins
  "${cpp_typesupport_target}"
  cv_bridge::cv_bridge
  image_transport::image_transport
  opencv_imgproc
  pluginlib::pluginlib
  rclcpp::rclcpp
  "${sensor_msgs_TARGETS}"
)

# add the publisher from video example
add_executable(publisher_from_video src/publisher_from_video.cpp)
target_link_libraries(publisher_from_video
  cv_bridge::cv_bridge
  image_transport::image_transport
  opencv_highgui
  opencv_videoio
  rclcpp::rclcpp
  "${sensor_msgs_TARGETS}"
  "${std_msgs_TARGETS}"
)

# Install plugin descriptions
pluginlib_export_plugin_description_file(${PROJECT_NAME} resized_plugins.xml)

# Install executables
install(
  TARGETS my_publisher my_subscriber resized_plugins publisher_from_video
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

# Install include directories
install(
  DIRECTORY include/
  DESTINATION include/${PROJECT_NAME}
)

ament_export_include_directories(include)
ament_export_dependencies(cv_bridge image_transport pluginlib rosidl_default_runtime rclcpp sensor_msgs std_msgs)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
