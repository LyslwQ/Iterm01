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
include examples/curl/CMakeFiles/mcurl.dir/depend.make

# Include the progress variables for this target.
include examples/curl/CMakeFiles/mcurl.dir/progress.make

# Include the compile flags for this target's objects.
include examples/curl/CMakeFiles/mcurl.dir/flags.make

examples/curl/CMakeFiles/mcurl.dir/mcurl.cc.o: examples/curl/CMakeFiles/mcurl.dir/flags.make
examples/curl/CMakeFiles/mcurl.dir/mcurl.cc.o: /home/ys/project/src9-9/muduo-2.0.0-beta/examples/curl/mcurl.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ys/project/src9-9/build/release-cpp11/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/curl/CMakeFiles/mcurl.dir/mcurl.cc.o"
	cd /home/ys/project/src9-9/build/release-cpp11/examples/curl && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/mcurl.dir/mcurl.cc.o -c /home/ys/project/src9-9/muduo-2.0.0-beta/examples/curl/mcurl.cc

examples/curl/CMakeFiles/mcurl.dir/mcurl.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mcurl.dir/mcurl.cc.i"
	cd /home/ys/project/src9-9/build/release-cpp11/examples/curl && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ys/project/src9-9/muduo-2.0.0-beta/examples/curl/mcurl.cc > CMakeFiles/mcurl.dir/mcurl.cc.i

examples/curl/CMakeFiles/mcurl.dir/mcurl.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mcurl.dir/mcurl.cc.s"
	cd /home/ys/project/src9-9/build/release-cpp11/examples/curl && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ys/project/src9-9/muduo-2.0.0-beta/examples/curl/mcurl.cc -o CMakeFiles/mcurl.dir/mcurl.cc.s

examples/curl/CMakeFiles/mcurl.dir/mcurl.cc.o.requires:
.PHONY : examples/curl/CMakeFiles/mcurl.dir/mcurl.cc.o.requires

examples/curl/CMakeFiles/mcurl.dir/mcurl.cc.o.provides: examples/curl/CMakeFiles/mcurl.dir/mcurl.cc.o.requires
	$(MAKE) -f examples/curl/CMakeFiles/mcurl.dir/build.make examples/curl/CMakeFiles/mcurl.dir/mcurl.cc.o.provides.build
.PHONY : examples/curl/CMakeFiles/mcurl.dir/mcurl.cc.o.provides

examples/curl/CMakeFiles/mcurl.dir/mcurl.cc.o.provides.build: examples/curl/CMakeFiles/mcurl.dir/mcurl.cc.o

# Object files for target mcurl
mcurl_OBJECTS = \
"CMakeFiles/mcurl.dir/mcurl.cc.o"

# External object files for target mcurl
mcurl_EXTERNAL_OBJECTS =

bin/mcurl: examples/curl/CMakeFiles/mcurl.dir/mcurl.cc.o
bin/mcurl: examples/curl/CMakeFiles/mcurl.dir/build.make
bin/mcurl: lib/libmuduo_curl.a
bin/mcurl: lib/libmuduo_net.a
bin/mcurl: lib/libmuduo_base.a
bin/mcurl: examples/curl/CMakeFiles/mcurl.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../bin/mcurl"
	cd /home/ys/project/src9-9/build/release-cpp11/examples/curl && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mcurl.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/curl/CMakeFiles/mcurl.dir/build: bin/mcurl
.PHONY : examples/curl/CMakeFiles/mcurl.dir/build

examples/curl/CMakeFiles/mcurl.dir/requires: examples/curl/CMakeFiles/mcurl.dir/mcurl.cc.o.requires
.PHONY : examples/curl/CMakeFiles/mcurl.dir/requires

examples/curl/CMakeFiles/mcurl.dir/clean:
	cd /home/ys/project/src9-9/build/release-cpp11/examples/curl && $(CMAKE_COMMAND) -P CMakeFiles/mcurl.dir/cmake_clean.cmake
.PHONY : examples/curl/CMakeFiles/mcurl.dir/clean

examples/curl/CMakeFiles/mcurl.dir/depend:
	cd /home/ys/project/src9-9/build/release-cpp11 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ys/project/src9-9/muduo-2.0.0-beta /home/ys/project/src9-9/muduo-2.0.0-beta/examples/curl /home/ys/project/src9-9/build/release-cpp11 /home/ys/project/src9-9/build/release-cpp11/examples/curl /home/ys/project/src9-9/build/release-cpp11/examples/curl/CMakeFiles/mcurl.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/curl/CMakeFiles/mcurl.dir/depend

