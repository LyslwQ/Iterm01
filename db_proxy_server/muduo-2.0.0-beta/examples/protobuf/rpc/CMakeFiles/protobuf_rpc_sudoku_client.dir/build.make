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
include examples/protobuf/rpc/CMakeFiles/protobuf_rpc_sudoku_client.dir/depend.make

# Include the progress variables for this target.
include examples/protobuf/rpc/CMakeFiles/protobuf_rpc_sudoku_client.dir/progress.make

# Include the compile flags for this target's objects.
include examples/protobuf/rpc/CMakeFiles/protobuf_rpc_sudoku_client.dir/flags.make

examples/protobuf/rpc/CMakeFiles/protobuf_rpc_sudoku_client.dir/client.cc.o: examples/protobuf/rpc/CMakeFiles/protobuf_rpc_sudoku_client.dir/flags.make
examples/protobuf/rpc/CMakeFiles/protobuf_rpc_sudoku_client.dir/client.cc.o: examples/protobuf/rpc/client.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/protobuf/rpc/CMakeFiles/protobuf_rpc_sudoku_client.dir/client.cc.o"
	cd /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/protobuf/rpc && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/protobuf_rpc_sudoku_client.dir/client.cc.o -c /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/protobuf/rpc/client.cc

examples/protobuf/rpc/CMakeFiles/protobuf_rpc_sudoku_client.dir/client.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/protobuf_rpc_sudoku_client.dir/client.cc.i"
	cd /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/protobuf/rpc && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/protobuf/rpc/client.cc > CMakeFiles/protobuf_rpc_sudoku_client.dir/client.cc.i

examples/protobuf/rpc/CMakeFiles/protobuf_rpc_sudoku_client.dir/client.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/protobuf_rpc_sudoku_client.dir/client.cc.s"
	cd /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/protobuf/rpc && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/protobuf/rpc/client.cc -o CMakeFiles/protobuf_rpc_sudoku_client.dir/client.cc.s

examples/protobuf/rpc/CMakeFiles/protobuf_rpc_sudoku_client.dir/client.cc.o.requires:
.PHONY : examples/protobuf/rpc/CMakeFiles/protobuf_rpc_sudoku_client.dir/client.cc.o.requires

examples/protobuf/rpc/CMakeFiles/protobuf_rpc_sudoku_client.dir/client.cc.o.provides: examples/protobuf/rpc/CMakeFiles/protobuf_rpc_sudoku_client.dir/client.cc.o.requires
	$(MAKE) -f examples/protobuf/rpc/CMakeFiles/protobuf_rpc_sudoku_client.dir/build.make examples/protobuf/rpc/CMakeFiles/protobuf_rpc_sudoku_client.dir/client.cc.o.provides.build
.PHONY : examples/protobuf/rpc/CMakeFiles/protobuf_rpc_sudoku_client.dir/client.cc.o.provides

examples/protobuf/rpc/CMakeFiles/protobuf_rpc_sudoku_client.dir/client.cc.o.provides.build: examples/protobuf/rpc/CMakeFiles/protobuf_rpc_sudoku_client.dir/client.cc.o

# Object files for target protobuf_rpc_sudoku_client
protobuf_rpc_sudoku_client_OBJECTS = \
"CMakeFiles/protobuf_rpc_sudoku_client.dir/client.cc.o"

# External object files for target protobuf_rpc_sudoku_client
protobuf_rpc_sudoku_client_EXTERNAL_OBJECTS =

bin/protobuf_rpc_sudoku_client: examples/protobuf/rpc/CMakeFiles/protobuf_rpc_sudoku_client.dir/client.cc.o
bin/protobuf_rpc_sudoku_client: examples/protobuf/rpc/CMakeFiles/protobuf_rpc_sudoku_client.dir/build.make
bin/protobuf_rpc_sudoku_client: lib/libsudoku_proto.a
bin/protobuf_rpc_sudoku_client: lib/libmuduo_protorpc.a
bin/protobuf_rpc_sudoku_client: lib/libmuduo_protorpc_wire.a
bin/protobuf_rpc_sudoku_client: lib/libmuduo_protobuf_codec.a
bin/protobuf_rpc_sudoku_client: lib/libmuduo_net.a
bin/protobuf_rpc_sudoku_client: lib/libmuduo_base.a
bin/protobuf_rpc_sudoku_client: examples/protobuf/rpc/CMakeFiles/protobuf_rpc_sudoku_client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../../bin/protobuf_rpc_sudoku_client"
	cd /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/protobuf/rpc && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/protobuf_rpc_sudoku_client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/protobuf/rpc/CMakeFiles/protobuf_rpc_sudoku_client.dir/build: bin/protobuf_rpc_sudoku_client
.PHONY : examples/protobuf/rpc/CMakeFiles/protobuf_rpc_sudoku_client.dir/build

examples/protobuf/rpc/CMakeFiles/protobuf_rpc_sudoku_client.dir/requires: examples/protobuf/rpc/CMakeFiles/protobuf_rpc_sudoku_client.dir/client.cc.o.requires
.PHONY : examples/protobuf/rpc/CMakeFiles/protobuf_rpc_sudoku_client.dir/requires

examples/protobuf/rpc/CMakeFiles/protobuf_rpc_sudoku_client.dir/clean:
	cd /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/protobuf/rpc && $(CMAKE_COMMAND) -P CMakeFiles/protobuf_rpc_sudoku_client.dir/cmake_clean.cmake
.PHONY : examples/protobuf/rpc/CMakeFiles/protobuf_rpc_sudoku_client.dir/clean

examples/protobuf/rpc/CMakeFiles/protobuf_rpc_sudoku_client.dir/depend:
	cd /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/protobuf/rpc /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/protobuf/rpc /home/ys/project/db_proxy_server_src9-12/muduo-2.0.0-beta/examples/protobuf/rpc/CMakeFiles/protobuf_rpc_sudoku_client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/protobuf/rpc/CMakeFiles/protobuf_rpc_sudoku_client.dir/depend

