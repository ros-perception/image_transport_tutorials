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
find_package(OpenCV REQUIRED COMPONENTS highgui imgcodecs videoio)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)

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
target_link_libraries(my_subscriber PRIVATE
  cv_bridge::cv_bridge
  image_transport::image_transport
  opencv_highgui
  rclcpp::rclcpp
)

# add the publisher from video example
add_executable(publisher_from_video src/publisher_from_video.cpp)
target_link_libraries(publisher_from_video PRIVATE
  cv_bridge::cv_bridge
  image_transport::image_transport
  opencv_highgui
  opencv_videoio
  rclcpp::rclcpp
  "${sensor_msgs_TARGETS}"
  "${std_msgs_TARGETS}"
)

# Install executables
install(
  TARGETS my_publisher my_subscriber publisher_from_video
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
