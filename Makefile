# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_BINARY_DIR = /home/tei/projects/cpp/scratch

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/nix/store/h240v616x2b9j3sbsiw7m58df47q91vn-cmake-3.19.7/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/nix/store/h240v616x2b9j3sbsiw7m58df47q91vn-cmake-3.19.7/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/tei/projects/cpp/scratch/CMakeFiles /home/tei/projects/cpp/scratch//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/tei/projects/cpp/scratch/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named day_three

# Build rule for target.
day_three: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 day_three
.PHONY : day_three

# fast build rule for target.
day_three/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/day_three.dir/build.make CMakeFiles/day_three.dir/build
.PHONY : day_three/fast

#=============================================================================
# Target rules for targets named day_two

# Build rule for target.
day_two: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 day_two
.PHONY : day_two

# fast build rule for target.
day_two/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/day_two.dir/build.make CMakeFiles/day_two.dir/build
.PHONY : day_two/fast

#=============================================================================
# Target rules for targets named day_one

# Build rule for target.
day_one: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 day_one
.PHONY : day_one

# fast build rule for target.
day_one/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/day_one.dir/build.make CMakeFiles/day_one.dir/build
.PHONY : day_one/fast

day_one.o: day_one.cpp.o

.PHONY : day_one.o

# target to build an object file
day_one.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/day_one.dir/build.make CMakeFiles/day_one.dir/day_one.cpp.o
.PHONY : day_one.cpp.o

day_one.i: day_one.cpp.i

.PHONY : day_one.i

# target to preprocess a source file
day_one.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/day_one.dir/build.make CMakeFiles/day_one.dir/day_one.cpp.i
.PHONY : day_one.cpp.i

day_one.s: day_one.cpp.s

.PHONY : day_one.s

# target to generate assembly for a file
day_one.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/day_one.dir/build.make CMakeFiles/day_one.dir/day_one.cpp.s
.PHONY : day_one.cpp.s

day_three.o: day_three.cpp.o

.PHONY : day_three.o

# target to build an object file
day_three.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/day_three.dir/build.make CMakeFiles/day_three.dir/day_three.cpp.o
.PHONY : day_three.cpp.o

day_three.i: day_three.cpp.i

.PHONY : day_three.i

# target to preprocess a source file
day_three.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/day_three.dir/build.make CMakeFiles/day_three.dir/day_three.cpp.i
.PHONY : day_three.cpp.i

day_three.s: day_three.cpp.s

.PHONY : day_three.s

# target to generate assembly for a file
day_three.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/day_three.dir/build.make CMakeFiles/day_three.dir/day_three.cpp.s
.PHONY : day_three.cpp.s

day_two.o: day_two.cpp.o

.PHONY : day_two.o

# target to build an object file
day_two.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/day_two.dir/build.make CMakeFiles/day_two.dir/day_two.cpp.o
.PHONY : day_two.cpp.o

day_two.i: day_two.cpp.i

.PHONY : day_two.i

# target to preprocess a source file
day_two.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/day_two.dir/build.make CMakeFiles/day_two.dir/day_two.cpp.i
.PHONY : day_two.cpp.i

day_two.s: day_two.cpp.s

.PHONY : day_two.s

# target to generate assembly for a file
day_two.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/day_two.dir/build.make CMakeFiles/day_two.dir/day_two.cpp.s
.PHONY : day_two.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... day_one"
	@echo "... day_three"
	@echo "... day_two"
	@echo "... day_one.o"
	@echo "... day_one.i"
	@echo "... day_one.s"
	@echo "... day_three.o"
	@echo "... day_three.i"
	@echo "... day_three.s"
	@echo "... day_two.o"
	@echo "... day_two.i"
	@echo "... day_two.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

