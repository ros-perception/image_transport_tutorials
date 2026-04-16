# Writing a Simple Image Subscriber (Python)

Description: This tutorial shows how to create a subscriber node that will receive the contents of the published image.
By using the `image_transport` subscriber to subscribe to images, any image transport can be used at runtime.

Tutorial Level: Beginner

Take a look at [my_subscriber.py](../image_transport_tutorials_py/image_transport_tutorials_py/my_subscriber.py).

To subscribe to images, use `ImageTransport` to create a subscription to the image topic.

## Steps

1. Import Necessary Modules:

```python
from image_transport_py import ImageTransport
import rclpy
from rclpy.node import Node
```

2. Initialize the Node and ImageTransport:

```python
class MySubscriber(Node):
    def __init__(self):
        super().__init__('my_subscriber')

        image_transport = ImageTransport(
            'imagetransport_sub', image_transport='compressed'
        )
        image_transport.subscribe('camera/image', 10, self.image_callback)
```

3. Handle Incoming Images:

```python
    def image_callback(self, msg):
        self.get_logger().info('got a new image from frame_id:=%s' % msg.header.frame_id)
```

## Running the subscriber

```
$ ros2 run image_transport_tutorials_py my_subscriber
```

## Transport Selection

By default, `image_transport` uses the `raw` transport.
You can specify a different transport by passing the `image_transport` parameter to `ImageTransport`.
Alternatively, you can use your own ROS 2 parameter file for the imagetransport node via the `launch_params_filepath` parameter.
