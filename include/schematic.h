#ifndef RGBD_2_SCHEMATIC_SCHEMATIC_H
#define RGBD_2_SCHEMATIC_SCHEMATIC_H

#include <vector>

namespace rgbd_2_schematic {

struct Schematic
{
  std::vector<unsigned char> voxels;         
  std::vector<unsigned char> data;

  int size_x, size_y, size_z;   // size of 3d voxel grid
};

} // namespace rgbd_2_schematic

#endif // RGBD_2_SCHEMATIC_SCHEMATIC_H

