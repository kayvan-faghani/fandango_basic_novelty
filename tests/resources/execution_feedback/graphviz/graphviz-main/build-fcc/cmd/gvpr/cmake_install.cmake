# Install script for directory: /root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/cmd/gvpr

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

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/gvpr" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/gvpr")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/gvpr"
         RPATH [[$ORIGIN/../lib/graphviz:$ORIGIN/../lib]])
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/build-fcc/cmd/gvpr/gvpr")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/gvpr" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/gvpr")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/gvpr"
         OLD_RPATH "::::::::::::::::::::::::::::::::::::::"
         NEW_RPATH [[$ORIGIN/../lib/graphviz:$ORIGIN/../lib]])
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/llvm-strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/gvpr")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/man/man1" TYPE FILE FILES "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/build-fcc/cmd/gvpr/gvpr.1.gz")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/graphviz/gvpr" TYPE FILE FILES
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/cmd/gvpr/lib/addedges"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/cmd/gvpr/lib/addranks"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/cmd/gvpr/lib/addrings"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/cmd/gvpr/lib/anon"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/cmd/gvpr/lib/attr"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/cmd/gvpr/lib/bb"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/cmd/gvpr/lib/bbox"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/cmd/gvpr/lib/bipart"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/cmd/gvpr/lib/binduce"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/cmd/gvpr/lib/chkclusters"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/cmd/gvpr/lib/chkedges"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/cmd/gvpr/lib/cliptree"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/cmd/gvpr/lib/col"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/cmd/gvpr/lib/collapse"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/cmd/gvpr/lib/color"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/cmd/gvpr/lib/cycle"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/cmd/gvpr/lib/dechain"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/cmd/gvpr/lib/deghist"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/cmd/gvpr/lib/deledges"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/cmd/gvpr/lib/delmulti"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/cmd/gvpr/lib/delnodes"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/cmd/gvpr/lib/depath"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/cmd/gvpr/lib/dijkstra"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/cmd/gvpr/lib/flatten"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/cmd/gvpr/lib/get-layers-list"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/cmd/gvpr/lib/histogram"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/cmd/gvpr/lib/group"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/cmd/gvpr/lib/indent"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/cmd/gvpr/lib/knbhd"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/cmd/gvpr/lib/maxdeg"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/cmd/gvpr/lib/path"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/cmd/gvpr/lib/rotate"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/cmd/gvpr/lib/scale"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/cmd/gvpr/lib/scalexy"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/cmd/gvpr/lib/span"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/cmd/gvpr/lib/topon"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/cmd/gvpr/lib/treetoclust"
    )
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/build-fcc/cmd/gvpr/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
