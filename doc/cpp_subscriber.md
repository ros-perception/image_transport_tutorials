# Writing a Simple Image Subscriber (C++)

Description: This tutorial shows how to create a subscriber node that will display an image on the screen.
By using the `image_transport` subscriber to subscribe to images, any image transport can be used at runtime.
To learn how to actually use a specific image transport, see the [next tutorial](different_transports.md).

Tutorial Level: Beginner

Take a look at [my_subscriber.cpp](../image_transport_tutorials/src/my_subscriber.cpp).

## The code explained

Now, let's break down the code piece by piece.

```cpp
#include "cv_bridge/cv_bridge.hpp"
#include "image_transport/image_transport.hpp"
#include "opencv2/highgui.hpp"
#include "rclcpp/logging.hpp"
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
```

These headers will allow us to subscribe to image messages, display images using OpenCV's simple GUI capabilities, and log errors.

```cpp
void imageCallback(const sensor_msgs::msg::Image::ConstSharedPtr & msg)
```

This is the callback function that will be called when a new image has arrived on the `camera/image` topic.
Although the image may have been sent in some arbitrary transport-specific message type, notice that the callback need only handle the normal `sensor_msgs/msg/Image` type.
All image encoding/decoding is handled automatically for you.

```cpp
try {
  cv::imshow("view", cv_bridge::toCvShare(msg, "bgr8")->image);
  cv::waitKey(10);
} catch (const cv_bridge::Exception & e) {
  auto logger = rclcpp::get_logger("my_subscriber");
  RCLCPP_ERROR(logger, "Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
}
```

The body of the callback.
We convert the ROS image message into an OpenCV image with BGR pixel encoding, then show it in a display window.

```cpp
rclcpp::Node::SharedPtr node = rclcpp::Node::make_shared("image_listener", options);
image_transport::ImageTransport it{*node};
```

We create an `ImageTransport` instance, initializing it with our node.

```cpp
image_transport::TransportHints hints{*node};
image_transport::Subscriber sub = it.subscribe("camera/image", 1, imageCallback, &hints);
```

Subscribe to the `camera/image` base topic.
`TransportHints` reads the `image_transport` node parameter to select the active transport at runtime (defaults to `"raw"`).
The actual ROS topic subscribed to depends on which transport is in use.
ROS will call the `imageCallback` function whenever a new image arrives.
The 2nd argument is the queue size.

`subscribe()` returns an `image_transport::Subscriber` object that you must hold on to until you want to unsubscribe.
When the Subscriber object is destructed, it will automatically unsubscribe from the `camera/image` base topic.

In just a few lines of code, we have written a ROS image viewer that can handle images in both raw and a variety of compressed forms.
