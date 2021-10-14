cmake_minimum_required(VERSION 3.11)

#
#   windows方法实现一些linux上的工具
#

project(crossutils)


add_executable(copythis ${CMAKE_CURRENT_SOURCE_DIR}/copythis.cpp)
add_executable(movethis ${CMAKE_CURRENT_SOURCE_DIR}/movethis.cpp)