cmake_minimum_required(VERSION 3.8)
project(resize_image_transport)

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
find_package(image_transport_tutorial_msgs REQUIRED)
find_package(OpenCV REQUIRED COMPONENTS imgproc)
find_package(pluginlib REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)

add_library(${PROJECT_NAME} SHARED
  src/manifest.cpp
  src/resized_publisher.cpp
  src/resized_subscriber.cpp
)
target_include_directories(${PROJECT_NAME} PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:include/${PROJECT_NAME}>"
)
target_link_libraries(${PROJECT_NAME}
  PUBLIC
    image_transport::image_transport
    image_transport_tutorial_msgs::image_transport_tutorial_msgs
    ${sensor_msgs_TARGETS}
  PRIVATE
    cv_bridge::cv_bridge
    opencv_imgproc
    pluginlib::pluginlib
    rclcpp::rclcpp
)

pluginlib_export_plugin_description_file(image_transport resized_plugins.xml)

install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

install(
  DIRECTORY include/
  DESTINATION include/${PROJECT_NAME}
)

ament_export_targets(${PROJECT_NAME} HAS_LIBRARY_TARGET)
ament_export_dependencies(
  image_transport
  image_transport_tutorial_msgs
  sensor_msgs
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
