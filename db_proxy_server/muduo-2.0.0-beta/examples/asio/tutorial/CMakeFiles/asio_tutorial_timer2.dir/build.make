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
CMAKE_SOURCE_DIR = /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta

# Include any dependencies generated for this target.
include examples/asio/tutorial/CMakeFiles/asio_tutorial_timer2.dir/depend.make

# Include the progress variables for this target.
include examples/asio/tutorial/CMakeFiles/asio_tutorial_timer2.dir/progress.make

# Include the compile flags for this target's objects.
include examples/asio/tutorial/CMakeFiles/asio_tutorial_timer2.dir/flags.make

examples/asio/tutorial/CMakeFiles/asio_tutorial_timer2.dir/timer2/timer.cc.o: examples/asio/tutorial/CMakeFiles/asio_tutorial_timer2.dir/flags.make
examples/asio/tutorial/CMakeFiles/asio_tutorial_timer2.dir/timer2/timer.cc.o: examples/asio/tutorial/timer2/timer.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/asio/tutorial/CMakeFiles/asio_tutorial_timer2.dir/timer2/timer.cc.o"
	cd /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/asio/tutorial && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/asio_tutorial_timer2.dir/timer2/timer.cc.o -c /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/asio/tutorial/timer2/timer.cc

examples/asio/tutorial/CMakeFiles/asio_tutorial_timer2.dir/timer2/timer.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/asio_tutorial_timer2.dir/timer2/timer.cc.i"
	cd /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/asio/tutorial && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/asio/tutorial/timer2/timer.cc > CMakeFiles/asio_tutorial_timer2.dir/timer2/timer.cc.i

examples/asio/tutorial/CMakeFiles/asio_tutorial_timer2.dir/timer2/timer.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/asio_tutorial_timer2.dir/timer2/timer.cc.s"
	cd /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/asio/tutorial && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/asio/tutorial/timer2/timer.cc -o CMakeFiles/asio_tutorial_timer2.dir/timer2/timer.cc.s

examples/asio/tutorial/CMakeFiles/asio_tutorial_timer2.dir/timer2/timer.cc.o.requires:
.PHONY : examples/asio/tutorial/CMakeFiles/asio_tutorial_timer2.dir/timer2/timer.cc.o.requires

examples/asio/tutorial/CMakeFiles/asio_tutorial_timer2.dir/timer2/timer.cc.o.provides: examples/asio/tutorial/CMakeFiles/asio_tutorial_timer2.dir/timer2/timer.cc.o.requires
	$(MAKE) -f examples/asio/tutorial/CMakeFiles/asio_tutorial_timer2.dir/build.make examples/asio/tutorial/CMakeFiles/asio_tutorial_timer2.dir/timer2/timer.cc.o.provides.build
.PHONY : examples/asio/tutorial/CMakeFiles/asio_tutorial_timer2.dir/timer2/timer.cc.o.provides

examples/asio/tutorial/CMakeFiles/asio_tutorial_timer2.dir/timer2/timer.cc.o.provides.build: examples/asio/tutorial/CMakeFiles/asio_tutorial_timer2.dir/timer2/timer.cc.o

# Object files for target asio_tutorial_timer2
asio_tutorial_timer2_OBJECTS = \
"CMakeFiles/asio_tutorial_timer2.dir/timer2/timer.cc.o"

# External object files for target asio_tutorial_timer2
asio_tutorial_timer2_EXTERNAL_OBJECTS =

bin/asio_tutorial_timer2: examples/asio/tutorial/CMakeFiles/asio_tutorial_timer2.dir/timer2/timer.cc.o
bin/asio_tutorial_timer2: examples/asio/tutorial/CMakeFiles/asio_tutorial_timer2.dir/build.make
bin/asio_tutorial_timer2: lib/libmuduo_net.a
bin/asio_tutorial_timer2: lib/libmuduo_base.a
bin/asio_tutorial_timer2: examples/asio/tutorial/CMakeFiles/asio_tutorial_timer2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../../bin/asio_tutorial_timer2"
	cd /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/asio/tutorial && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/asio_tutorial_timer2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/asio/tutorial/CMakeFiles/asio_tutorial_timer2.dir/build: bin/asio_tutorial_timer2
.PHONY : examples/asio/tutorial/CMakeFiles/asio_tutorial_timer2.dir/build

examples/asio/tutorial/CMakeFiles/asio_tutorial_timer2.dir/requires: examples/asio/tutorial/CMakeFiles/asio_tutorial_timer2.dir/timer2/timer.cc.o.requires
.PHONY : examples/asio/tutorial/CMakeFiles/asio_tutorial_timer2.dir/requires

examples/asio/tutorial/CMakeFiles/asio_tutorial_timer2.dir/clean:
	cd /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/asio/tutorial && $(CMAKE_COMMAND) -P CMakeFiles/asio_tutorial_timer2.dir/cmake_clean.cmake
.PHONY : examples/asio/tutorial/CMakeFiles/asio_tutorial_timer2.dir/clean

examples/asio/tutorial/CMakeFiles/asio_tutorial_timer2.dir/depend:
	cd /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/asio/tutorial /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/asio/tutorial /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/asio/tutorial/CMakeFiles/asio_tutorial_timer2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/asio/tutorial/CMakeFiles/asio_tutorial_timer2.dir/depend

