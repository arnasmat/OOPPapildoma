cmake_minimum_required(VERSION 3.25)
project(OOPPapildoma)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR})


add_executable(OOPPapildoma ${SOURCES})
