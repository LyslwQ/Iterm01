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
CMAKE_SOURCE_DIR = /home/ys/project/src9-9/muduo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ys/project/src9-9/build/release

# Include any dependencies generated for this target.
include examples/netty/echo/CMakeFiles/netty_echo_server.dir/depend.make

# Include the progress variables for this target.
include examples/netty/echo/CMakeFiles/netty_echo_server.dir/progress.make

# Include the compile flags for this target's objects.
include examples/netty/echo/CMakeFiles/netty_echo_server.dir/flags.make

examples/netty/echo/CMakeFiles/netty_echo_server.dir/server.cc.o: examples/netty/echo/CMakeFiles/netty_echo_server.dir/flags.make
examples/netty/echo/CMakeFiles/netty_echo_server.dir/server.cc.o: /home/ys/project/src9-9/muduo/examples/netty/echo/server.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ys/project/src9-9/build/release/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/netty/echo/CMakeFiles/netty_echo_server.dir/server.cc.o"
	cd /home/ys/project/src9-9/build/release/examples/netty/echo && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/netty_echo_server.dir/server.cc.o -c /home/ys/project/src9-9/muduo/examples/netty/echo/server.cc

examples/netty/echo/CMakeFiles/netty_echo_server.dir/server.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/netty_echo_server.dir/server.cc.i"
	cd /home/ys/project/src9-9/build/release/examples/netty/echo && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ys/project/src9-9/muduo/examples/netty/echo/server.cc > CMakeFiles/netty_echo_server.dir/server.cc.i

examples/netty/echo/CMakeFiles/netty_echo_server.dir/server.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/netty_echo_server.dir/server.cc.s"
	cd /home/ys/project/src9-9/build/release/examples/netty/echo && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ys/project/src9-9/muduo/examples/netty/echo/server.cc -o CMakeFiles/netty_echo_server.dir/server.cc.s

examples/netty/echo/CMakeFiles/netty_echo_server.dir/server.cc.o.requires:
.PHONY : examples/netty/echo/CMakeFiles/netty_echo_server.dir/server.cc.o.requires

examples/netty/echo/CMakeFiles/netty_echo_server.dir/server.cc.o.provides: examples/netty/echo/CMakeFiles/netty_echo_server.dir/server.cc.o.requires
	$(MAKE) -f examples/netty/echo/CMakeFiles/netty_echo_server.dir/build.make examples/netty/echo/CMakeFiles/netty_echo_server.dir/server.cc.o.provides.build
.PHONY : examples/netty/echo/CMakeFiles/netty_echo_server.dir/server.cc.o.provides

examples/netty/echo/CMakeFiles/netty_echo_server.dir/server.cc.o.provides.build: examples/netty/echo/CMakeFiles/netty_echo_server.dir/server.cc.o

# Object files for target netty_echo_server
netty_echo_server_OBJECTS = \
"CMakeFiles/netty_echo_server.dir/server.cc.o"

# External object files for target netty_echo_server
netty_echo_server_EXTERNAL_OBJECTS =

bin/netty_echo_server: examples/netty/echo/CMakeFiles/netty_echo_server.dir/server.cc.o
bin/netty_echo_server: examples/netty/echo/CMakeFiles/netty_echo_server.dir/build.make
bin/netty_echo_server: lib/libmuduo_net.a
bin/netty_echo_server: lib/libmuduo_base.a
bin/netty_echo_server: examples/netty/echo/CMakeFiles/netty_echo_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../../bin/netty_echo_server"
	cd /home/ys/project/src9-9/build/release/examples/netty/echo && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/netty_echo_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/netty/echo/CMakeFiles/netty_echo_server.dir/build: bin/netty_echo_server
.PHONY : examples/netty/echo/CMakeFiles/netty_echo_server.dir/build

examples/netty/echo/CMakeFiles/netty_echo_server.dir/requires: examples/netty/echo/CMakeFiles/netty_echo_server.dir/server.cc.o.requires
.PHONY : examples/netty/echo/CMakeFiles/netty_echo_server.dir/requires

examples/netty/echo/CMakeFiles/netty_echo_server.dir/clean:
	cd /home/ys/project/src9-9/build/release/examples/netty/echo && $(CMAKE_COMMAND) -P CMakeFiles/netty_echo_server.dir/cmake_clean.cmake
.PHONY : examples/netty/echo/CMakeFiles/netty_echo_server.dir/clean

examples/netty/echo/CMakeFiles/netty_echo_server.dir/depend:
	cd /home/ys/project/src9-9/build/release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ys/project/src9-9/muduo /home/ys/project/src9-9/muduo/examples/netty/echo /home/ys/project/src9-9/build/release /home/ys/project/src9-9/build/release/examples/netty/echo /home/ys/project/src9-9/build/release/examples/netty/echo/CMakeFiles/netty_echo_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/netty/echo/CMakeFiles/netty_echo_server.dir/depend

