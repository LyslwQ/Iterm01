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
include examples/socks4a/CMakeFiles/tcprelay.dir/depend.make

# Include the progress variables for this target.
include examples/socks4a/CMakeFiles/tcprelay.dir/progress.make

# Include the compile flags for this target's objects.
include examples/socks4a/CMakeFiles/tcprelay.dir/flags.make

examples/socks4a/CMakeFiles/tcprelay.dir/tcprelay.cc.o: examples/socks4a/CMakeFiles/tcprelay.dir/flags.make
examples/socks4a/CMakeFiles/tcprelay.dir/tcprelay.cc.o: /home/ys/project/src9-9/muduo-2.0.0-beta/examples/socks4a/tcprelay.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ys/project/src9-9/build/release-cpp11/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/socks4a/CMakeFiles/tcprelay.dir/tcprelay.cc.o"
	cd /home/ys/project/src9-9/build/release-cpp11/examples/socks4a && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tcprelay.dir/tcprelay.cc.o -c /home/ys/project/src9-9/muduo-2.0.0-beta/examples/socks4a/tcprelay.cc

examples/socks4a/CMakeFiles/tcprelay.dir/tcprelay.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tcprelay.dir/tcprelay.cc.i"
	cd /home/ys/project/src9-9/build/release-cpp11/examples/socks4a && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ys/project/src9-9/muduo-2.0.0-beta/examples/socks4a/tcprelay.cc > CMakeFiles/tcprelay.dir/tcprelay.cc.i

examples/socks4a/CMakeFiles/tcprelay.dir/tcprelay.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tcprelay.dir/tcprelay.cc.s"
	cd /home/ys/project/src9-9/build/release-cpp11/examples/socks4a && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ys/project/src9-9/muduo-2.0.0-beta/examples/socks4a/tcprelay.cc -o CMakeFiles/tcprelay.dir/tcprelay.cc.s

examples/socks4a/CMakeFiles/tcprelay.dir/tcprelay.cc.o.requires:
.PHONY : examples/socks4a/CMakeFiles/tcprelay.dir/tcprelay.cc.o.requires

examples/socks4a/CMakeFiles/tcprelay.dir/tcprelay.cc.o.provides: examples/socks4a/CMakeFiles/tcprelay.dir/tcprelay.cc.o.requires
	$(MAKE) -f examples/socks4a/CMakeFiles/tcprelay.dir/build.make examples/socks4a/CMakeFiles/tcprelay.dir/tcprelay.cc.o.provides.build
.PHONY : examples/socks4a/CMakeFiles/tcprelay.dir/tcprelay.cc.o.provides

examples/socks4a/CMakeFiles/tcprelay.dir/tcprelay.cc.o.provides.build: examples/socks4a/CMakeFiles/tcprelay.dir/tcprelay.cc.o

# Object files for target tcprelay
tcprelay_OBJECTS = \
"CMakeFiles/tcprelay.dir/tcprelay.cc.o"

# External object files for target tcprelay
tcprelay_EXTERNAL_OBJECTS =

bin/tcprelay: examples/socks4a/CMakeFiles/tcprelay.dir/tcprelay.cc.o
bin/tcprelay: examples/socks4a/CMakeFiles/tcprelay.dir/build.make
bin/tcprelay: lib/libmuduo_net.a
bin/tcprelay: lib/libmuduo_base.a
bin/tcprelay: examples/socks4a/CMakeFiles/tcprelay.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../bin/tcprelay"
	cd /home/ys/project/src9-9/build/release-cpp11/examples/socks4a && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tcprelay.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/socks4a/CMakeFiles/tcprelay.dir/build: bin/tcprelay
.PHONY : examples/socks4a/CMakeFiles/tcprelay.dir/build

examples/socks4a/CMakeFiles/tcprelay.dir/requires: examples/socks4a/CMakeFiles/tcprelay.dir/tcprelay.cc.o.requires
.PHONY : examples/socks4a/CMakeFiles/tcprelay.dir/requires

examples/socks4a/CMakeFiles/tcprelay.dir/clean:
	cd /home/ys/project/src9-9/build/release-cpp11/examples/socks4a && $(CMAKE_COMMAND) -P CMakeFiles/tcprelay.dir/cmake_clean.cmake
.PHONY : examples/socks4a/CMakeFiles/tcprelay.dir/clean

examples/socks4a/CMakeFiles/tcprelay.dir/depend:
	cd /home/ys/project/src9-9/build/release-cpp11 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ys/project/src9-9/muduo-2.0.0-beta /home/ys/project/src9-9/muduo-2.0.0-beta/examples/socks4a /home/ys/project/src9-9/build/release-cpp11 /home/ys/project/src9-9/build/release-cpp11/examples/socks4a /home/ys/project/src9-9/build/release-cpp11/examples/socks4a/CMakeFiles/tcprelay.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/socks4a/CMakeFiles/tcprelay.dir/depend

