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
include examples/curl/CMakeFiles/curl_download.dir/depend.make

# Include the progress variables for this target.
include examples/curl/CMakeFiles/curl_download.dir/progress.make

# Include the compile flags for this target's objects.
include examples/curl/CMakeFiles/curl_download.dir/flags.make

examples/curl/CMakeFiles/curl_download.dir/download.cc.o: examples/curl/CMakeFiles/curl_download.dir/flags.make
examples/curl/CMakeFiles/curl_download.dir/download.cc.o: /home/ys/project/src9-9/muduo/examples/curl/download.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ys/project/src9-9/build/release/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/curl/CMakeFiles/curl_download.dir/download.cc.o"
	cd /home/ys/project/src9-9/build/release/examples/curl && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/curl_download.dir/download.cc.o -c /home/ys/project/src9-9/muduo/examples/curl/download.cc

examples/curl/CMakeFiles/curl_download.dir/download.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/curl_download.dir/download.cc.i"
	cd /home/ys/project/src9-9/build/release/examples/curl && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ys/project/src9-9/muduo/examples/curl/download.cc > CMakeFiles/curl_download.dir/download.cc.i

examples/curl/CMakeFiles/curl_download.dir/download.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/curl_download.dir/download.cc.s"
	cd /home/ys/project/src9-9/build/release/examples/curl && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ys/project/src9-9/muduo/examples/curl/download.cc -o CMakeFiles/curl_download.dir/download.cc.s

examples/curl/CMakeFiles/curl_download.dir/download.cc.o.requires:
.PHONY : examples/curl/CMakeFiles/curl_download.dir/download.cc.o.requires

examples/curl/CMakeFiles/curl_download.dir/download.cc.o.provides: examples/curl/CMakeFiles/curl_download.dir/download.cc.o.requires
	$(MAKE) -f examples/curl/CMakeFiles/curl_download.dir/build.make examples/curl/CMakeFiles/curl_download.dir/download.cc.o.provides.build
.PHONY : examples/curl/CMakeFiles/curl_download.dir/download.cc.o.provides

examples/curl/CMakeFiles/curl_download.dir/download.cc.o.provides.build: examples/curl/CMakeFiles/curl_download.dir/download.cc.o

# Object files for target curl_download
curl_download_OBJECTS = \
"CMakeFiles/curl_download.dir/download.cc.o"

# External object files for target curl_download
curl_download_EXTERNAL_OBJECTS =

bin/curl_download: examples/curl/CMakeFiles/curl_download.dir/download.cc.o
bin/curl_download: examples/curl/CMakeFiles/curl_download.dir/build.make
bin/curl_download: lib/libmuduo_curl.a
bin/curl_download: lib/libmuduo_net.a
bin/curl_download: lib/libmuduo_base.a
bin/curl_download: examples/curl/CMakeFiles/curl_download.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../bin/curl_download"
	cd /home/ys/project/src9-9/build/release/examples/curl && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/curl_download.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/curl/CMakeFiles/curl_download.dir/build: bin/curl_download
.PHONY : examples/curl/CMakeFiles/curl_download.dir/build

examples/curl/CMakeFiles/curl_download.dir/requires: examples/curl/CMakeFiles/curl_download.dir/download.cc.o.requires
.PHONY : examples/curl/CMakeFiles/curl_download.dir/requires

examples/curl/CMakeFiles/curl_download.dir/clean:
	cd /home/ys/project/src9-9/build/release/examples/curl && $(CMAKE_COMMAND) -P CMakeFiles/curl_download.dir/cmake_clean.cmake
.PHONY : examples/curl/CMakeFiles/curl_download.dir/clean

examples/curl/CMakeFiles/curl_download.dir/depend:
	cd /home/ys/project/src9-9/build/release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ys/project/src9-9/muduo /home/ys/project/src9-9/muduo/examples/curl /home/ys/project/src9-9/build/release /home/ys/project/src9-9/build/release/examples/curl /home/ys/project/src9-9/build/release/examples/curl/CMakeFiles/curl_download.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/curl/CMakeFiles/curl_download.dir/depend

