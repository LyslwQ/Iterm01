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
include examples/pingpong/CMakeFiles/pingpong_bench.dir/depend.make

# Include the progress variables for this target.
include examples/pingpong/CMakeFiles/pingpong_bench.dir/progress.make

# Include the compile flags for this target's objects.
include examples/pingpong/CMakeFiles/pingpong_bench.dir/flags.make

examples/pingpong/CMakeFiles/pingpong_bench.dir/bench.cc.o: examples/pingpong/CMakeFiles/pingpong_bench.dir/flags.make
examples/pingpong/CMakeFiles/pingpong_bench.dir/bench.cc.o: examples/pingpong/bench.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/pingpong/CMakeFiles/pingpong_bench.dir/bench.cc.o"
	cd /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/pingpong && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/pingpong_bench.dir/bench.cc.o -c /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/pingpong/bench.cc

examples/pingpong/CMakeFiles/pingpong_bench.dir/bench.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pingpong_bench.dir/bench.cc.i"
	cd /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/pingpong && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/pingpong/bench.cc > CMakeFiles/pingpong_bench.dir/bench.cc.i

examples/pingpong/CMakeFiles/pingpong_bench.dir/bench.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pingpong_bench.dir/bench.cc.s"
	cd /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/pingpong && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/pingpong/bench.cc -o CMakeFiles/pingpong_bench.dir/bench.cc.s

examples/pingpong/CMakeFiles/pingpong_bench.dir/bench.cc.o.requires:
.PHONY : examples/pingpong/CMakeFiles/pingpong_bench.dir/bench.cc.o.requires

examples/pingpong/CMakeFiles/pingpong_bench.dir/bench.cc.o.provides: examples/pingpong/CMakeFiles/pingpong_bench.dir/bench.cc.o.requires
	$(MAKE) -f examples/pingpong/CMakeFiles/pingpong_bench.dir/build.make examples/pingpong/CMakeFiles/pingpong_bench.dir/bench.cc.o.provides.build
.PHONY : examples/pingpong/CMakeFiles/pingpong_bench.dir/bench.cc.o.provides

examples/pingpong/CMakeFiles/pingpong_bench.dir/bench.cc.o.provides.build: examples/pingpong/CMakeFiles/pingpong_bench.dir/bench.cc.o

# Object files for target pingpong_bench
pingpong_bench_OBJECTS = \
"CMakeFiles/pingpong_bench.dir/bench.cc.o"

# External object files for target pingpong_bench
pingpong_bench_EXTERNAL_OBJECTS =

bin/pingpong_bench: examples/pingpong/CMakeFiles/pingpong_bench.dir/bench.cc.o
bin/pingpong_bench: examples/pingpong/CMakeFiles/pingpong_bench.dir/build.make
bin/pingpong_bench: lib/libmuduo_net.a
bin/pingpong_bench: lib/libmuduo_base.a
bin/pingpong_bench: examples/pingpong/CMakeFiles/pingpong_bench.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../bin/pingpong_bench"
	cd /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/pingpong && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pingpong_bench.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/pingpong/CMakeFiles/pingpong_bench.dir/build: bin/pingpong_bench
.PHONY : examples/pingpong/CMakeFiles/pingpong_bench.dir/build

examples/pingpong/CMakeFiles/pingpong_bench.dir/requires: examples/pingpong/CMakeFiles/pingpong_bench.dir/bench.cc.o.requires
.PHONY : examples/pingpong/CMakeFiles/pingpong_bench.dir/requires

examples/pingpong/CMakeFiles/pingpong_bench.dir/clean:
	cd /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/pingpong && $(CMAKE_COMMAND) -P CMakeFiles/pingpong_bench.dir/cmake_clean.cmake
.PHONY : examples/pingpong/CMakeFiles/pingpong_bench.dir/clean

examples/pingpong/CMakeFiles/pingpong_bench.dir/depend:
	cd /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/pingpong /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/pingpong /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/pingpong/CMakeFiles/pingpong_bench.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/pingpong/CMakeFiles/pingpong_bench.dir/depend

