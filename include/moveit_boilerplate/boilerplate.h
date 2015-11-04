/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2015, PickNik LLC
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of PickNik LLC nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/

/* Author: Dave Coleman <dave@dav.ee>
   Desc:   Base class for using MoveIt! in C++
*/

#ifndef MOVEIT_BOILERPLATE__MOVEIT_BOILERPLATE
#define MOVEIT_BOILERPLATE__MOVEIT_BOILERPLATE

// ROS
#include <ros/ros.h>
#include <tf/transform_listener.h>

// MoveIt
#include <moveit/planning_scene_monitor/planning_scene_monitor.h>

// Visual tools
#include <moveit_visual_tools/moveit_visual_tools.h>

// MoveItManipulation
#include <moveit_boilerplate/namespaces.h>
#include <moveit_boilerplate/remote_control.h>
#include <moveit_boilerplate/execution_interface.h>

// ROS parameter loading
#include <ros_param_shortcuts/ros_param_shortcuts.h>

namespace moveit_boilerplate
{
static const std::string ROBOT_DESCRIPTION = "robot_description";

class Boilerplate
{
public:
  /**
   * \brief Constructor
   */
  Boilerplate();

  /**
   * \brief Connect to the MoveIt! planning scene messages
   */
  bool loadPlanningSceneMonitor(const std::string &joint_state_topic);

  /**
   * \brief Load visual tools
   */
  void loadVisualTools();
  
  /**
   * \brief Use the planning scene to get the robot's current state
   */
  moveit::core::RobotStatePtr getCurrentState();

protected:

  // A shared node handle
  ros::NodeHandle nh_;

  // Transform
  boost::shared_ptr<tf::TransformListener> tf_;

  // For visualizing things in rviz
  mvt::MoveItVisualToolsPtr visual_tools_;

  // Core MoveIt components
  robot_model_loader::RobotModelLoaderPtr robot_model_loader_;
  robot_model::RobotModelPtr robot_model_;
  planning_scene::PlanningScenePtr planning_scene_;
  psm::PlanningSceneMonitorPtr planning_scene_monitor_;

  // For executing joint and cartesian trajectories
  ExecutionInterfacePtr execution_interface_;

  // Allocated memory for robot state
  moveit::core::RobotStatePtr current_state_;

  // Remote control for dealing with GUIs
  RemoteControlPtr remote_control_;

};  // end class

}  // end namespace

#endif