#ifndef MGV_UART_
#define MGV_UART_

#include <ros/ros.h>
#include <string>
#include <thread>
#include <vector>
#include <serial/serial.h>
#include <trajectory_msgs/MultiDOFJointTrajectory.h>
#include <glob.h>
#include <glog/logging.h>

namespace mgv_uart
{
  class PP_uart
  {
  public:
    PP_uart(const ros::NodeHandle &nh, const ros::NodeHandle &nh_private);
    void ppUartEncode(trajectory_msgs::MultiDOFJointTrajectory *msg);
    void ppUartPublish();
    void ppUartCallback(trajectory_msgs::MultiDOFJointTrajectory *msg);
    void ppUartInit();

  private:
    ros::NodeHandle nh_;
    ros::NodeHandle nh_private_;
    // header
    std::string ppUartHeader = "pp";
    // 1: remote control 2: close the motor  rs 3: SL_planning
    std::string ppUartModel = "3";
    // all of data stream
    std::string ppUart_;
    // the final msg is sent
    std::vector<std::string> ppUartAll;

    serial::Serial sp;
    serial::Timeout to = serial::Timeout::simpleTimeout(100);

    ros::Subscriber ppUart_sub_;
  };
}

#endif