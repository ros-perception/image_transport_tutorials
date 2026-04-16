# image_transport_tutorials

Tutorials for using [image_transport](https://github.com/ros-perception/image_transport) in ROS 2.

## Packages

| Package | Description |
|---|---|
| `image_transport_tutorial_msgs` | Custom message definitions (`ResizedImage.msg`) used by the resized transport plugin |
| `image_transport_tutorials` | C++ tutorial nodes: simple image publisher and subscriber |
| `resize_image_transport` | `image_transport` plugin that publishes/subscribes to half-resolution images |
| `image_transport_tutorials_py` | Python tutorial nodes: simple image publisher and subscriber |

## Installation

See [doc/installation.md](doc/installation.md).

## Tutorials

| Tutorial | Level |
|---|---|
| [Writing a Simple Image Publisher (C++)](doc/cpp_publisher.md) | Beginner |
| [Writing a Simple Image Subscriber (C++)](doc/cpp_subscriber.md) | Beginner |
| [Running the Publisher and Subscriber with Different Transports](doc/different_transports.md) | Beginner |
| [Writing a Custom Image Transport Plugin](doc/custom_plugin.md) | Intermediate |
| [Writing a Simple Image Publisher (Python)](doc/python_publisher.md) | Beginner |
| [Writing a Simple Image Subscriber (Python)](doc/python_subscriber.md) | Beginner |
