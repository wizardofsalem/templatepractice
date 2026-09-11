cmake_minimum_required(VERSION 3.31)

project(templatepractice CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(templatepractice)

target_sources(templatepractice
  PRIVATE
  ./src/main.cpp
)

target_include_directories(templatepractice
PRIVATE
./include/)

