cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(InstantRestartMod VERSION 1.0.0)

# Include Geode SDK macros
find_package(Geode REQUIRED)

# Add source files
add_geode_mod(
    ${PROJECT_NAME}
    SOURCES
        src/main.cpp
)
