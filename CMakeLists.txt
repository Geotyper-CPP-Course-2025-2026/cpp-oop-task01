cmake_minimum_required(VERSION 3.10)
project(FileSystem VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/File.cpp
    src/Directory.cpp
)

# Create library
add_library(filesystem_lib ${SOURCES})

# Test executable
add_executable(test_runner tests/test_runner.cpp)
target_link_libraries(test_runner filesystem_lib)

# Enable testing
enable_testing()
add_test(NAME FileSystemTests COMMAND test_runner)
