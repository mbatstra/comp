cmake_minimum_required(VERSION 3.5)
project("comp" VERSION 1.0.0)

# Set C++ standard / version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/src)

# Automatically add all files in the src directory to the project
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.h")

# Add executable target with project source
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# If you have any libraries to link against, you can specify them here
# target_link_libraries(${PROJECT_NAME} library_name)
