#include "cv_bridge/cv_bridge.h"
#include "image_transport/image_transport.hpp"
#include "opencv2/highgui.hpp"
#include "rclcpp/logging.hpp"
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"

/// Example Node ///

class NodeThatNeedsImgs : public rclcpp::Node {
public:
  NodeThatNeedsImgs() : Node("node_that_needs_imgs"){};

public:
  void InitializeImageTransport() {
    it_ = std::make_shared<image_transport::ImageTransport>(
        this->shared_from_this()); // https://answers.ros.org/question/353828/getting-a-nodesharedptr-from-this/
    it_img_sub_ = std::make_shared<image_transport::Subscriber>(
        it_->subscribe("camera/image", 1,
                       std::bind(&NodeThatNeedsImgs::ImgCallback, this,
                                 std::placeholders::_1)));
  }

private:
  void ImgCallback(sensor_msgs::msg::Image::ConstSharedPtr const &msg) {
    try {
      cv::imshow("view", cv_bridge::toCvShare(msg, "bgr8")->image);
      cv::waitKey(10);
    } catch (cv_bridge::Exception &e) {
      auto logger = rclcpp::get_logger("my_subscriber");
      RCLCPP_ERROR(logger, "Could not convert from '%s' to 'bgr8'.",
                   msg->encoding.c_str());
    }
  }

private:
  std::shared_ptr<image_transport::ImageTransport> it_;
  std::shared_ptr<image_transport::Subscriber> it_img_sub_;
};

/// Entry Point ///

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);

  auto node = std::make_shared<NodeThatNeedsImgs>();
  node->InitializeImageTransport();

  rclcpp::spin(node);
  rclcpp::shutdown();

  return 0;
}