#ifndef OCTOMAP_2_SCHEMATIC_SCHEMATIC_H
#define OCTOMAP_2_SCHEMATIC_SCHEMATIC_H

#include <vector>

struct Schematic
{
  std::vector<unsigned char> voxels;         
  std::vector<unsigned char> data;

  int size_x, size_y, size_z;   // size of 3d voxel grid
};

#endif // OCTOMAP_2_SCHEMATIC_SCHEMATIC_H

