#!/usr/bin/env python3
# Copyright 2024, Open Source Robotics Foundation, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


import rclpy
from rclpy.node import Node
from image_transport_py import ImageTransport
from cv_bridge import CvBridge
import logging
import numpy as np

logging.basicConfig(level=logging.DEBUG)
logger = logging.getLogger(__name__)


class MyPublisher(Node):
    def __init__(self):
        super().__init__("my_publisher")

        self.image_transport = ImageTransport("imagetransport_pub", image_transport="compressed")
        self.img_pub = self.image_transport.advertise("camera/image", 10)

        self.bridge = CvBridge()

        timer_period = 0.5
        self.timer = self.create_timer(timer_period, self.timer_callback)

    def timer_callback(self):
        original = np.uint8(np.random.randint(0, 255, size=(640, 480)))
        image_msg = self.bridge.cv2_to_imgmsg(original)
        image_msg.header.stamp = self.get_clock().now().to_msg()
        image_msg.header.frame_id = "camera"

        self.img_pub.publish(image_msg)
        self.get_logger().info("Publishing image")


def main(args=None):
    rclpy.init(args=args)
    node = MyPublisher()

    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass

    # Destroy the node explicitly (optional)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()
