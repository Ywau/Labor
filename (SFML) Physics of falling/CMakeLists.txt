cmake_minimum_required(VERSION 3.13)  # CMake version check

project(pictures)               # Create project "simple_example"

set(CMAKE_CXX_STANDARD 17)            # Enable c++14 standard

# Add main.cpp file of the project root directory as a source file
set(SOURCE_FILES src/main.cpp)

#find_package(SFML COMPONENTS graphics audio REQUIRED)
# Add executable target with source files listed in SOURCE_FILES variable
add_executable(app ${SOURCE_FILES})
add_subdirectory(SFML)
target_link_libraries(app sfml-graphics)

