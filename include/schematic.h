/**
 *  @file schematic.h
 *  @author Ivan Dryanovski <ivan.dryanovski@gmail.com>
 * 
 *  @section LICENSE
 * 
 *  Copyright (C) 2013, Ivan Dryanovski
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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

