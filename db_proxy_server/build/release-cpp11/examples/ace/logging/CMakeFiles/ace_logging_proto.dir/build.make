# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ys/project/src9-9/muduo-2.0.0-beta

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ys/project/src9-9/build/release-cpp11

# Include any dependencies generated for this target.
include examples/ace/logging/CMakeFiles/ace_logging_proto.dir/depend.make

# Include the progress variables for this target.
include examples/ace/logging/CMakeFiles/ace_logging_proto.dir/progress.make

# Include the compile flags for this target's objects.
include examples/ace/logging/CMakeFiles/ace_logging_proto.dir/flags.make

examples/ace/logging/logrecord.pb.cc: /home/ys/project/src9-9/muduo-2.0.0-beta/examples/ace/logging/logrecord.proto
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ys/project/src9-9/build/release-cpp11/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating logrecord.pb.cc, logrecord.pb.h"
	cd /home/ys/project/src9-9/build/release-cpp11/examples/ace/logging && protoc --cpp_out . /home/ys/project/src9-9/muduo-2.0.0-beta/examples/ace/logging/logrecord.proto -I/home/ys/project/src9-9/muduo-2.0.0-beta/examples/ace/logging

examples/ace/logging/logrecord.pb.h: examples/ace/logging/logrecord.pb.cc

examples/ace/logging/CMakeFiles/ace_logging_proto.dir/logrecord.pb.cc.o: examples/ace/logging/CMakeFiles/ace_logging_proto.dir/flags.make
examples/ace/logging/CMakeFiles/ace_logging_proto.dir/logrecord.pb.cc.o: examples/ace/logging/logrecord.pb.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ys/project/src9-9/build/release-cpp11/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/ace/logging/CMakeFiles/ace_logging_proto.dir/logrecord.pb.cc.o"
	cd /home/ys/project/src9-9/build/release-cpp11/examples/ace/logging && g++   $(CXX_DEFINES) $(CXX_FLAGS) -Wno-conversion -Wno-shadow -o CMakeFiles/ace_logging_proto.dir/logrecord.pb.cc.o -c /home/ys/project/src9-9/build/release-cpp11/examples/ace/logging/logrecord.pb.cc

examples/ace/logging/CMakeFiles/ace_logging_proto.dir/logrecord.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ace_logging_proto.dir/logrecord.pb.cc.i"
	cd /home/ys/project/src9-9/build/release-cpp11/examples/ace/logging && g++  $(CXX_DEFINES) $(CXX_FLAGS) -Wno-conversion -Wno-shadow -E /home/ys/project/src9-9/build/release-cpp11/examples/ace/logging/logrecord.pb.cc > CMakeFiles/ace_logging_proto.dir/logrecord.pb.cc.i

examples/ace/logging/CMakeFiles/ace_logging_proto.dir/logrecord.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ace_logging_proto.dir/logrecord.pb.cc.s"
	cd /home/ys/project/src9-9/build/release-cpp11/examples/ace/logging && g++  $(CXX_DEFINES) $(CXX_FLAGS) -Wno-conversion -Wno-shadow -S /home/ys/project/src9-9/build/release-cpp11/examples/ace/logging/logrecord.pb.cc -o CMakeFiles/ace_logging_proto.dir/logrecord.pb.cc.s

examples/ace/logging/CMakeFiles/ace_logging_proto.dir/logrecord.pb.cc.o.requires:
.PHONY : examples/ace/logging/CMakeFiles/ace_logging_proto.dir/logrecord.pb.cc.o.requires

examples/ace/logging/CMakeFiles/ace_logging_proto.dir/logrecord.pb.cc.o.provides: examples/ace/logging/CMakeFiles/ace_logging_proto.dir/logrecord.pb.cc.o.requires
	$(MAKE) -f examples/ace/logging/CMakeFiles/ace_logging_proto.dir/build.make examples/ace/logging/CMakeFiles/ace_logging_proto.dir/logrecord.pb.cc.o.provides.build
.PHONY : examples/ace/logging/CMakeFiles/ace_logging_proto.dir/logrecord.pb.cc.o.provides

examples/ace/logging/CMakeFiles/ace_logging_proto.dir/logrecord.pb.cc.o.provides.build: examples/ace/logging/CMakeFiles/ace_logging_proto.dir/logrecord.pb.cc.o

# Object files for target ace_logging_proto
ace_logging_proto_OBJECTS = \
"CMakeFiles/ace_logging_proto.dir/logrecord.pb.cc.o"

# External object files for target ace_logging_proto
ace_logging_proto_EXTERNAL_OBJECTS =

lib/libace_logging_proto.a: examples/ace/logging/CMakeFiles/ace_logging_proto.dir/logrecord.pb.cc.o
lib/libace_logging_proto.a: examples/ace/logging/CMakeFiles/ace_logging_proto.dir/build.make
lib/libace_logging_proto.a: examples/ace/logging/CMakeFiles/ace_logging_proto.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library ../../../lib/libace_logging_proto.a"
	cd /home/ys/project/src9-9/build/release-cpp11/examples/ace/logging && $(CMAKE_COMMAND) -P CMakeFiles/ace_logging_proto.dir/cmake_clean_target.cmake
	cd /home/ys/project/src9-9/build/release-cpp11/examples/ace/logging && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ace_logging_proto.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/ace/logging/CMakeFiles/ace_logging_proto.dir/build: lib/libace_logging_proto.a
.PHONY : examples/ace/logging/CMakeFiles/ace_logging_proto.dir/build

examples/ace/logging/CMakeFiles/ace_logging_proto.dir/requires: examples/ace/logging/CMakeFiles/ace_logging_proto.dir/logrecord.pb.cc.o.requires
.PHONY : examples/ace/logging/CMakeFiles/ace_logging_proto.dir/requires

examples/ace/logging/CMakeFiles/ace_logging_proto.dir/clean:
	cd /home/ys/project/src9-9/build/release-cpp11/examples/ace/logging && $(CMAKE_COMMAND) -P CMakeFiles/ace_logging_proto.dir/cmake_clean.cmake
.PHONY : examples/ace/logging/CMakeFiles/ace_logging_proto.dir/clean

examples/ace/logging/CMakeFiles/ace_logging_proto.dir/depend: examples/ace/logging/logrecord.pb.cc
examples/ace/logging/CMakeFiles/ace_logging_proto.dir/depend: examples/ace/logging/logrecord.pb.h
	cd /home/ys/project/src9-9/build/release-cpp11 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ys/project/src9-9/muduo-2.0.0-beta /home/ys/project/src9-9/muduo-2.0.0-beta/examples/ace/logging /home/ys/project/src9-9/build/release-cpp11 /home/ys/project/src9-9/build/release-cpp11/examples/ace/logging /home/ys/project/src9-9/build/release-cpp11/examples/ace/logging/CMakeFiles/ace_logging_proto.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/ace/logging/CMakeFiles/ace_logging_proto.dir/depend

