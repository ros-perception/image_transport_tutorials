# Running the Simple Image Publisher and Subscriber with Different Transports

Description: This tutorial discusses running the simple image publisher and subscriber using multiple transports.

Tutorial Level: Beginner

## Running the publisher

In a previous tutorial we made a publisher node called `my_publisher`.
Now run the node with an image file as the command-line argument:

```
$ ros2 run image_transport_tutorials my_publisher path/to/some/image.jpg
```

To check that your node is running properly, list the topics being published:

```
$ ros2 topic list
```

You should see `/camera/image` in the output.
You can also get more information about the topic:

```
$ ros2 topic info /camera/image
```

The output should be:

```
Type: sensor_msgs/msg/Image
Publisher count: 1
Subscription count: 0
```

## Running the subscriber

In the last tutorial, we made a subscriber node called `my_subscriber`. Now run it:

```
$ ros2 run image_transport_tutorials my_subscriber
```

You should see a window pop up with the image you gave to the publisher.

## Finding available transports

`image_transport` searches your ROS installation for transport plugins at runtime and dynamically loads all that are built.
This affords you great flexibility in adding additional transports, but makes it unclear which are available on your system.
`image_transport` provides a `list_transports` executable for this purpose:

```
$ ros2 run image_transport list_transports
```

Which should show at minimum:

```
Declared transports:
image_transport/raw

Details:
----------
"image_transport/raw"
 - Provided by package: image_transport
 - Publisher:
      This is the default publisher. It publishes the Image as-is on the base topic.

 - Subscriber:
      This is the default pass-through subscriber for topics of type sensor_msgs/Image.
```

Depending on your setup, you may already have "compressed", "theora", or other transports available.
After building the packages in this repository, `image_transport/resized` will also be listed.

## Adding new transports

Our nodes are currently communicating raw `sensor_msgs/msg/Image` messages, so we are not gaining anything over using `rclcpp::Publisher` and `rclcpp::Subscriber`.
Let's change that by introducing a new transport.

The `compressed_image_transport` package provides plugins for the "compressed" transport, which sends images over the wire in either JPEG- or PNG-compressed form.
Notice that `compressed_image_transport` is not a dependency of your package; `image_transport` will automatically discover all transport plugins built in your ROS system.

The easiest way to add the "compressed" transport is to install the package:

```
$ sudo apt-get install ros-rolling-compressed-image-transport
```

Or install all the transport plugins at once:

```
$ sudo apt-get install ros-rolling-image-transport-plugins
```

But you can also build from source.

## Changing the transport used

Now let's start up a new subscriber, this one using compressed transport.
The key is that `image_transport` subscribers check the parameter `image_transport` for the name of a transport to use in place of "raw".
Let's set this parameter and start a subscriber node with name "compressed_listener":

```
$ ros2 run image_transport_tutorials my_subscriber --ros-args --remap __name:=compressed_listener -p image_transport:=compressed
```

You should see an identical image window pop up.

`compressed_listener` is listening to a separate topic carrying JPEG-compressed versions of the same images published on `/camera/image`.

## Changing transport-specific behavior

For a particular transport, we may want to tweak settings such as compression level, bit rate, etc.
Transport plugins can expose such settings through ROS parameters.
For example, `/camera/image/compressed` allows you to change the compression format and quality on the fly; see the package documentation for full details.

For now let's adjust the JPEG quality.
By default, the "compressed" transport uses JPEG compression at 80% quality.
Let's change it to 15%.
We can use the GUI, `rqt_reconfigure`, to change the quality:

```
$ ros2 run rqt_reconfigure rqt_reconfigure
```

Now pick `/image_publisher` in the drop-down menu and move the `jpeg_quality` slider down to 15%.
Do you see the compression artifacts in your second view window?

The `rqt_reconfigure` GUI has updated the ROS parameter `/image_publisher/jpeg_quality`.
You can verify this by running:

```
$ ros2 param get /image_publisher jpeg_quality
```

This should display 15.
