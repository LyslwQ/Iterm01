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
include muduo/net/tests/CMakeFiles/echoclient_unittest.dir/depend.make

# Include the progress variables for this target.
include muduo/net/tests/CMakeFiles/echoclient_unittest.dir/progress.make

# Include the compile flags for this target's objects.
include muduo/net/tests/CMakeFiles/echoclient_unittest.dir/flags.make

muduo/net/tests/CMakeFiles/echoclient_unittest.dir/EchoClient_unittest.cc.o: muduo/net/tests/CMakeFiles/echoclient_unittest.dir/flags.make
muduo/net/tests/CMakeFiles/echoclient_unittest.dir/EchoClient_unittest.cc.o: /home/ys/project/src9-9/muduo-2.0.0-beta/muduo/net/tests/EchoClient_unittest.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ys/project/src9-9/build/release-cpp11/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object muduo/net/tests/CMakeFiles/echoclient_unittest.dir/EchoClient_unittest.cc.o"
	cd /home/ys/project/src9-9/build/release-cpp11/muduo/net/tests && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/echoclient_unittest.dir/EchoClient_unittest.cc.o -c /home/ys/project/src9-9/muduo-2.0.0-beta/muduo/net/tests/EchoClient_unittest.cc

muduo/net/tests/CMakeFiles/echoclient_unittest.dir/EchoClient_unittest.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/echoclient_unittest.dir/EchoClient_unittest.cc.i"
	cd /home/ys/project/src9-9/build/release-cpp11/muduo/net/tests && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ys/project/src9-9/muduo-2.0.0-beta/muduo/net/tests/EchoClient_unittest.cc > CMakeFiles/echoclient_unittest.dir/EchoClient_unittest.cc.i

muduo/net/tests/CMakeFiles/echoclient_unittest.dir/EchoClient_unittest.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/echoclient_unittest.dir/EchoClient_unittest.cc.s"
	cd /home/ys/project/src9-9/build/release-cpp11/muduo/net/tests && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ys/project/src9-9/muduo-2.0.0-beta/muduo/net/tests/EchoClient_unittest.cc -o CMakeFiles/echoclient_unittest.dir/EchoClient_unittest.cc.s

muduo/net/tests/CMakeFiles/echoclient_unittest.dir/EchoClient_unittest.cc.o.requires:
.PHONY : muduo/net/tests/CMakeFiles/echoclient_unittest.dir/EchoClient_unittest.cc.o.requires

muduo/net/tests/CMakeFiles/echoclient_unittest.dir/EchoClient_unittest.cc.o.provides: muduo/net/tests/CMakeFiles/echoclient_unittest.dir/EchoClient_unittest.cc.o.requires
	$(MAKE) -f muduo/net/tests/CMakeFiles/echoclient_unittest.dir/build.make muduo/net/tests/CMakeFiles/echoclient_unittest.dir/EchoClient_unittest.cc.o.provides.build
.PHONY : muduo/net/tests/CMakeFiles/echoclient_unittest.dir/EchoClient_unittest.cc.o.provides

muduo/net/tests/CMakeFiles/echoclient_unittest.dir/EchoClient_unittest.cc.o.provides.build: muduo/net/tests/CMakeFiles/echoclient_unittest.dir/EchoClient_unittest.cc.o

# Object files for target echoclient_unittest
echoclient_unittest_OBJECTS = \
"CMakeFiles/echoclient_unittest.dir/EchoClient_unittest.cc.o"

# External object files for target echoclient_unittest
echoclient_unittest_EXTERNAL_OBJECTS =

bin/echoclient_unittest: muduo/net/tests/CMakeFiles/echoclient_unittest.dir/EchoClient_unittest.cc.o
bin/echoclient_unittest: muduo/net/tests/CMakeFiles/echoclient_unittest.dir/build.make
bin/echoclient_unittest: lib/libmuduo_net.a
bin/echoclient_unittest: lib/libmuduo_base.a
bin/echoclient_unittest: muduo/net/tests/CMakeFiles/echoclient_unittest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../../bin/echoclient_unittest"
	cd /home/ys/project/src9-9/build/release-cpp11/muduo/net/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/echoclient_unittest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
muduo/net/tests/CMakeFiles/echoclient_unittest.dir/build: bin/echoclient_unittest
.PHONY : muduo/net/tests/CMakeFiles/echoclient_unittest.dir/build

muduo/net/tests/CMakeFiles/echoclient_unittest.dir/requires: muduo/net/tests/CMakeFiles/echoclient_unittest.dir/EchoClient_unittest.cc.o.requires
.PHONY : muduo/net/tests/CMakeFiles/echoclient_unittest.dir/requires

muduo/net/tests/CMakeFiles/echoclient_unittest.dir/clean:
	cd /home/ys/project/src9-9/build/release-cpp11/muduo/net/tests && $(CMAKE_COMMAND) -P CMakeFiles/echoclient_unittest.dir/cmake_clean.cmake
.PHONY : muduo/net/tests/CMakeFiles/echoclient_unittest.dir/clean

muduo/net/tests/CMakeFiles/echoclient_unittest.dir/depend:
	cd /home/ys/project/src9-9/build/release-cpp11 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ys/project/src9-9/muduo-2.0.0-beta /home/ys/project/src9-9/muduo-2.0.0-beta/muduo/net/tests /home/ys/project/src9-9/build/release-cpp11 /home/ys/project/src9-9/build/release-cpp11/muduo/net/tests /home/ys/project/src9-9/build/release-cpp11/muduo/net/tests/CMakeFiles/echoclient_unittest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : muduo/net/tests/CMakeFiles/echoclient_unittest.dir/depend

