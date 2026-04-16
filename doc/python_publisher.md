# Writing a Simple Image Publisher (Python)

Description: This tutorial shows how to create a publisher node that will continually publish an image with random contents from Python.

Tutorial Level: Beginner

Take a look at [my_publisher.py](../image_transport_tutorials_py/image_transport_tutorials_py/my_publisher.py).

To publish images using `image_transport_py`, you create an `ImageTransport` object and use it to advertise an image topic.
The first parameter for `ImageTransport` is the image transport node's name, which must be unique in the namespace.

## Steps

1. Import Necessary Modules:

```python
from cv_bridge import CvBridge
from image_transport_py import ImageTransport
import numpy as np
import rclpy
from rclpy.node import Node
```

2. Initialize the Node and ImageTransport:

```python
class MyPublisher(Node):
    def __init__(self):
        super().__init__('my_publisher')

        self.image_transport = ImageTransport(
            'imagetransport_pub', image_transport='compressed'
        )
        self.img_pub = self.image_transport.advertise('camera/image', 10)

        self.bridge = CvBridge()

        timer_period = 0.5
        self.timer = self.create_timer(timer_period, self.timer_callback)
```

3. Publish Images in the Timer Callback:

```python
    def timer_callback(self):
        original = np.uint8(np.random.randint(0, 255, size=(640, 480, 3)))
        image_msg = self.bridge.cv2_to_imgmsg(original, encoding='bgr8')
        image_msg.header.stamp = self.get_clock().now().to_msg()
        image_msg.header.frame_id = 'camera'

        self.img_pub.publish(image_msg)
        self.get_logger().info('Publishing image')
```

## Running the publisher

```
$ ros2 run image_transport_tutorials_py my_publisher
```
