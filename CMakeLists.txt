cmake_minimum_required(VERSION 2.6)

# Name of project
project(CustomMemory)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify project files: header files and source files
file(GLOB SOURCES
    Source/Public/*.h
    Source/Private/*.cpp
)

# Add executable based on the source files
add_executable(CustomMemory ${SOURCES})

# Other libraries needed
include_directories(Source/Public)

# The rules here are specific to Windows Systems
if(WIN32)
    # Avoid ZERO_CHECK target in Visual Studio
    set(CMAKE_SUPPRESS_REGENERATION TRUE)
 
    # This will use the proper libraries in debug mode in Visual Studio
    set_target_properties(CustomMemory PROPERTIES DEBUG_POSTFIX _d)
endif(WIN32)
