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
CMAKE_COMMAND = /opt/clion-2019.1.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion-2019.1.2/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/fajcon/symulacja/Simulation_of_the_4th_Krakow_bypass

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/fajcon/symulacja/Simulation_of_the_4th_Krakow_bypass/cmake-build-debug

# Include any dependencies generated for this target.
include bypass_tests/lib/googletest-master/googlemock/gtest/CMakeFiles/gtest.dir/depend.make

# Include the progress variables for this target.
include bypass_tests/lib/googletest-master/googlemock/gtest/CMakeFiles/gtest.dir/progress.make

# Include the compile flags for this target's objects.
include bypass_tests/lib/googletest-master/googlemock/gtest/CMakeFiles/gtest.dir/flags.make

bypass_tests/lib/googletest-master/googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o: bypass_tests/lib/googletest-master/googlemock/gtest/CMakeFiles/gtest.dir/flags.make
bypass_tests/lib/googletest-master/googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o: ../bypass_tests/lib/googletest-master/googletest/src/gtest-all.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fajcon/symulacja/Simulation_of_the_4th_Krakow_bypass/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object bypass_tests/lib/googletest-master/googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o"
	cd /home/fajcon/symulacja/Simulation_of_the_4th_Krakow_bypass/cmake-build-debug/bypass_tests/lib/googletest-master/googlemock/gtest && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gtest.dir/src/gtest-all.cc.o -c /home/fajcon/symulacja/Simulation_of_the_4th_Krakow_bypass/bypass_tests/lib/googletest-master/googletest/src/gtest-all.cc

bypass_tests/lib/googletest-master/googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gtest.dir/src/gtest-all.cc.i"
	cd /home/fajcon/symulacja/Simulation_of_the_4th_Krakow_bypass/cmake-build-debug/bypass_tests/lib/googletest-master/googlemock/gtest && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/fajcon/symulacja/Simulation_of_the_4th_Krakow_bypass/bypass_tests/lib/googletest-master/googletest/src/gtest-all.cc > CMakeFiles/gtest.dir/src/gtest-all.cc.i

bypass_tests/lib/googletest-master/googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gtest.dir/src/gtest-all.cc.s"
	cd /home/fajcon/symulacja/Simulation_of_the_4th_Krakow_bypass/cmake-build-debug/bypass_tests/lib/googletest-master/googlemock/gtest && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/fajcon/symulacja/Simulation_of_the_4th_Krakow_bypass/bypass_tests/lib/googletest-master/googletest/src/gtest-all.cc -o CMakeFiles/gtest.dir/src/gtest-all.cc.s

# Object files for target gtest
gtest_OBJECTS = \
"CMakeFiles/gtest.dir/src/gtest-all.cc.o"

# External object files for target gtest
gtest_EXTERNAL_OBJECTS =

lib/libgtestd.a: bypass_tests/lib/googletest-master/googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o
lib/libgtestd.a: bypass_tests/lib/googletest-master/googlemock/gtest/CMakeFiles/gtest.dir/build.make
lib/libgtestd.a: bypass_tests/lib/googletest-master/googlemock/gtest/CMakeFiles/gtest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/fajcon/symulacja/Simulation_of_the_4th_Krakow_bypass/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ../../../../../lib/libgtestd.a"
	cd /home/fajcon/symulacja/Simulation_of_the_4th_Krakow_bypass/cmake-build-debug/bypass_tests/lib/googletest-master/googlemock/gtest && $(CMAKE_COMMAND) -P CMakeFiles/gtest.dir/cmake_clean_target.cmake
	cd /home/fajcon/symulacja/Simulation_of_the_4th_Krakow_bypass/cmake-build-debug/bypass_tests/lib/googletest-master/googlemock/gtest && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gtest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
bypass_tests/lib/googletest-master/googlemock/gtest/CMakeFiles/gtest.dir/build: lib/libgtestd.a

.PHONY : bypass_tests/lib/googletest-master/googlemock/gtest/CMakeFiles/gtest.dir/build

bypass_tests/lib/googletest-master/googlemock/gtest/CMakeFiles/gtest.dir/clean:
	cd /home/fajcon/symulacja/Simulation_of_the_4th_Krakow_bypass/cmake-build-debug/bypass_tests/lib/googletest-master/googlemock/gtest && $(CMAKE_COMMAND) -P CMakeFiles/gtest.dir/cmake_clean.cmake
.PHONY : bypass_tests/lib/googletest-master/googlemock/gtest/CMakeFiles/gtest.dir/clean

bypass_tests/lib/googletest-master/googlemock/gtest/CMakeFiles/gtest.dir/depend:
	cd /home/fajcon/symulacja/Simulation_of_the_4th_Krakow_bypass/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/fajcon/symulacja/Simulation_of_the_4th_Krakow_bypass /home/fajcon/symulacja/Simulation_of_the_4th_Krakow_bypass/bypass_tests/lib/googletest-master/googletest /home/fajcon/symulacja/Simulation_of_the_4th_Krakow_bypass/cmake-build-debug /home/fajcon/symulacja/Simulation_of_the_4th_Krakow_bypass/cmake-build-debug/bypass_tests/lib/googletest-master/googlemock/gtest /home/fajcon/symulacja/Simulation_of_the_4th_Krakow_bypass/cmake-build-debug/bypass_tests/lib/googletest-master/googlemock/gtest/CMakeFiles/gtest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : bypass_tests/lib/googletest-master/googlemock/gtest/CMakeFiles/gtest.dir/depend

