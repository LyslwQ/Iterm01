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
include examples/ace/logging/CMakeFiles/ace_logging_client.dir/depend.make

# Include the progress variables for this target.
include examples/ace/logging/CMakeFiles/ace_logging_client.dir/progress.make

# Include the compile flags for this target's objects.
include examples/ace/logging/CMakeFiles/ace_logging_client.dir/flags.make

examples/ace/logging/CMakeFiles/ace_logging_client.dir/client.cc.o: examples/ace/logging/CMakeFiles/ace_logging_client.dir/flags.make
examples/ace/logging/CMakeFiles/ace_logging_client.dir/client.cc.o: examples/ace/logging/client.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/ace/logging/CMakeFiles/ace_logging_client.dir/client.cc.o"
	cd /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/ace/logging && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ace_logging_client.dir/client.cc.o -c /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/ace/logging/client.cc

examples/ace/logging/CMakeFiles/ace_logging_client.dir/client.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ace_logging_client.dir/client.cc.i"
	cd /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/ace/logging && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/ace/logging/client.cc > CMakeFiles/ace_logging_client.dir/client.cc.i

examples/ace/logging/CMakeFiles/ace_logging_client.dir/client.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ace_logging_client.dir/client.cc.s"
	cd /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/ace/logging && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/ace/logging/client.cc -o CMakeFiles/ace_logging_client.dir/client.cc.s

examples/ace/logging/CMakeFiles/ace_logging_client.dir/client.cc.o.requires:
.PHONY : examples/ace/logging/CMakeFiles/ace_logging_client.dir/client.cc.o.requires

examples/ace/logging/CMakeFiles/ace_logging_client.dir/client.cc.o.provides: examples/ace/logging/CMakeFiles/ace_logging_client.dir/client.cc.o.requires
	$(MAKE) -f examples/ace/logging/CMakeFiles/ace_logging_client.dir/build.make examples/ace/logging/CMakeFiles/ace_logging_client.dir/client.cc.o.provides.build
.PHONY : examples/ace/logging/CMakeFiles/ace_logging_client.dir/client.cc.o.provides

examples/ace/logging/CMakeFiles/ace_logging_client.dir/client.cc.o.provides.build: examples/ace/logging/CMakeFiles/ace_logging_client.dir/client.cc.o

# Object files for target ace_logging_client
ace_logging_client_OBJECTS = \
"CMakeFiles/ace_logging_client.dir/client.cc.o"

# External object files for target ace_logging_client
ace_logging_client_EXTERNAL_OBJECTS =

bin/ace_logging_client: examples/ace/logging/CMakeFiles/ace_logging_client.dir/client.cc.o
bin/ace_logging_client: examples/ace/logging/CMakeFiles/ace_logging_client.dir/build.make
bin/ace_logging_client: lib/libmuduo_protobuf_codec.a
bin/ace_logging_client: lib/libace_logging_proto.a
bin/ace_logging_client: lib/libmuduo_net.a
bin/ace_logging_client: lib/libmuduo_base.a
bin/ace_logging_client: examples/ace/logging/CMakeFiles/ace_logging_client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../../bin/ace_logging_client"
	cd /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/ace/logging && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ace_logging_client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/ace/logging/CMakeFiles/ace_logging_client.dir/build: bin/ace_logging_client
.PHONY : examples/ace/logging/CMakeFiles/ace_logging_client.dir/build

examples/ace/logging/CMakeFiles/ace_logging_client.dir/requires: examples/ace/logging/CMakeFiles/ace_logging_client.dir/client.cc.o.requires
.PHONY : examples/ace/logging/CMakeFiles/ace_logging_client.dir/requires

examples/ace/logging/CMakeFiles/ace_logging_client.dir/clean:
	cd /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/ace/logging && $(CMAKE_COMMAND) -P CMakeFiles/ace_logging_client.dir/cmake_clean.cmake
.PHONY : examples/ace/logging/CMakeFiles/ace_logging_client.dir/clean

examples/ace/logging/CMakeFiles/ace_logging_client.dir/depend:
	cd /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/ace/logging /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/ace/logging /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/ace/logging/CMakeFiles/ace_logging_client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/ace/logging/CMakeFiles/ace_logging_client.dir/depend

