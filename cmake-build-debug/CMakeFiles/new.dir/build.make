# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/Lital/Desktop/new

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/Lital/Desktop/new/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/new.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/new.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/new.dir/flags.make

CMakeFiles/new.dir/anomaly_detection_util.cpp.o: CMakeFiles/new.dir/flags.make
CMakeFiles/new.dir/anomaly_detection_util.cpp.o: ../anomaly_detection_util.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Lital/Desktop/new/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/new.dir/anomaly_detection_util.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/new.dir/anomaly_detection_util.cpp.o -c /mnt/c/Users/Lital/Desktop/new/anomaly_detection_util.cpp

CMakeFiles/new.dir/anomaly_detection_util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/new.dir/anomaly_detection_util.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Lital/Desktop/new/anomaly_detection_util.cpp > CMakeFiles/new.dir/anomaly_detection_util.cpp.i

CMakeFiles/new.dir/anomaly_detection_util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/new.dir/anomaly_detection_util.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Lital/Desktop/new/anomaly_detection_util.cpp -o CMakeFiles/new.dir/anomaly_detection_util.cpp.s

CMakeFiles/new.dir/MainTrain.cpp.o: CMakeFiles/new.dir/flags.make
CMakeFiles/new.dir/MainTrain.cpp.o: ../MainTrain.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Lital/Desktop/new/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/new.dir/MainTrain.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/new.dir/MainTrain.cpp.o -c /mnt/c/Users/Lital/Desktop/new/MainTrain.cpp

CMakeFiles/new.dir/MainTrain.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/new.dir/MainTrain.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Lital/Desktop/new/MainTrain.cpp > CMakeFiles/new.dir/MainTrain.cpp.i

CMakeFiles/new.dir/MainTrain.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/new.dir/MainTrain.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Lital/Desktop/new/MainTrain.cpp -o CMakeFiles/new.dir/MainTrain.cpp.s

# Object files for target new
new_OBJECTS = \
"CMakeFiles/new.dir/anomaly_detection_util.cpp.o" \
"CMakeFiles/new.dir/MainTrain.cpp.o"

# External object files for target new
new_EXTERNAL_OBJECTS =

new: CMakeFiles/new.dir/anomaly_detection_util.cpp.o
new: CMakeFiles/new.dir/MainTrain.cpp.o
new: CMakeFiles/new.dir/build.make
new: CMakeFiles/new.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/Lital/Desktop/new/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable new"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/new.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/new.dir/build: new

.PHONY : CMakeFiles/new.dir/build

CMakeFiles/new.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/new.dir/cmake_clean.cmake
.PHONY : CMakeFiles/new.dir/clean

CMakeFiles/new.dir/depend:
	cd /mnt/c/Users/Lital/Desktop/new/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/Lital/Desktop/new /mnt/c/Users/Lital/Desktop/new /mnt/c/Users/Lital/Desktop/new/cmake-build-debug /mnt/c/Users/Lital/Desktop/new/cmake-build-debug /mnt/c/Users/Lital/Desktop/new/cmake-build-debug/CMakeFiles/new.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/new.dir/depend

