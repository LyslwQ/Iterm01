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
include examples/roundtrip/CMakeFiles/roundtrip.dir/depend.make

# Include the progress variables for this target.
include examples/roundtrip/CMakeFiles/roundtrip.dir/progress.make

# Include the compile flags for this target's objects.
include examples/roundtrip/CMakeFiles/roundtrip.dir/flags.make

examples/roundtrip/CMakeFiles/roundtrip.dir/roundtrip.cc.o: examples/roundtrip/CMakeFiles/roundtrip.dir/flags.make
examples/roundtrip/CMakeFiles/roundtrip.dir/roundtrip.cc.o: examples/roundtrip/roundtrip.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/roundtrip/CMakeFiles/roundtrip.dir/roundtrip.cc.o"
	cd /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/roundtrip && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/roundtrip.dir/roundtrip.cc.o -c /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/roundtrip/roundtrip.cc

examples/roundtrip/CMakeFiles/roundtrip.dir/roundtrip.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/roundtrip.dir/roundtrip.cc.i"
	cd /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/roundtrip && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/roundtrip/roundtrip.cc > CMakeFiles/roundtrip.dir/roundtrip.cc.i

examples/roundtrip/CMakeFiles/roundtrip.dir/roundtrip.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/roundtrip.dir/roundtrip.cc.s"
	cd /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/roundtrip && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/roundtrip/roundtrip.cc -o CMakeFiles/roundtrip.dir/roundtrip.cc.s

examples/roundtrip/CMakeFiles/roundtrip.dir/roundtrip.cc.o.requires:
.PHONY : examples/roundtrip/CMakeFiles/roundtrip.dir/roundtrip.cc.o.requires

examples/roundtrip/CMakeFiles/roundtrip.dir/roundtrip.cc.o.provides: examples/roundtrip/CMakeFiles/roundtrip.dir/roundtrip.cc.o.requires
	$(MAKE) -f examples/roundtrip/CMakeFiles/roundtrip.dir/build.make examples/roundtrip/CMakeFiles/roundtrip.dir/roundtrip.cc.o.provides.build
.PHONY : examples/roundtrip/CMakeFiles/roundtrip.dir/roundtrip.cc.o.provides

examples/roundtrip/CMakeFiles/roundtrip.dir/roundtrip.cc.o.provides.build: examples/roundtrip/CMakeFiles/roundtrip.dir/roundtrip.cc.o

# Object files for target roundtrip
roundtrip_OBJECTS = \
"CMakeFiles/roundtrip.dir/roundtrip.cc.o"

# External object files for target roundtrip
roundtrip_EXTERNAL_OBJECTS =

bin/roundtrip: examples/roundtrip/CMakeFiles/roundtrip.dir/roundtrip.cc.o
bin/roundtrip: examples/roundtrip/CMakeFiles/roundtrip.dir/build.make
bin/roundtrip: lib/libmuduo_net.a
bin/roundtrip: lib/libmuduo_base.a
bin/roundtrip: examples/roundtrip/CMakeFiles/roundtrip.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../bin/roundtrip"
	cd /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/roundtrip && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/roundtrip.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/roundtrip/CMakeFiles/roundtrip.dir/build: bin/roundtrip
.PHONY : examples/roundtrip/CMakeFiles/roundtrip.dir/build

examples/roundtrip/CMakeFiles/roundtrip.dir/requires: examples/roundtrip/CMakeFiles/roundtrip.dir/roundtrip.cc.o.requires
.PHONY : examples/roundtrip/CMakeFiles/roundtrip.dir/requires

examples/roundtrip/CMakeFiles/roundtrip.dir/clean:
	cd /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/roundtrip && $(CMAKE_COMMAND) -P CMakeFiles/roundtrip.dir/cmake_clean.cmake
.PHONY : examples/roundtrip/CMakeFiles/roundtrip.dir/clean

examples/roundtrip/CMakeFiles/roundtrip.dir/depend:
	cd /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/roundtrip /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/roundtrip /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/roundtrip/CMakeFiles/roundtrip.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/roundtrip/CMakeFiles/roundtrip.dir/depend

