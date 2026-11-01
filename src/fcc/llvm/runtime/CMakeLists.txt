cmake_minimum_required(VERSION 3.20)
project(Runtime)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 \
-Wredundant-decls -Wcast-align \
-Wmissing-include-dirs -Wswitch-default \
-Wextra -Wall -Winvalid-pch -Wredundant-decls -Wformat=2 \
-Wmissing-format-attribute -Wformat-nonliteral")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_library(Runtime SHARED
  LRuntime.cpp)

target_include_directories(Runtime PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(Runtime PROPERTIES COMPILE_FLAGS "-Werror")