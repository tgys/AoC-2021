# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /nix/store/h240v616x2b9j3sbsiw7m58df47q91vn-cmake-3.19.7/bin/cmake

# The command to remove a file.
RM = /nix/store/h240v616x2b9j3sbsiw7m58df47q91vn-cmake-3.19.7/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tei/projects/cpp/scratch

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tei/projects/cpp/scratch/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/day_12_pt2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/day_12_pt2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/day_12_pt2.dir/flags.make

CMakeFiles/day_12_pt2.dir/day_12_pt2.cpp.o: CMakeFiles/day_12_pt2.dir/flags.make
CMakeFiles/day_12_pt2.dir/day_12_pt2.cpp.o: ../day_12_pt2.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tei/projects/cpp/scratch/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/day_12_pt2.dir/day_12_pt2.cpp.o"
	/run/current-system/sw/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/day_12_pt2.dir/day_12_pt2.cpp.o -c /home/tei/projects/cpp/scratch/day_12_pt2.cpp

CMakeFiles/day_12_pt2.dir/day_12_pt2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/day_12_pt2.dir/day_12_pt2.cpp.i"
	/run/current-system/sw/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tei/projects/cpp/scratch/day_12_pt2.cpp > CMakeFiles/day_12_pt2.dir/day_12_pt2.cpp.i

CMakeFiles/day_12_pt2.dir/day_12_pt2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/day_12_pt2.dir/day_12_pt2.cpp.s"
	/run/current-system/sw/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tei/projects/cpp/scratch/day_12_pt2.cpp -o CMakeFiles/day_12_pt2.dir/day_12_pt2.cpp.s

# Object files for target day_12_pt2
day_12_pt2_OBJECTS = \
"CMakeFiles/day_12_pt2.dir/day_12_pt2.cpp.o"

# External object files for target day_12_pt2
day_12_pt2_EXTERNAL_OBJECTS =

day_12_pt2: CMakeFiles/day_12_pt2.dir/day_12_pt2.cpp.o
day_12_pt2: CMakeFiles/day_12_pt2.dir/build.make
day_12_pt2: CMakeFiles/day_12_pt2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tei/projects/cpp/scratch/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable day_12_pt2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/day_12_pt2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/day_12_pt2.dir/build: day_12_pt2

.PHONY : CMakeFiles/day_12_pt2.dir/build

CMakeFiles/day_12_pt2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/day_12_pt2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/day_12_pt2.dir/clean

CMakeFiles/day_12_pt2.dir/depend:
	cd /home/tei/projects/cpp/scratch/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tei/projects/cpp/scratch /home/tei/projects/cpp/scratch /home/tei/projects/cpp/scratch/cmake-build-debug /home/tei/projects/cpp/scratch/cmake-build-debug /home/tei/projects/cpp/scratch/cmake-build-debug/CMakeFiles/day_12_pt2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/day_12_pt2.dir/depend
