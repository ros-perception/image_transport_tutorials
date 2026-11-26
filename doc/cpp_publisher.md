# Writing a Simple Image Publisher (C++)

Description: This tutorial shows how to create a publisher node that will continually publish an image.

Tutorial Level: Beginner

Take a look at [my_publisher.cpp](../image_transport_tutorials/src/my_publisher.cpp).

## The code explained

Now, let's break down the code piece by piece.
For lines not explained here, review [Writing a Simple Publisher and Subscriber (C++)](https://docs.ros.org/en/rolling/Tutorials/Beginner-Client-Libraries/Writing-A-Simple-Cpp-Publisher-And-Subscriber.html).

```cpp
#include "cv_bridge/cv_bridge.hpp"
#include "image_transport/image_transport.hpp"
#include "opencv2/core/mat.hpp"
#include "opencv2/imgcodecs.hpp"
#include "rclcpp/rclcpp.hpp"
```

These headers will allow us to load an image using OpenCV, convert it to the ROS message format, and publish it.

```cpp
rclcpp::Node::SharedPtr node = rclcpp::Node::make_shared("image_publisher", options);
image_transport::ImageTransport it{*node};
```

We create an `ImageTransport` instance, initializing it with our node.
We use methods of `ImageTransport` to create image publishers and subscribers, much as we use methods of `Node` to create generic ROS publishers and subscribers.

```cpp
image_transport::Publisher pub = it.advertise("camera/image", 1);
```

Advertise that we are going to be publishing images on the base topic `camera/image`.
Depending on whether more plugins are built, additional (per-plugin) topics derived from the base topic may also be advertised.
The second argument is the size of our publishing queue.

`advertise()` returns an `image_transport::Publisher` object, which serves two purposes:
1. It contains a `publish()` method that lets you publish images onto the base topic it was created with
2. When it goes out of scope, it will automatically unadvertise

```cpp
cv::Mat image = cv::imread(argv[1], cv::IMREAD_COLOR);
std_msgs::msg::Header hdr;
sensor_msgs::msg::Image::SharedPtr msg = cv_bridge::CvImage(hdr, "bgr8", image).toImageMsg();
```

We load a user-specified (on the command line) color image from disk using OpenCV, then convert it to the ROS type `sensor_msgs/msg/Image`.

```cpp
rclcpp::WallRate loop_rate(5);
rclcpp::executors::SingleThreadedExecutor executor;
executor.add_node(node);
while (rclcpp::ok()) {
  pub.publish(msg);
  executor.spin_some();
  loop_rate.sleep();
}
```

We broadcast the image to anyone connected to one of our topics, exactly as we would have using an `rclcpp::Publisher`.

## Adding video stream from a webcam

The example above requires a path to an image file to be added as a command line parameter.
This image will be converted and sent as a message to an image subscriber.
In most cases, however, this is not a very practical example as you are often required to handle streaming data.
(For example: multiple webcams mounted on a robot record the scene around it and you have to pass the image data to some other node for further analysis).

The publisher example can be modified quite easily to make it work with a video device supported by `cv::VideoCapture` (in case it is not, you have to handle it accordingly).
Take a look at [publisher_from_video.cpp](../image_transport_tutorials/src/publisher_from_video.cpp) to see how a video device can be passed in as a command line argument and used as the image source.

If you have a single device, you do not need to do the whole routine with passing a command line argument.
In this case, you can hard-code the index/address of the device and directly pass it to the video capturing structure in OpenCV (example: `cv::VideoCapture(0)` if `/dev/video0` is used).
Multiple checks are also included here to make sure that the publisher does not break if the camera is shut down.
If the retrieved frame from the video device is not empty, it will then be converted to a ROS message which will be published by the publisher.
