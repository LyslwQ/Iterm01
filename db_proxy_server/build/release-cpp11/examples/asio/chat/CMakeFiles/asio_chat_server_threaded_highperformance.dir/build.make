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
include examples/asio/chat/CMakeFiles/asio_chat_server_threaded_highperformance.dir/depend.make

# Include the progress variables for this target.
include examples/asio/chat/CMakeFiles/asio_chat_server_threaded_highperformance.dir/progress.make

# Include the compile flags for this target's objects.
include examples/asio/chat/CMakeFiles/asio_chat_server_threaded_highperformance.dir/flags.make

examples/asio/chat/CMakeFiles/asio_chat_server_threaded_highperformance.dir/server_threaded_highperformance.cc.o: examples/asio/chat/CMakeFiles/asio_chat_server_threaded_highperformance.dir/flags.make
examples/asio/chat/CMakeFiles/asio_chat_server_threaded_highperformance.dir/server_threaded_highperformance.cc.o: /home/ys/project/src9-9/muduo-2.0.0-beta/examples/asio/chat/server_threaded_highperformance.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ys/project/src9-9/build/release-cpp11/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/asio/chat/CMakeFiles/asio_chat_server_threaded_highperformance.dir/server_threaded_highperformance.cc.o"
	cd /home/ys/project/src9-9/build/release-cpp11/examples/asio/chat && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/asio_chat_server_threaded_highperformance.dir/server_threaded_highperformance.cc.o -c /home/ys/project/src9-9/muduo-2.0.0-beta/examples/asio/chat/server_threaded_highperformance.cc

examples/asio/chat/CMakeFiles/asio_chat_server_threaded_highperformance.dir/server_threaded_highperformance.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/asio_chat_server_threaded_highperformance.dir/server_threaded_highperformance.cc.i"
	cd /home/ys/project/src9-9/build/release-cpp11/examples/asio/chat && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ys/project/src9-9/muduo-2.0.0-beta/examples/asio/chat/server_threaded_highperformance.cc > CMakeFiles/asio_chat_server_threaded_highperformance.dir/server_threaded_highperformance.cc.i

examples/asio/chat/CMakeFiles/asio_chat_server_threaded_highperformance.dir/server_threaded_highperformance.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/asio_chat_server_threaded_highperformance.dir/server_threaded_highperformance.cc.s"
	cd /home/ys/project/src9-9/build/release-cpp11/examples/asio/chat && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ys/project/src9-9/muduo-2.0.0-beta/examples/asio/chat/server_threaded_highperformance.cc -o CMakeFiles/asio_chat_server_threaded_highperformance.dir/server_threaded_highperformance.cc.s

examples/asio/chat/CMakeFiles/asio_chat_server_threaded_highperformance.dir/server_threaded_highperformance.cc.o.requires:
.PHONY : examples/asio/chat/CMakeFiles/asio_chat_server_threaded_highperformance.dir/server_threaded_highperformance.cc.o.requires

examples/asio/chat/CMakeFiles/asio_chat_server_threaded_highperformance.dir/server_threaded_highperformance.cc.o.provides: examples/asio/chat/CMakeFiles/asio_chat_server_threaded_highperformance.dir/server_threaded_highperformance.cc.o.requires
	$(MAKE) -f examples/asio/chat/CMakeFiles/asio_chat_server_threaded_highperformance.dir/build.make examples/asio/chat/CMakeFiles/asio_chat_server_threaded_highperformance.dir/server_threaded_highperformance.cc.o.provides.build
.PHONY : examples/asio/chat/CMakeFiles/asio_chat_server_threaded_highperformance.dir/server_threaded_highperformance.cc.o.provides

examples/asio/chat/CMakeFiles/asio_chat_server_threaded_highperformance.dir/server_threaded_highperformance.cc.o.provides.build: examples/asio/chat/CMakeFiles/asio_chat_server_threaded_highperformance.dir/server_threaded_highperformance.cc.o

# Object files for target asio_chat_server_threaded_highperformance
asio_chat_server_threaded_highperformance_OBJECTS = \
"CMakeFiles/asio_chat_server_threaded_highperformance.dir/server_threaded_highperformance.cc.o"

# External object files for target asio_chat_server_threaded_highperformance
asio_chat_server_threaded_highperformance_EXTERNAL_OBJECTS =

bin/asio_chat_server_threaded_highperformance: examples/asio/chat/CMakeFiles/asio_chat_server_threaded_highperformance.dir/server_threaded_highperformance.cc.o
bin/asio_chat_server_threaded_highperformance: examples/asio/chat/CMakeFiles/asio_chat_server_threaded_highperformance.dir/build.make
bin/asio_chat_server_threaded_highperformance: lib/libmuduo_net.a
bin/asio_chat_server_threaded_highperformance: lib/libmuduo_base.a
bin/asio_chat_server_threaded_highperformance: examples/asio/chat/CMakeFiles/asio_chat_server_threaded_highperformance.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../../bin/asio_chat_server_threaded_highperformance"
	cd /home/ys/project/src9-9/build/release-cpp11/examples/asio/chat && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/asio_chat_server_threaded_highperformance.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/asio/chat/CMakeFiles/asio_chat_server_threaded_highperformance.dir/build: bin/asio_chat_server_threaded_highperformance
.PHONY : examples/asio/chat/CMakeFiles/asio_chat_server_threaded_highperformance.dir/build

examples/asio/chat/CMakeFiles/asio_chat_server_threaded_highperformance.dir/requires: examples/asio/chat/CMakeFiles/asio_chat_server_threaded_highperformance.dir/server_threaded_highperformance.cc.o.requires
.PHONY : examples/asio/chat/CMakeFiles/asio_chat_server_threaded_highperformance.dir/requires

examples/asio/chat/CMakeFiles/asio_chat_server_threaded_highperformance.dir/clean:
	cd /home/ys/project/src9-9/build/release-cpp11/examples/asio/chat && $(CMAKE_COMMAND) -P CMakeFiles/asio_chat_server_threaded_highperformance.dir/cmake_clean.cmake
.PHONY : examples/asio/chat/CMakeFiles/asio_chat_server_threaded_highperformance.dir/clean

examples/asio/chat/CMakeFiles/asio_chat_server_threaded_highperformance.dir/depend:
	cd /home/ys/project/src9-9/build/release-cpp11 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ys/project/src9-9/muduo-2.0.0-beta /home/ys/project/src9-9/muduo-2.0.0-beta/examples/asio/chat /home/ys/project/src9-9/build/release-cpp11 /home/ys/project/src9-9/build/release-cpp11/examples/asio/chat /home/ys/project/src9-9/build/release-cpp11/examples/asio/chat/CMakeFiles/asio_chat_server_threaded_highperformance.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/asio/chat/CMakeFiles/asio_chat_server_threaded_highperformance.dir/depend

