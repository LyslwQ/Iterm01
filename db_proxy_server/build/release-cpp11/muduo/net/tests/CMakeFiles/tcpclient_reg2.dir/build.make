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
include muduo/net/tests/CMakeFiles/tcpclient_reg2.dir/depend.make

# Include the progress variables for this target.
include muduo/net/tests/CMakeFiles/tcpclient_reg2.dir/progress.make

# Include the compile flags for this target's objects.
include muduo/net/tests/CMakeFiles/tcpclient_reg2.dir/flags.make

muduo/net/tests/CMakeFiles/tcpclient_reg2.dir/TcpClient_reg2.cc.o: muduo/net/tests/CMakeFiles/tcpclient_reg2.dir/flags.make
muduo/net/tests/CMakeFiles/tcpclient_reg2.dir/TcpClient_reg2.cc.o: /home/ys/project/src9-9/muduo-2.0.0-beta/muduo/net/tests/TcpClient_reg2.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ys/project/src9-9/build/release-cpp11/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object muduo/net/tests/CMakeFiles/tcpclient_reg2.dir/TcpClient_reg2.cc.o"
	cd /home/ys/project/src9-9/build/release-cpp11/muduo/net/tests && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tcpclient_reg2.dir/TcpClient_reg2.cc.o -c /home/ys/project/src9-9/muduo-2.0.0-beta/muduo/net/tests/TcpClient_reg2.cc

muduo/net/tests/CMakeFiles/tcpclient_reg2.dir/TcpClient_reg2.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tcpclient_reg2.dir/TcpClient_reg2.cc.i"
	cd /home/ys/project/src9-9/build/release-cpp11/muduo/net/tests && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ys/project/src9-9/muduo-2.0.0-beta/muduo/net/tests/TcpClient_reg2.cc > CMakeFiles/tcpclient_reg2.dir/TcpClient_reg2.cc.i

muduo/net/tests/CMakeFiles/tcpclient_reg2.dir/TcpClient_reg2.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tcpclient_reg2.dir/TcpClient_reg2.cc.s"
	cd /home/ys/project/src9-9/build/release-cpp11/muduo/net/tests && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ys/project/src9-9/muduo-2.0.0-beta/muduo/net/tests/TcpClient_reg2.cc -o CMakeFiles/tcpclient_reg2.dir/TcpClient_reg2.cc.s

muduo/net/tests/CMakeFiles/tcpclient_reg2.dir/TcpClient_reg2.cc.o.requires:
.PHONY : muduo/net/tests/CMakeFiles/tcpclient_reg2.dir/TcpClient_reg2.cc.o.requires

muduo/net/tests/CMakeFiles/tcpclient_reg2.dir/TcpClient_reg2.cc.o.provides: muduo/net/tests/CMakeFiles/tcpclient_reg2.dir/TcpClient_reg2.cc.o.requires
	$(MAKE) -f muduo/net/tests/CMakeFiles/tcpclient_reg2.dir/build.make muduo/net/tests/CMakeFiles/tcpclient_reg2.dir/TcpClient_reg2.cc.o.provides.build
.PHONY : muduo/net/tests/CMakeFiles/tcpclient_reg2.dir/TcpClient_reg2.cc.o.provides

muduo/net/tests/CMakeFiles/tcpclient_reg2.dir/TcpClient_reg2.cc.o.provides.build: muduo/net/tests/CMakeFiles/tcpclient_reg2.dir/TcpClient_reg2.cc.o

# Object files for target tcpclient_reg2
tcpclient_reg2_OBJECTS = \
"CMakeFiles/tcpclient_reg2.dir/TcpClient_reg2.cc.o"

# External object files for target tcpclient_reg2
tcpclient_reg2_EXTERNAL_OBJECTS =

bin/tcpclient_reg2: muduo/net/tests/CMakeFiles/tcpclient_reg2.dir/TcpClient_reg2.cc.o
bin/tcpclient_reg2: muduo/net/tests/CMakeFiles/tcpclient_reg2.dir/build.make
bin/tcpclient_reg2: lib/libmuduo_net.a
bin/tcpclient_reg2: lib/libmuduo_base.a
bin/tcpclient_reg2: muduo/net/tests/CMakeFiles/tcpclient_reg2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../../bin/tcpclient_reg2"
	cd /home/ys/project/src9-9/build/release-cpp11/muduo/net/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tcpclient_reg2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
muduo/net/tests/CMakeFiles/tcpclient_reg2.dir/build: bin/tcpclient_reg2
.PHONY : muduo/net/tests/CMakeFiles/tcpclient_reg2.dir/build

muduo/net/tests/CMakeFiles/tcpclient_reg2.dir/requires: muduo/net/tests/CMakeFiles/tcpclient_reg2.dir/TcpClient_reg2.cc.o.requires
.PHONY : muduo/net/tests/CMakeFiles/tcpclient_reg2.dir/requires

muduo/net/tests/CMakeFiles/tcpclient_reg2.dir/clean:
	cd /home/ys/project/src9-9/build/release-cpp11/muduo/net/tests && $(CMAKE_COMMAND) -P CMakeFiles/tcpclient_reg2.dir/cmake_clean.cmake
.PHONY : muduo/net/tests/CMakeFiles/tcpclient_reg2.dir/clean

muduo/net/tests/CMakeFiles/tcpclient_reg2.dir/depend:
	cd /home/ys/project/src9-9/build/release-cpp11 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ys/project/src9-9/muduo-2.0.0-beta /home/ys/project/src9-9/muduo-2.0.0-beta/muduo/net/tests /home/ys/project/src9-9/build/release-cpp11 /home/ys/project/src9-9/build/release-cpp11/muduo/net/tests /home/ys/project/src9-9/build/release-cpp11/muduo/net/tests/CMakeFiles/tcpclient_reg2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : muduo/net/tests/CMakeFiles/tcpclient_reg2.dir/depend

