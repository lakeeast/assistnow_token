cmake_minimum_required(VERSION 3.0.0)
file(GLOB_RECURSE sources *.cpp)
project(assistnow_token VERSION 0.1.0)
add_executable(assistnow_token ${sources})

