/**
 *  @file pcd_converter.h
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

#ifndef RGBD_2_SCHEMATIC_PCD_CONVERTER_H
#define RGBD_2_SCHEMATIC_PCD_CONVERTER_H

#include <iostream>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>

#include "converter.h"
#include "schematic.h"

namespace rgbd_2_schematic {

typedef pcl::PointXYZRGB        PointT;
typedef pcl::PointCloud<PointT> PointCloudT;
  
class PcdConverter: public Converter
{ 
  public:

    PcdConverter();

    bool load(const std::string& path);
    void setCloud(PointCloudT::Ptr cloud);
    bool convert(Schematic& schematic);
    
  private:

    PointCloudT::Ptr cloud_;
    
    // minimum of cloud bbx
    double min_x_, min_y_, min_z_;
    
    // resolution
    double res_;   
};

} // namespace rgbd_2_schematic

#endif // RGBD_2_SCHEMATIC_PCD_CONVERTER_H
