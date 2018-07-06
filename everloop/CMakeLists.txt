project(matrix-hal-examples C CXX)
cmake_minimum_required(VERSION 2.8)

add_definitions(-std=c++11)

find_package(Threads)
FIND_LIBRARY(GFLAGS_LIB NAMES gflags)
message(STATUS "gflags found =>" "${GFLAGS_LIB}") 

add_executable(everloop_green everloop_green.cpp)
  set_property(TARGET everloop_green PROPERTY CXX_STANDARD 11)
  target_link_libraries(everloop_green matrix_creator_hal)
  target_link_libraries(everloop_green ${CMAKE_THREAD_LIBS_INIT})

add_executable(everloop_moving_dots everloop_moving_dots.cpp)
  set_property(TARGET everloop_moving_dots PROPERTY CXX_STANDARD 11)
  target_link_libraries(everloop_moving_dots matrix_creator_hal)
  target_link_libraries(everloop_moving_dots ${CMAKE_THREAD_LIBS_INIT})

add_executable(everloop_rainbow everloop_rainbow.cpp)
  set_property(TARGET everloop_rainbow PROPERTY CXX_STANDARD 11)
  target_link_libraries(everloop_rainbow matrix_creator_hal)
  target_link_libraries(everloop_rainbow ${CMAKE_THREAD_LIBS_INIT})

add_executable(everloop_yellow_purple everloop_yellow_purple.cpp)
  set_property(TARGET everloop_yellow_purple PROPERTY CXX_STANDARD 11)
  target_link_libraries(everloop_yellow_purple matrix_creator_hal)
  target_link_libraries(everloop_yellow_purple ${CMAKE_THREAD_LIBS_INIT})