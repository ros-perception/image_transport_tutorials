// Copyright 2021, Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef RESIZE_IMAGE_TRANSPORT__RESIZED_PUBLISHER_HPP_
#define RESIZE_IMAGE_TRANSPORT__RESIZED_PUBLISHER_HPP_

#include <string>

#include "sensor_msgs/msg/image.hpp"

#include "image_transport/simple_publisher_plugin.hpp"
#include "image_transport_tutorial_msgs/msg/resized_image.hpp"


namespace resize_image_transport
{
class ResizedPublisher : public image_transport::SimplePublisherPlugin
  <image_transport_tutorial_msgs::msg::ResizedImage>
{
protected:
  virtual void publish(
    const sensor_msgs::msg::Image & message,
    const PublisherT & publisher) const;
};
}  // namespace resize_image_transport
#endif  // RESIZE_IMAGE_TRANSPORT__RESIZED_PUBLISHER_HPP_
