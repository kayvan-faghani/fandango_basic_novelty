cmake_minimum_required(VERSION 3.5)
project(bf-llvm)

find_package(LLVM REQUIRED CONFIG)

# runtime library
add_subdirectory(runtime)

# instrumentation pass, analysis pass, fcc
add_subdirectory(compiler)

# mylibc
add_subdirectory(mylibc)