project(matrix-hal-examples C CXX)
cmake_minimum_required(VERSION 2.8)

add_definitions(-std=c++11)

find_package(Threads)
find_library (FFTW_LIBRARIES NAMES fftw3f )
FIND_LIBRARY(WIRINGPI_LIB NAMES wiringPi)
FIND_LIBRARY(WIRINGPI_DEV_LIB NAMES wiringPiDev)
FIND_LIBRARY(CRYPT_LIB NAMES crypt)
FIND_LIBRARY(GFLAGS_LIB NAMES gflags)
message(STATUS "gflags found =>" "${GFLAGS_LIB}") 

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