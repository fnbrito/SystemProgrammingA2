# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

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
CMAKE_COMMAND = /home/filipe/Tools/clion-2020.3.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/filipe/Tools/clion-2020.3.2/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/filipe/CLionProjects/encodeInput

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/filipe/CLionProjects/encodeInput/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/encodeInput.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/encodeInput.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/encodeInput.dir/flags.make

CMakeFiles/encodeInput.dir/src/main.c.o: CMakeFiles/encodeInput.dir/flags.make
CMakeFiles/encodeInput.dir/src/main.c.o: ../src/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/filipe/CLionProjects/encodeInput/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/encodeInput.dir/src/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/encodeInput.dir/src/main.c.o   -c /home/filipe/CLionProjects/encodeInput/src/main.c

CMakeFiles/encodeInput.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/encodeInput.dir/src/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/filipe/CLionProjects/encodeInput/src/main.c > CMakeFiles/encodeInput.dir/src/main.c.i

CMakeFiles/encodeInput.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/encodeInput.dir/src/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/filipe/CLionProjects/encodeInput/src/main.c -o CMakeFiles/encodeInput.dir/src/main.c.s

# Object files for target encodeInput
encodeInput_OBJECTS = \
"CMakeFiles/encodeInput.dir/src/main.c.o"

# External object files for target encodeInput
encodeInput_EXTERNAL_OBJECTS =

encodeInput: CMakeFiles/encodeInput.dir/src/main.c.o
encodeInput: CMakeFiles/encodeInput.dir/build.make
encodeInput: CMakeFiles/encodeInput.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/filipe/CLionProjects/encodeInput/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable encodeInput"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/encodeInput.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/encodeInput.dir/build: encodeInput

.PHONY : CMakeFiles/encodeInput.dir/build

CMakeFiles/encodeInput.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/encodeInput.dir/cmake_clean.cmake
.PHONY : CMakeFiles/encodeInput.dir/clean

CMakeFiles/encodeInput.dir/depend:
	cd /home/filipe/CLionProjects/encodeInput/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/filipe/CLionProjects/encodeInput /home/filipe/CLionProjects/encodeInput /home/filipe/CLionProjects/encodeInput/cmake-build-debug /home/filipe/CLionProjects/encodeInput/cmake-build-debug /home/filipe/CLionProjects/encodeInput/cmake-build-debug/CMakeFiles/encodeInput.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/encodeInput.dir/depend

