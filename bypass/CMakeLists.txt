project(bypass)

set(HEADER_FILES
        Vehicle.hpp
        Car.hpp
        Bypass.hpp
        Simulation.hpp
        BypassSection.hpp
        Road.hpp
        Junction.hpp
        )

set(SOURCE_FILES
        Car.cpp
        Bypass.cpp
        Simulation.cpp
        BypassSection.cpp
        Road.cpp
        Junction.cpp
        )

add_library(bypass STATIC ${SOURCE_FILES} ${HEADER_FILES})
