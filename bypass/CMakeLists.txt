project(bypass)

set(HEADER_FILES
        Vehicle.hpp
        Car.hpp
        Bypass.hpp
        Simulation.hpp
        )

set(SOURCE_FILES
        Car.cpp
        Bypass.cpp
        Simulation.cpp
        )

add_library(bypass STATIC ${SOURCE_FILES} ${HEADER_FILES})
