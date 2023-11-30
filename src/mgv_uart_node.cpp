#include "src/mgv_uart/include/mgv_uart.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "mgv_uart");
  google::InitGoogleLogging(argv[0]);
  google::InstallFailureSignalHandler();

  ros::NodeHandle nh("");
  ros::NodeHandle nh_private("~");

  FLAGS_alsologtostderr = true;

  mgv_uart::PP_uart node(nh, nh_private);
  ROS_INFO("Initialized Mgv Uart node.");

  ros::spin();
  return 0;
}