cmake_minimum_required(VERSION 3.0)
project(threadpool)

set(cmake_color_makefile ON)
set(cmake_verbose_makefile OFF)
set(cmake_include_current_dir TRUE)
set(cmake_allow_loose_loop_constructs TRUE)

set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake"
  )

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE MinSizeRel)
endif()

include(platform)
include(target)

add_subdirectory(test)

message(STATUS "BUILD TYPE: ${CMAKE_BUILD_TYPE}")
