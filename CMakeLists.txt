cmake_minimum_required (VERSION 2.6) 
project (RGBD2SCHEMATIC) 

include_directories(include)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# Octomap
find_package(octomap)

if (OCTOMAP_FOUND) 
  include_directories(${OCTOMAP_INCLUDE_DIRS})
  link_directories(${OCTOMAP_LIBRARY_DIRS})
  link_libraries(${OCTOMAP_LIBRARIES})
else()
  message("Octomap not found. Disabling octomap2schematic build.")
endif (OCTOMAP_FOUND)
  
# PCL
find_package(PCL COMPONENTS common io filters)

if (PCL_FOUND) 
  include_directories(${PCL_INCLUDE_DIRS})
  link_directories(${PCL_LIBRARY_DIRS})
  add_definitions(${PCL_DEFINITIONS})
else()
  message("PCL not found. Disabling pcd2schematic build.")
endif (PCL_FOUND) 
  
  
##############################################
# create rgbd2schematic common library

add_library(rgbd2schematic
  src/converter.cpp
  src/writer.cpp)

target_link_libraries(rgbd2schematic z)

##############################################
# create octomap2schematic executable  

if (OCTOMAP_FOUND) 
  add_executable(octomap2schematic
    src/octomap_converter.cpp
    src/octomap2schematic.cpp)

  target_link_libraries(octomap2schematic rgbd2schematic)
endif (OCTOMAP_FOUND)
  
##############################################
# create pcd2schematic executable  
  
if (PCL_FOUND)   
  add_executable(pcd2schematic
    src/pcd_converter.cpp
    src/pcd2schematic.cpp)

  target_link_libraries(pcd2schematic rgbd2schematic)
  target_link_libraries(rgbd2schematic ${PCL_LIBRARIES})
endif (PCL_FOUND)


