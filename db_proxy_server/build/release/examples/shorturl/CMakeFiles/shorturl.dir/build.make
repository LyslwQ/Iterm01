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
include examples/shorturl/CMakeFiles/shorturl.dir/depend.make

# Include the progress variables for this target.
include examples/shorturl/CMakeFiles/shorturl.dir/progress.make

# Include the compile flags for this target's objects.
include examples/shorturl/CMakeFiles/shorturl.dir/flags.make

examples/shorturl/CMakeFiles/shorturl.dir/shorturl.cc.o: examples/shorturl/CMakeFiles/shorturl.dir/flags.make
examples/shorturl/CMakeFiles/shorturl.dir/shorturl.cc.o: /home/ys/project/src9-9/muduo/examples/shorturl/shorturl.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ys/project/src9-9/build/release/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/shorturl/CMakeFiles/shorturl.dir/shorturl.cc.o"
	cd /home/ys/project/src9-9/build/release/examples/shorturl && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/shorturl.dir/shorturl.cc.o -c /home/ys/project/src9-9/muduo/examples/shorturl/shorturl.cc

examples/shorturl/CMakeFiles/shorturl.dir/shorturl.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/shorturl.dir/shorturl.cc.i"
	cd /home/ys/project/src9-9/build/release/examples/shorturl && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ys/project/src9-9/muduo/examples/shorturl/shorturl.cc > CMakeFiles/shorturl.dir/shorturl.cc.i

examples/shorturl/CMakeFiles/shorturl.dir/shorturl.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/shorturl.dir/shorturl.cc.s"
	cd /home/ys/project/src9-9/build/release/examples/shorturl && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ys/project/src9-9/muduo/examples/shorturl/shorturl.cc -o CMakeFiles/shorturl.dir/shorturl.cc.s

examples/shorturl/CMakeFiles/shorturl.dir/shorturl.cc.o.requires:
.PHONY : examples/shorturl/CMakeFiles/shorturl.dir/shorturl.cc.o.requires

examples/shorturl/CMakeFiles/shorturl.dir/shorturl.cc.o.provides: examples/shorturl/CMakeFiles/shorturl.dir/shorturl.cc.o.requires
	$(MAKE) -f examples/shorturl/CMakeFiles/shorturl.dir/build.make examples/shorturl/CMakeFiles/shorturl.dir/shorturl.cc.o.provides.build
.PHONY : examples/shorturl/CMakeFiles/shorturl.dir/shorturl.cc.o.provides

examples/shorturl/CMakeFiles/shorturl.dir/shorturl.cc.o.provides.build: examples/shorturl/CMakeFiles/shorturl.dir/shorturl.cc.o

# Object files for target shorturl
shorturl_OBJECTS = \
"CMakeFiles/shorturl.dir/shorturl.cc.o"

# External object files for target shorturl
shorturl_EXTERNAL_OBJECTS =

bin/shorturl: examples/shorturl/CMakeFiles/shorturl.dir/shorturl.cc.o
bin/shorturl: examples/shorturl/CMakeFiles/shorturl.dir/build.make
bin/shorturl: lib/libmuduo_http.a
bin/shorturl: lib/libmuduo_base.a
bin/shorturl: lib/libmuduo_net.a
bin/shorturl: lib/libmuduo_base.a
bin/shorturl: examples/shorturl/CMakeFiles/shorturl.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../bin/shorturl"
	cd /home/ys/project/src9-9/build/release/examples/shorturl && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/shorturl.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/shorturl/CMakeFiles/shorturl.dir/build: bin/shorturl
.PHONY : examples/shorturl/CMakeFiles/shorturl.dir/build

examples/shorturl/CMakeFiles/shorturl.dir/requires: examples/shorturl/CMakeFiles/shorturl.dir/shorturl.cc.o.requires
.PHONY : examples/shorturl/CMakeFiles/shorturl.dir/requires

examples/shorturl/CMakeFiles/shorturl.dir/clean:
	cd /home/ys/project/src9-9/build/release/examples/shorturl && $(CMAKE_COMMAND) -P CMakeFiles/shorturl.dir/cmake_clean.cmake
.PHONY : examples/shorturl/CMakeFiles/shorturl.dir/clean

examples/shorturl/CMakeFiles/shorturl.dir/depend:
	cd /home/ys/project/src9-9/build/release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ys/project/src9-9/muduo /home/ys/project/src9-9/muduo/examples/shorturl /home/ys/project/src9-9/build/release /home/ys/project/src9-9/build/release/examples/shorturl /home/ys/project/src9-9/build/release/examples/shorturl/CMakeFiles/shorturl.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/shorturl/CMakeFiles/shorturl.dir/depend

