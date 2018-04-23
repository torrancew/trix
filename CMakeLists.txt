cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

project(
  trixos
  VERSION 0.0.1
  DESCRIPTION "A simple hobby OS"
  LANGUAGES C ASM
)

add_subdirectory(kernel)
