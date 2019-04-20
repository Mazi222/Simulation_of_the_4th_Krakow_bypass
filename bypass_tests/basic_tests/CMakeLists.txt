project(basic_tests)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runBasicCalendarTests
        basic_check.cpp
        basic_check.hpp)

target_link_libraries(runBasicCalendarTests gtest gtest_main)
target_link_libraries(runBasicCalendarTests bypass)

set(SOURCE_FILES
        basic_check.cpp)

set(HEADER_FILES
        basic_check.hpp vehicle_check.cpp)
add_library(basictests STATIC ${SOURCE_FILES} ${HEADER_FILES})
