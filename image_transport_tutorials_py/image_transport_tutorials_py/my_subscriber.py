#!/usr/bin/env python3
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
from std_msgs.msg import String
from sensor_msgs.msg import Image, CameraInfo
from image_transport_py import ImageTransport
import logging
from cv_bridge import CvBridge
import cv2


logging.basicConfig(level=logging.DEBUG)
logger = logging.getLogger(__name__)


class MySubscriber(Node):
    def __init__(self):
        super().__init__("my_subscriber")

        image_transport2 = ImageTransport(
            "imagetransport_sub", image_transport="compressed"
        )
        s = image_transport2.subscribe("camera/image", 10, self.image_callback)
        logger.info(s)
        logger.info(s.get_topic())

        self.bridge = CvBridge()
        self.cv_image = None

    def image_callback(self, msg):
        logger.info("got a new image from frame id: %s" % msg.header.frame_id)


def main(args=None):
    rclpy.init(args=args)
    node = MySubscriber()

    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass

    # Destroy the node explicitly (optional)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()
