cmake_minimum_required(VERSION 3.10)

# Project name and version
project(swaption_pricer VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Main executable
add_executable(swaption_pricer ${SOURCES} main.cpp)

# Enable warnings and optimizations
if(CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(swaption_pricer PRIVATE -Wall -Wextra -Wpedantic -O2)
endif()

# Find Google Test
find_package(GTest REQUIRED)

# Enable testing
enable_testing()
add_subdirectory(tests)

