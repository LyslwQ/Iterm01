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
include examples/protobuf/resolver/CMakeFiles/resolver_proto.dir/depend.make

# Include the progress variables for this target.
include examples/protobuf/resolver/CMakeFiles/resolver_proto.dir/progress.make

# Include the compile flags for this target's objects.
include examples/protobuf/resolver/CMakeFiles/resolver_proto.dir/flags.make

examples/protobuf/resolver/resolver.pb.cc: /home/ys/project/src9-9/muduo-2.0.0-beta/examples/protobuf/resolver/resolver.proto
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ys/project/src9-9/build/release-cpp11/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating resolver.pb.cc, resolver.pb.h"
	cd /home/ys/project/src9-9/build/release-cpp11/examples/protobuf/resolver && protoc --cpp_out . /home/ys/project/src9-9/muduo-2.0.0-beta/examples/protobuf/resolver/resolver.proto -I/home/ys/project/src9-9/muduo-2.0.0-beta/examples/protobuf/resolver

examples/protobuf/resolver/resolver.pb.h: examples/protobuf/resolver/resolver.pb.cc

examples/protobuf/resolver/CMakeFiles/resolver_proto.dir/resolver.pb.cc.o: examples/protobuf/resolver/CMakeFiles/resolver_proto.dir/flags.make
examples/protobuf/resolver/CMakeFiles/resolver_proto.dir/resolver.pb.cc.o: examples/protobuf/resolver/resolver.pb.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ys/project/src9-9/build/release-cpp11/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/protobuf/resolver/CMakeFiles/resolver_proto.dir/resolver.pb.cc.o"
	cd /home/ys/project/src9-9/build/release-cpp11/examples/protobuf/resolver && g++   $(CXX_DEFINES) $(CXX_FLAGS) -Wno-conversion -Wno-shadow -o CMakeFiles/resolver_proto.dir/resolver.pb.cc.o -c /home/ys/project/src9-9/build/release-cpp11/examples/protobuf/resolver/resolver.pb.cc

examples/protobuf/resolver/CMakeFiles/resolver_proto.dir/resolver.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/resolver_proto.dir/resolver.pb.cc.i"
	cd /home/ys/project/src9-9/build/release-cpp11/examples/protobuf/resolver && g++  $(CXX_DEFINES) $(CXX_FLAGS) -Wno-conversion -Wno-shadow -E /home/ys/project/src9-9/build/release-cpp11/examples/protobuf/resolver/resolver.pb.cc > CMakeFiles/resolver_proto.dir/resolver.pb.cc.i

examples/protobuf/resolver/CMakeFiles/resolver_proto.dir/resolver.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/resolver_proto.dir/resolver.pb.cc.s"
	cd /home/ys/project/src9-9/build/release-cpp11/examples/protobuf/resolver && g++  $(CXX_DEFINES) $(CXX_FLAGS) -Wno-conversion -Wno-shadow -S /home/ys/project/src9-9/build/release-cpp11/examples/protobuf/resolver/resolver.pb.cc -o CMakeFiles/resolver_proto.dir/resolver.pb.cc.s

examples/protobuf/resolver/CMakeFiles/resolver_proto.dir/resolver.pb.cc.o.requires:
.PHONY : examples/protobuf/resolver/CMakeFiles/resolver_proto.dir/resolver.pb.cc.o.requires

examples/protobuf/resolver/CMakeFiles/resolver_proto.dir/resolver.pb.cc.o.provides: examples/protobuf/resolver/CMakeFiles/resolver_proto.dir/resolver.pb.cc.o.requires
	$(MAKE) -f examples/protobuf/resolver/CMakeFiles/resolver_proto.dir/build.make examples/protobuf/resolver/CMakeFiles/resolver_proto.dir/resolver.pb.cc.o.provides.build
.PHONY : examples/protobuf/resolver/CMakeFiles/resolver_proto.dir/resolver.pb.cc.o.provides

examples/protobuf/resolver/CMakeFiles/resolver_proto.dir/resolver.pb.cc.o.provides.build: examples/protobuf/resolver/CMakeFiles/resolver_proto.dir/resolver.pb.cc.o

# Object files for target resolver_proto
resolver_proto_OBJECTS = \
"CMakeFiles/resolver_proto.dir/resolver.pb.cc.o"

# External object files for target resolver_proto
resolver_proto_EXTERNAL_OBJECTS =

lib/libresolver_proto.a: examples/protobuf/resolver/CMakeFiles/resolver_proto.dir/resolver.pb.cc.o
lib/libresolver_proto.a: examples/protobuf/resolver/CMakeFiles/resolver_proto.dir/build.make
lib/libresolver_proto.a: examples/protobuf/resolver/CMakeFiles/resolver_proto.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library ../../../lib/libresolver_proto.a"
	cd /home/ys/project/src9-9/build/release-cpp11/examples/protobuf/resolver && $(CMAKE_COMMAND) -P CMakeFiles/resolver_proto.dir/cmake_clean_target.cmake
	cd /home/ys/project/src9-9/build/release-cpp11/examples/protobuf/resolver && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/resolver_proto.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/protobuf/resolver/CMakeFiles/resolver_proto.dir/build: lib/libresolver_proto.a
.PHONY : examples/protobuf/resolver/CMakeFiles/resolver_proto.dir/build

examples/protobuf/resolver/CMakeFiles/resolver_proto.dir/requires: examples/protobuf/resolver/CMakeFiles/resolver_proto.dir/resolver.pb.cc.o.requires
.PHONY : examples/protobuf/resolver/CMakeFiles/resolver_proto.dir/requires

examples/protobuf/resolver/CMakeFiles/resolver_proto.dir/clean:
	cd /home/ys/project/src9-9/build/release-cpp11/examples/protobuf/resolver && $(CMAKE_COMMAND) -P CMakeFiles/resolver_proto.dir/cmake_clean.cmake
.PHONY : examples/protobuf/resolver/CMakeFiles/resolver_proto.dir/clean

examples/protobuf/resolver/CMakeFiles/resolver_proto.dir/depend: examples/protobuf/resolver/resolver.pb.cc
examples/protobuf/resolver/CMakeFiles/resolver_proto.dir/depend: examples/protobuf/resolver/resolver.pb.h
	cd /home/ys/project/src9-9/build/release-cpp11 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ys/project/src9-9/muduo-2.0.0-beta /home/ys/project/src9-9/muduo-2.0.0-beta/examples/protobuf/resolver /home/ys/project/src9-9/build/release-cpp11 /home/ys/project/src9-9/build/release-cpp11/examples/protobuf/resolver /home/ys/project/src9-9/build/release-cpp11/examples/protobuf/resolver/CMakeFiles/resolver_proto.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/protobuf/resolver/CMakeFiles/resolver_proto.dir/depend

