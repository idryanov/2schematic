/**
 *  @file octomap_converter.h
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

#ifndef RGBD_2_SCHEMATIC_OCTOMAP_CONVERTER_H
#define RGBD_2_SCHEMATIC_OCTOMAP_CONVERTER_H

#include <iostream>
#include <octomap/octomap.h>
#include <octomap/ColorOcTree.h>

#include "converter.h"
#include "schematic.h"

namespace rgbd_2_schematic {

class OctomapConverter: public Converter
{ 
  public:

    OctomapConverter();

    bool load(const std::string& path);
    void setTree(octomap::ColorOcTree* tree);
    bool convert(Schematic& schematic);   
    
  private:

    octomap::ColorOcTree* tree_;
    
    // minimum of tree bbx
    double min_x_, min_y_, min_z_;
    
    // tree resolution
    double res_;   
    
    void initTreeParams();
};

} // namespace rgbd_2_schematic

#endif // RGBD_2_SCHEMATIC_OCTOMAP_CONVERTER_H
