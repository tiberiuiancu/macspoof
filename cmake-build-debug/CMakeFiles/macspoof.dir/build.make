# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /usr/share/clion-2018.3.3/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /usr/share/clion-2018.3.3/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tiberiu/Desktop/macspoof

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tiberiu/Desktop/macspoof/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/macspoof.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/macspoof.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/macspoof.dir/flags.make

CMakeFiles/macspoof.dir/main.cpp.o: CMakeFiles/macspoof.dir/flags.make
CMakeFiles/macspoof.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tiberiu/Desktop/macspoof/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/macspoof.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/macspoof.dir/main.cpp.o -c /home/tiberiu/Desktop/macspoof/main.cpp

CMakeFiles/macspoof.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/macspoof.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tiberiu/Desktop/macspoof/main.cpp > CMakeFiles/macspoof.dir/main.cpp.i

CMakeFiles/macspoof.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/macspoof.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tiberiu/Desktop/macspoof/main.cpp -o CMakeFiles/macspoof.dir/main.cpp.s

# Object files for target macspoof
macspoof_OBJECTS = \
"CMakeFiles/macspoof.dir/main.cpp.o"

# External object files for target macspoof
macspoof_EXTERNAL_OBJECTS =

macspoof: CMakeFiles/macspoof.dir/main.cpp.o
macspoof: CMakeFiles/macspoof.dir/build.make
macspoof: CMakeFiles/macspoof.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tiberiu/Desktop/macspoof/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable macspoof"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/macspoof.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/macspoof.dir/build: macspoof

.PHONY : CMakeFiles/macspoof.dir/build

CMakeFiles/macspoof.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/macspoof.dir/cmake_clean.cmake
.PHONY : CMakeFiles/macspoof.dir/clean

CMakeFiles/macspoof.dir/depend:
	cd /home/tiberiu/Desktop/macspoof/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tiberiu/Desktop/macspoof /home/tiberiu/Desktop/macspoof /home/tiberiu/Desktop/macspoof/cmake-build-debug /home/tiberiu/Desktop/macspoof/cmake-build-debug /home/tiberiu/Desktop/macspoof/cmake-build-debug/CMakeFiles/macspoof.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/macspoof.dir/depend
