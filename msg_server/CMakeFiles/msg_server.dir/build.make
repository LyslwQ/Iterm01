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
CMAKE_SOURCE_DIR = /home/ys/project/msg_server_src01

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ys/project/msg_server_src01

# Include any dependencies generated for this target.
include CMakeFiles/msg_server.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/msg_server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/msg_server.dir/flags.make

CMakeFiles/msg_server.dir/main.cpp.o: CMakeFiles/msg_server.dir/flags.make
CMakeFiles/msg_server.dir/main.cpp.o: main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ys/project/msg_server_src01/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/msg_server.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/msg_server.dir/main.cpp.o -c /home/ys/project/msg_server_src01/main.cpp

CMakeFiles/msg_server.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/msg_server.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ys/project/msg_server_src01/main.cpp > CMakeFiles/msg_server.dir/main.cpp.i

CMakeFiles/msg_server.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/msg_server.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ys/project/msg_server_src01/main.cpp -o CMakeFiles/msg_server.dir/main.cpp.s

CMakeFiles/msg_server.dir/main.cpp.o.requires:
.PHONY : CMakeFiles/msg_server.dir/main.cpp.o.requires

CMakeFiles/msg_server.dir/main.cpp.o.provides: CMakeFiles/msg_server.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/msg_server.dir/build.make CMakeFiles/msg_server.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/msg_server.dir/main.cpp.o.provides

CMakeFiles/msg_server.dir/main.cpp.o.provides.build: CMakeFiles/msg_server.dir/main.cpp.o

CMakeFiles/msg_server.dir/SerClientManager.cpp.o: CMakeFiles/msg_server.dir/flags.make
CMakeFiles/msg_server.dir/SerClientManager.cpp.o: SerClientManager.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ys/project/msg_server_src01/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/msg_server.dir/SerClientManager.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/msg_server.dir/SerClientManager.cpp.o -c /home/ys/project/msg_server_src01/SerClientManager.cpp

CMakeFiles/msg_server.dir/SerClientManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/msg_server.dir/SerClientManager.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ys/project/msg_server_src01/SerClientManager.cpp > CMakeFiles/msg_server.dir/SerClientManager.cpp.i

CMakeFiles/msg_server.dir/SerClientManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/msg_server.dir/SerClientManager.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ys/project/msg_server_src01/SerClientManager.cpp -o CMakeFiles/msg_server.dir/SerClientManager.cpp.s

CMakeFiles/msg_server.dir/SerClientManager.cpp.o.requires:
.PHONY : CMakeFiles/msg_server.dir/SerClientManager.cpp.o.requires

CMakeFiles/msg_server.dir/SerClientManager.cpp.o.provides: CMakeFiles/msg_server.dir/SerClientManager.cpp.o.requires
	$(MAKE) -f CMakeFiles/msg_server.dir/build.make CMakeFiles/msg_server.dir/SerClientManager.cpp.o.provides.build
.PHONY : CMakeFiles/msg_server.dir/SerClientManager.cpp.o.provides

CMakeFiles/msg_server.dir/SerClientManager.cpp.o.provides.build: CMakeFiles/msg_server.dir/SerClientManager.cpp.o

# Object files for target msg_server
msg_server_OBJECTS = \
"CMakeFiles/msg_server.dir/main.cpp.o" \
"CMakeFiles/msg_server.dir/SerClientManager.cpp.o"

# External object files for target msg_server
msg_server_EXTERNAL_OBJECTS =

msg_server: CMakeFiles/msg_server.dir/main.cpp.o
msg_server: CMakeFiles/msg_server.dir/SerClientManager.cpp.o
msg_server: CMakeFiles/msg_server.dir/build.make
msg_server: /usr/lib64/libmuduo_net.a
msg_server: /usr/lib64/libmuduo_base.a
msg_server: CMakeFiles/msg_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable msg_server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/msg_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/msg_server.dir/build: msg_server
.PHONY : CMakeFiles/msg_server.dir/build

CMakeFiles/msg_server.dir/requires: CMakeFiles/msg_server.dir/main.cpp.o.requires
CMakeFiles/msg_server.dir/requires: CMakeFiles/msg_server.dir/SerClientManager.cpp.o.requires
.PHONY : CMakeFiles/msg_server.dir/requires

CMakeFiles/msg_server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/msg_server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/msg_server.dir/clean

CMakeFiles/msg_server.dir/depend:
	cd /home/ys/project/msg_server_src01 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ys/project/msg_server_src01 /home/ys/project/msg_server_src01 /home/ys/project/msg_server_src01 /home/ys/project/msg_server_src01 /home/ys/project/msg_server_src01/CMakeFiles/msg_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/msg_server.dir/depend

