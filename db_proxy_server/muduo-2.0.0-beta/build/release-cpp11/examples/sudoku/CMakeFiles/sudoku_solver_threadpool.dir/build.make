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
include examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/depend.make

# Include the progress variables for this target.
include examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/progress.make

# Include the compile flags for this target's objects.
include examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/flags.make

examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/server_threadpool.cc.o: examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/flags.make
examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/server_threadpool.cc.o: /home/ys/project/src9-9/muduo-2.0.0-beta/examples/sudoku/server_threadpool.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ys/project/src9-9/build/release-cpp11/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/server_threadpool.cc.o"
	cd /home/ys/project/src9-9/build/release-cpp11/examples/sudoku && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sudoku_solver_threadpool.dir/server_threadpool.cc.o -c /home/ys/project/src9-9/muduo-2.0.0-beta/examples/sudoku/server_threadpool.cc

examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/server_threadpool.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sudoku_solver_threadpool.dir/server_threadpool.cc.i"
	cd /home/ys/project/src9-9/build/release-cpp11/examples/sudoku && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ys/project/src9-9/muduo-2.0.0-beta/examples/sudoku/server_threadpool.cc > CMakeFiles/sudoku_solver_threadpool.dir/server_threadpool.cc.i

examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/server_threadpool.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sudoku_solver_threadpool.dir/server_threadpool.cc.s"
	cd /home/ys/project/src9-9/build/release-cpp11/examples/sudoku && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ys/project/src9-9/muduo-2.0.0-beta/examples/sudoku/server_threadpool.cc -o CMakeFiles/sudoku_solver_threadpool.dir/server_threadpool.cc.s

examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/server_threadpool.cc.o.requires:
.PHONY : examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/server_threadpool.cc.o.requires

examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/server_threadpool.cc.o.provides: examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/server_threadpool.cc.o.requires
	$(MAKE) -f examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/build.make examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/server_threadpool.cc.o.provides.build
.PHONY : examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/server_threadpool.cc.o.provides

examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/server_threadpool.cc.o.provides.build: examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/server_threadpool.cc.o

examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/sudoku.cc.o: examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/flags.make
examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/sudoku.cc.o: /home/ys/project/src9-9/muduo-2.0.0-beta/examples/sudoku/sudoku.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ys/project/src9-9/build/release-cpp11/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/sudoku.cc.o"
	cd /home/ys/project/src9-9/build/release-cpp11/examples/sudoku && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sudoku_solver_threadpool.dir/sudoku.cc.o -c /home/ys/project/src9-9/muduo-2.0.0-beta/examples/sudoku/sudoku.cc

examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/sudoku.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sudoku_solver_threadpool.dir/sudoku.cc.i"
	cd /home/ys/project/src9-9/build/release-cpp11/examples/sudoku && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ys/project/src9-9/muduo-2.0.0-beta/examples/sudoku/sudoku.cc > CMakeFiles/sudoku_solver_threadpool.dir/sudoku.cc.i

examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/sudoku.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sudoku_solver_threadpool.dir/sudoku.cc.s"
	cd /home/ys/project/src9-9/build/release-cpp11/examples/sudoku && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ys/project/src9-9/muduo-2.0.0-beta/examples/sudoku/sudoku.cc -o CMakeFiles/sudoku_solver_threadpool.dir/sudoku.cc.s

examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/sudoku.cc.o.requires:
.PHONY : examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/sudoku.cc.o.requires

examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/sudoku.cc.o.provides: examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/sudoku.cc.o.requires
	$(MAKE) -f examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/build.make examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/sudoku.cc.o.provides.build
.PHONY : examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/sudoku.cc.o.provides

examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/sudoku.cc.o.provides.build: examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/sudoku.cc.o

# Object files for target sudoku_solver_threadpool
sudoku_solver_threadpool_OBJECTS = \
"CMakeFiles/sudoku_solver_threadpool.dir/server_threadpool.cc.o" \
"CMakeFiles/sudoku_solver_threadpool.dir/sudoku.cc.o"

# External object files for target sudoku_solver_threadpool
sudoku_solver_threadpool_EXTERNAL_OBJECTS =

bin/sudoku_solver_threadpool: examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/server_threadpool.cc.o
bin/sudoku_solver_threadpool: examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/sudoku.cc.o
bin/sudoku_solver_threadpool: examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/build.make
bin/sudoku_solver_threadpool: lib/libmuduo_net.a
bin/sudoku_solver_threadpool: lib/libmuduo_base.a
bin/sudoku_solver_threadpool: examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../bin/sudoku_solver_threadpool"
	cd /home/ys/project/src9-9/build/release-cpp11/examples/sudoku && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sudoku_solver_threadpool.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/build: bin/sudoku_solver_threadpool
.PHONY : examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/build

examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/requires: examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/server_threadpool.cc.o.requires
examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/requires: examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/sudoku.cc.o.requires
.PHONY : examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/requires

examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/clean:
	cd /home/ys/project/src9-9/build/release-cpp11/examples/sudoku && $(CMAKE_COMMAND) -P CMakeFiles/sudoku_solver_threadpool.dir/cmake_clean.cmake
.PHONY : examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/clean

examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/depend:
	cd /home/ys/project/src9-9/build/release-cpp11 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ys/project/src9-9/muduo-2.0.0-beta /home/ys/project/src9-9/muduo-2.0.0-beta/examples/sudoku /home/ys/project/src9-9/build/release-cpp11 /home/ys/project/src9-9/build/release-cpp11/examples/sudoku /home/ys/project/src9-9/build/release-cpp11/examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/sudoku/CMakeFiles/sudoku_solver_threadpool.dir/depend

