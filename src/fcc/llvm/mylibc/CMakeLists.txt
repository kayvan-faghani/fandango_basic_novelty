# We're building fcc with `nolibc-fcc` here, which is a version of fcc
# that doesn't link against our instrumented libc (mylibc), because
# we are just building it here.

cmake_minimum_required(VERSION 3.20)
project(mylibc)

# Place the final product in the top-level output directory
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_C_COMPILER "${CMAKE_BINARY_DIR}/compiler/nolibc-fcc")
set(CMAKE_CXX_COMPILER "${CMAKE_BINARY_DIR}/compiler/nolibc-fcc++")

add_library(mylibc STATIC mylibc.c)
target_include_directories(mylibc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
#set_target_properties(mylibc PROPERTIES COMPILE_FLAGS "-Werror")

add_custom_target(MakeSureFCCExists ALL DEPENDS ${CMAKE_BINARY_DIR}/compiler/nolibc-fcc InstrumentationPass)
add_dependencies(mylibc MakeSureFCCExists)