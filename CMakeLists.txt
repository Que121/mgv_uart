cmake_minimum_required(VERSION 2.8.3)

project(mgv_uart)
set(CMAKE_CXX_STANDARD 14)

find_package(catkin_simple REQUIRED)
catkin_simple(ALL_DEPS_REQUIRED)

add_definitions(-std=c++11 -Wall)

#############
# LIBRARIES #
#############
cs_add_library(${PROJECT_NAME}
src/mgv_uart.cpp
)

############
# BINARIES #
############
cs_add_executable(mgv_uart_node
  src/mgv_uart_node.cpp
)
target_link_libraries(mgv_uart_node ${PROJECT_NAME})

##########
# EXPORT #
##########
cs_install()
cs_export()
