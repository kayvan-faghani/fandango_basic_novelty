# Install script for directory: /root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/plugin

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/llvm-objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/build-fcc/plugin/ascii/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/build-fcc/plugin/core/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/build-fcc/plugin/devil/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/build-fcc/plugin/dot_layout/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/build-fcc/plugin/gd/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/build-fcc/plugin/gdiplus/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/build-fcc/plugin/gdk/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/build-fcc/plugin/gs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/build-fcc/plugin/kitty/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/build-fcc/plugin/lasi/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/build-fcc/plugin/neato_layout/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/build-fcc/plugin/pango/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/build-fcc/plugin/poppler/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/build-fcc/plugin/quartz/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/build-fcc/plugin/rsvg/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/build-fcc/plugin/vt/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/build-fcc/plugin/webp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/build-fcc/plugin/xlib/cmake_install.cmake")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/build-fcc/plugin/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
