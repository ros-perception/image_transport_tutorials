# Installation

Before starting any of the tutorials below, create a workspace and clone this repository so you can inspect and manipulate the code:

```
$ mkdir -p ~/image_transport_tutorials_ws/src
$ cd ~/image_transport_tutorials_ws/src
$ git clone https://github.com/ros-perception/image_transport_tutorials.git
```

Install needed dependencies:

```
$ cd ~/image_transport_tutorials_ws/
$ source /opt/ros/rolling/setup.bash
$ rosdep install -i --from-path src --rosdistro rolling -y
$ colcon build
```

Make sure to include the correct setup file (in the above example it is for rolling on Ubuntu and for bash).
