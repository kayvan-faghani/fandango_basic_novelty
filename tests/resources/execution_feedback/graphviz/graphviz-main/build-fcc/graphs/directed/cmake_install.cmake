# Install script for directory: /root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/graphviz/graphs/directed" TYPE FILE FILES
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/abstract.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/alf.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/arrows.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/awilliams.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/biological.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/clust.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/clust1.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/clust2.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/clust3.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/clust4.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/clust5.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/crazy.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/ctext.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/dfa.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/fig6.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/fsm.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/grammar.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/hashtable.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/honda-tokoro.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/japanese.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/jcctree.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/jsort.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/KW91.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/Latin1.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/ldbxtried.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/longflat.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/mike.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/NaN.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/nhg.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/oldarrows.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/pgram.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/pm2way.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/pmpipe.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/polypoly.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/proc3d.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/psfonttest.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/record2.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/records.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/rowe.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/russian.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/sdh.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/shells.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/states.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/structs.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/switch.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/table.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/train11.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/trapeziumlr.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/tree.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/triedds.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/try.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/unix.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/unix2.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/viewfile.gv"
    "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/graphs/directed/world.gv"
    )
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/root/fandango_basic_novelty/tests/resources/execution_feedback/graphviz/graphviz-main/build-fcc/graphs/directed/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
