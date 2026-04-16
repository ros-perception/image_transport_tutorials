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

#ifndef RESIZE_IMAGE_TRANSPORT__RESIZED_SUBSCRIBER_HPP_
#define RESIZE_IMAGE_TRANSPORT__RESIZED_SUBSCRIBER_HPP_

#include <string>

#include "image_transport/simple_subscriber_plugin.hpp"
#include "image_transport_tutorial_msgs/msg/resized_image.hpp"

namespace resize_image_transport
{
class ResizedSubscriber : public image_transport::SimpleSubscriberPlugin
  <image_transport_tutorial_msgs::msg::ResizedImage>
{
public:
  virtual ~ResizedSubscriber() {}

protected:
  virtual void internalCallback(
    const typename image_transport_tutorial_msgs::msg::ResizedImage::ConstSharedPtr & message,
    const Callback & user_cb);
};
}  // namespace resize_image_transport

#endif  // RESIZE_IMAGE_TRANSPORT__RESIZED_SUBSCRIBER_HPP_
