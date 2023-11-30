#include "src/mgv_uart/include/mgv_uart.h"

namespace mgv_uart
{
  PP_uart::PP_uart(const ros::NodeHandle &nh,
                   const ros::NodeHandle &nh_private)
      : nh_(nh),
        nh_private_(nh_private)
  {
    ppUartInit();
    this->ppUart_sub_ = nh_.subscribe("command/trajectory", 1, PP_uart::ppUartCallback);
  } // TBD

  void PP_uart::ppUartInit()
  { // Init： PP3
    this->ppUart_ = this->ppUartHeader + this->ppUartModel;
    sp.setPort("/dev/ttyUSB0");
    sp.setBaudrate(115200);
    sp.setTimeout(to);
  }

  // ppXYZ/XYZW/XYZ/XYZ/XYZ/XYZ
  // velocities.linear, velocities.angular
  // translation, rotation,
  // accelerations.linear, accelerations.angular
  // geometry_msgs::Vector3 float64
  void PP_uart::ppUartEncode(trajectory_msgs::MultiDOFJointTrajectory *msg)
  {
    assert(msg != NULL);

    for (const trajectory_msgs::MultiDOFJointTrajectoryPoint &point_msg : msg->points)
    {
      // translation, rotation
      std::string ppUart_translation = std::to_string(std::round((point_msg.transforms[0].translation.x) * 1000)) + "," +
                                       std::to_string(std::round((point_msg.transforms[0].translation.y) * 1000)) + "," +
                                       std::to_string(std::round((point_msg.transforms[0].translation.z) * 1000)) + ",";
      std::string ppUart_rotation = std::to_string(std::round((point_msg.transforms[0].rotation.x) * 1000)) + "," +
                                    std::to_string(std::round((point_msg.transforms[0].rotation.y) * 1000)) + "," +
                                    std::to_string(std::round((point_msg.transforms[0].rotation.z) * 1000)) + "," +
                                    std::to_string(std::round((point_msg.transforms[0].rotation.w) * 1000)) + ",";
      // velocities.linear, velocities.angular
      std::string ppUart_velocitiesLinear = std::to_string(std::round((point_msg.velocities[0].linear.x) * 1000)) + "," +
                                            std::to_string(std::round((point_msg.velocities[0].linear.y) * 1000)) + "," +
                                            std::to_string(std::round((point_msg.velocities[0].linear.z) * 1000)) + ",";
      std::string ppUart_velocitiesAngular = std::to_string(std::round((point_msg.velocities[0].angular.x) * 1000)) + "," +
                                             std::to_string(std::round((point_msg.velocities[0].angular.y) * 1000)) + "," +
                                             std::to_string(std::round((point_msg.velocities[0].angular.z) * 1000)) + ",";
      // accelerations.linear, accelerations.angular
      std::string ppUart_accelerationsLinear = std::to_string(std::round((point_msg.accelerations[0].linear.x) * 1000)) + "," +
                                               std::to_string(std::round((point_msg.accelerations[0].linear.y) * 1000)) + "," +
                                               std::to_string(std::round((point_msg.accelerations[0].linear.z) * 1000)) + ",";
      std::string ppUart_accelerationsAngular = std::to_string(std::round((point_msg.accelerations[0].angular.x) * 1000)) + "," +
                                                std::to_string(std::round((point_msg.accelerations[0].angular.y) * 1000)) + "," +
                                                std::to_string(std::round((point_msg.accelerations[0].angular.z) * 1000));

      // geometry_msgs::Vector3 float64
      this->ppUart_ = this->ppUart_ +
                      (ppUart_translation + ppUart_rotation +
                       ppUart_velocitiesLinear + ppUart_velocitiesAngular +
                       ppUart_accelerationsLinear + ppUart_accelerationsAngular);

      this->ppUartAll.push_back(this->ppUart_);
    }

    ROS_INFO("Finished ppUartEncode !");
  }

  void PP_uart::ppUartPublish()
  {
    for (const std::string &ppUartPub_ : this->ppUartAll)
    {
      this->sp.write(ppUartPub_);
    }
    this->ppUartAll.clear();
    ROS_INFO("Finished ppUartPublish !");
  }

  void PP_uart::ppUartCallback(trajectory_msgs::MultiDOFJointTrajectory *msg)
  {
    this->ppUartEncode(msg);
    this->ppUartPublish();
  }
}