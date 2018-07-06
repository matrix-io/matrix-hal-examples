project(matrix-hal-examples C CXX)
cmake_minimum_required(VERSION 2.8)

add_definitions(-std=c++11)

find_package(Threads)
FIND_LIBRARY(GFLAGS_LIB NAMES gflags)


add_executable(gpio_io gpio_io.cpp)
  set_property(TARGET gpio_io PROPERTY CXX_STANDARD 11)
  target_link_libraries(gpio_io matrix_creator_hal)
  target_link_libraries(gpio_io ${CMAKE_THREAD_LIBS_INIT})

add_executable(gpio_pwm gpio_pwm.cpp)
  set_property(TARGET gpio_pwm PROPERTY CXX_STANDARD 11)
  target_link_libraries(gpio_pwm matrix_creator_hal)
  target_link_libraries(gpio_pwm ${CMAKE_THREAD_LIBS_INIT})

add_executable(gpio_servo gpio_servo.cpp)
  set_property(TARGET gpio_servo PROPERTY CXX_STANDARD 11)
  target_link_libraries(gpio_servo matrix_creator_hal)
  target_link_libraries(gpio_servo ${CMAKE_THREAD_LIBS_INIT})