cmake_minimum_required(VERSION 3.1)
project(Simulation_of_the_4th_Krakow_bypass)

add_definitions(-std=c++11)

set(SOURCE_FILES main.cpp)


add_executable(bypass_run ${SOURCE_FILES})

include_directories(bypass)

add_subdirectory(bypass)
add_subdirectory(bypass_tests)

target_link_libraries(bypass_run gtest gtest_main)
target_link_libraries(bypass_run basictests)
target_link_libraries(bypass_run bypass)



#if ($ENV{CLION_IDE})
#    message("Call cmake command from the CLion IDE")
#    set(CALENDAR_PATH_VAR "test")
#    set(CALENDAR_DIR_VAR "test")
#endif ()