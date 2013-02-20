# The name of our project is "HELLO". CMakeLists files in this project can 
 # refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and 
 # to the root binary directory of the project as ${HELLO_BINARY_DIR}. 
cmake_minimum_required (VERSION 2.6) 
project (RGBD2SCHEMATIC) 

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# Octomap
find_package(octomap REQUIRED)
include_directories(${OCTOMAP_INCLUDE_DIRS})
link_directories(${OCTOMAP_LIBRARY_DIRS})
link_libraries(${OCTOMAP_LIBRARIES})

include_directories(include)

# create rgbd2schematic library

add_library(rgbd2schematic
  src/converter.cpp
  src/octomap_converter.cpp
  src/writer.cpp)

target_link_libraries(rgbd2schematic z)
  
# create octomap2schematic executable  
  
add_executable(octomap2schematic
  src/octomap2schematic.cpp)

target_link_libraries(octomap2schematic rgbd2schematic)


