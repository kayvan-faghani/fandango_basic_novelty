project(bf-llvm-pass)
cmake_minimum_required(VERSION 3.20)
find_package(LLVM REQUIRED CONFIG)


message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

message(STATUS "LLVM definitions ${LLVM_DEFINITIONS}")
message(STATUS "LLVM Include Dir: ${LLVM_INCLUDE_DIRS}")
message(STATUS "LLVM LIBRARY Dir: ${LLVM_LIBRARY_DIRS}")

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})

# *** InstrumentationPass ***
add_library(InstrumentationPass MODULE
    InstrumentationPass.cpp
    InstrumentationHelpers.cpp
    Runtime.cpp
)

# LLVM is (typically) built with no C++ RTTI. We need to match that;
# otherwise, we'll get linker errors about missing RTTI data.
set_target_properties(InstrumentationPass PROPERTIES
    COMPILE_FLAGS "-fno-rtti"
)

# Get proper shared-library behavior (where symbols are not necessarily
# resolved when the shared library is linked) on OS X.
if(APPLE)
    set_target_properties(InstrumentationPass PROPERTIES
        LINK_FLAGS "-undefined dynamic_lookup"
    )
endif(APPLE)

# *** AnalysisPass ***
add_library(AnalysisPass MODULE
    AnalysisPass.cpp
    InstrumentationHelpers.cpp
)

# LLVM is (typically) built with no C++ RTTI. We need to match that;
# otherwise, we'll get linker errors about missing RTTI data.
set_target_properties(AnalysisPass PROPERTIES
    COMPILE_FLAGS "-fno-rtti -g"
)

# Get proper shared-library behavior (where symbols are not necessarily
# resolved when the shared library is linked) on OS X.
if(APPLE)
    set_target_properties(AnalysisPass PROPERTIES
        LINK_FLAGS "-undefined dynamic_lookup"
    )
endif(APPLE)

# *** fcc ***

configure_file("fcc.in" "fcc" @ONLY)
execute_process(COMMAND chmod +x ${CMAKE_CURRENT_BINARY_DIR}/fcc)

configure_file("nolibc-fcc.in" "nolibc-fcc" @ONLY)
execute_process(COMMAND chmod +x ${CMAKE_CURRENT_BINARY_DIR}/nolibc-fcc)

configure_file("fcc++.in" "fcc++" @ONLY)
execute_process(COMMAND chmod +x ${CMAKE_CURRENT_BINARY_DIR}/fcc++)

configure_file("nolibc-fcc++.in" "nolibc-fcc++" @ONLY)
execute_process(COMMAND chmod +x ${CMAKE_CURRENT_BINARY_DIR}/nolibc-fcc++)

configure_file("fan.in" "fan" @ONLY)
execute_process(COMMAND chmod +x ${CMAKE_CURRENT_BINARY_DIR}/fan)