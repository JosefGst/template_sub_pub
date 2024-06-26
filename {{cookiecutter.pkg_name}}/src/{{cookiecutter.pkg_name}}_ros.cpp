/*
 * MIT License
 *
 * Copyright (c) 2024 Josef Gstoettner
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "ros/ros.h"
#include "{{cookiecutter.pkg_name}}/{{cookiecutter.pkg_name}}_ros.h"
#include "{{cookiecutter.pkg_name}}/reconfigure.h"
#include <string>

namespace ros_{{cookiecutter.pkg_name}}
{

  {{cookiecutter.class_name}}::{{cookiecutter.class_name}}() : nh_("~")
  {
    init_params();
    init_chatter();

    timer = nh_.createTimer(ros::Duration(1.0 / rate), &{{cookiecutter.class_name}}::timer_cb, this, false);
  }

  void {{cookiecutter.class_name}}::init_chatter()
  {
    chatter_pub = nh_.advertise<std_msgs::String>("/chatter", 1);
    ROS_INFO_STREAM("advertise to chatter topic on [" << chatter_pub.getTopic() << "]");

    cmd_vel_sub = nh_.subscribe("/cmd_vel", 1, &{{cookiecutter.class_name}}::cmd_vel_cb, this);
    ROS_INFO_STREAM("subscribe to topic on [" << cmd_vel_sub.getTopic() << "]");
  }

  void {{cookiecutter.class_name}}::init_params()
  {
    nh_.param("rate", rate, 10);
    nh_.param("pub_string", global_config.pub_string, std::string("Hello World!"));
  }

  void {{cookiecutter.class_name}}::timer_cb(const ros::TimerEvent &event)
  {
    string_msg.data = global_config.pub_string;
    chatter_pub.publish(string_msg);
  }

  void {{cookiecutter.class_name}}::cmd_vel_cb(const geometry_msgs::Twist &msg)
  {
    ROS_INFO_STREAM("cmd_vel: [" << msg << "]");
  }

}  // namespace ros_{{cookiecutter.pkg_name}}
