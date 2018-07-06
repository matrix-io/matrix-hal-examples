project(matrix-hal-examples C CXX)
cmake_minimum_required(VERSION 2.8)

add_definitions(-std=c++11)

find_package(Threads)
FIND_LIBRARY(GFLAGS_LIB NAMES gflags)

add_executable(mic_record_file mic_record_file.cpp)
  set_property(TARGET mic_record_file PROPERTY CXX_STANDARD 11)
  target_link_libraries(mic_record_file matrix_creator_hal)
  target_link_libraries(mic_record_file ${CMAKE_THREAD_LIBS_INIT})
  target_link_libraries(mic_record_file ${GFLAGS_LIB})

add_executable(mic_record_pipe mic_record_pipe.cpp)
  set_property(TARGET mic_record_pipe PROPERTY CXX_STANDARD 11)
  target_link_libraries(mic_record_pipe matrix_creator_hal)
  target_link_libraries(mic_record_pipe ${CMAKE_THREAD_LIBS_INIT})
  target_link_libraries(mic_record_pipe ${GFLAGS_LIB})

