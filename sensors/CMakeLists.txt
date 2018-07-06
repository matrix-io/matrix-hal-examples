project(matrix-hal-examples C CXX)
cmake_minimum_required(VERSION 2.8)

add_definitions(-std=c++11)

find_package(Threads)
FIND_LIBRARY(GFLAGS_LIB NAMES gflags)

add_executable(humidity_sensor humidity_sensor.cpp)
  set_property(TARGET humidity_sensor PROPERTY CXX_STANDARD 11)
  target_link_libraries(humidity_sensor matrix_creator_hal)
  target_link_libraries(humidity_sensor ${CMAKE_THREAD_LIBS_INIT})

add_executable(imu_sensor imu_sensor.cpp)
  set_property(TARGET imu_sensor PROPERTY CXX_STANDARD 11)
  target_link_libraries(imu_sensor matrix_creator_hal)
  target_link_libraries(imu_sensor ${CMAKE_THREAD_LIBS_INIT})

add_executable(pressure_sensor pressure_sensor.cpp)
  set_property(TARGET pressure_sensor PROPERTY CXX_STANDARD 11)
  target_link_libraries(pressure_sensor matrix_creator_hal)
  target_link_libraries(pressure_sensor ${CMAKE_THREAD_LIBS_INIT})

add_executable(uv_sensor uv_sensor.cpp)
  set_property(TARGET uv_sensor PROPERTY CXX_STANDARD 11)
  target_link_libraries(uv_sensor matrix_creator_hal)
  target_link_libraries(uv_sensor ${CMAKE_THREAD_LIBS_INIT})