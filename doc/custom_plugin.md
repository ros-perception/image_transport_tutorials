# Writing a Custom Image Transport Plugin

Description: This tutorial shows how to write a custom `image_transport` plugin that publishes and subscribes to a custom message type.
The example plugin (`resize_image_transport`) decimates the image by a factor of 2 on publish, and restores it to the original size on subscribe.

Tutorial Level: Intermediate

The plugin spans two packages:

- **`image_transport_tutorial_msgs`** — defines the `ResizedImage.msg` message used on the wire:

  ```
  uint32 original_height
  uint32 original_width
  sensor_msgs/Image image
  ```

- **`resize_image_transport`** — implements the plugin itself.

## Publisher plugin

Take a look at [resized_publisher.hpp](../resize_image_transport/include/resize_image_transport/resized_publisher.hpp) and [resized_publisher.cpp](../resize_image_transport/src/resized_publisher.cpp).

The publisher inherits from `image_transport::SimplePublisherPlugin`, templated on the wire message type:

```cpp
class ResizedPublisher : public image_transport::SimplePublisherPlugin
  <image_transport_tutorial_msgs::msg::ResizedImage>
```

The `publish()` override receives a `sensor_msgs/msg/Image`, halves its resolution with OpenCV, and publishes a `ResizedImage`:

```cpp
void ResizedPublisher::publish(
  const sensor_msgs::msg::Image & message,
  const PublisherT & publisher) const
{
  // ...
  image_transport_tutorial_msgs::msg::ResizedImage resized_image;
  resized_image.original_height = cv_image.rows;
  resized_image.original_width  = cv_image.cols;
  resized_image.image = *(cv_bridge::CvImage(message.header, "bgr8", cv_image).toImageMsg());
  publisher->publish(resized_image);
}
```

## Subscriber plugin

Take a look at [resized_subscriber.hpp](../resize_image_transport/include/resize_image_transport/resized_subscriber.hpp) and [resized_subscriber.cpp](../resize_image_transport/src/resized_subscriber.cpp).

The subscriber inherits from `image_transport::SimpleSubscriberPlugin` and its `internalCallback()` override receives a `ResizedImage`, restores the original resolution, and forwards a `sensor_msgs/msg/Image` to the user callback:

```cpp
void ResizedSubscriber::internalCallback(
  const image_transport_tutorial_msgs::msg::ResizedImage::ConstSharedPtr & msg,
  const Callback & user_cb)
{
  // ...
  cv::resize(img_rsz, img_restored, cv::Size(msg->original_width, msg->original_height));
  cv_bridge::CvImage cv_img(msg->image.header, msg->image.encoding, img_restored);
  user_cb(cv_img.toImageMsg());
}
```

## Registering the plugin

[manifest.cpp](../resize_image_transport/src/manifest.cpp) registers both classes with pluginlib:

```cpp
PLUGINLIB_EXPORT_CLASS(resize_image_transport::ResizedPublisher,  image_transport::PublisherPlugin)
PLUGINLIB_EXPORT_CLASS(resize_image_transport::ResizedSubscriber, image_transport::SubscriberPlugin)
```

The plugin description file [resized_plugins.xml](../resize_image_transport/resized_plugins.xml) declares the transport name and wire message type so `image_transport` can discover the plugin at runtime.

## Using the resized transport

After building, run the publisher and subscriber with the resized transport:

```
$ ros2 run image_transport_tutorials my_publisher path/to/some/image.jpg
$ ros2 run image_transport_tutorials my_subscriber --ros-args -p image_transport:=resized
```
