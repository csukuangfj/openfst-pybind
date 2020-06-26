cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(openfst-pybind)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "No CMAKE_BUILD_TYPE given, default to Release")
  set(CMAKE_BUILD_TYPE Debug CACHE STRING
    "Set the build type. Available values are: Debug Release RelWithDebInfo MinSizeRel"
    FORCE)
endif()

option(ENABLE_TESTS  "True to enable tests for openfst pybind"  ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(openfst)
include(pybind11)

add_subdirectory(openfst-pybind)

if (ENABLE_TESTS)
  enable_testing()
  add_subdirectory(tests)
else()
  message(STATUS "tests are disabled")
endif()
