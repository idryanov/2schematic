/**
 *  @file pcd_converter.cpp
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

#include "pcd_converter.h"

namespace rgbd_2_schematic {

using namespace std;

PcdConverter::PcdConverter():Converter(),
  res_(0.05)
{

}

void PcdConverter::setResolution(double resolution)
{
  res_ = resolution;
}
  
bool PcdConverter::load(const std::string& path)
{
  cloud_.reset(new PointCloudT());
 
  cout << "Opening " << path << "..." << endl;  
  
  int load_result = pcl::io::loadPCDFile<PointT> (path, *cloud_);

  if (load_result != -1)
  {
    return true;
  }
  else
  {
    cout << "ERROR: could not load " << path << endl;
    return false;
  } 
}

void PcdConverter::setCloud(PointCloudT::Ptr cloud)
{
  cloud_ = cloud;

}

bool PcdConverter::convert(Schematic& schematic)
{
  if (!cloud_)
  {
    cout << "ERROR: cloud is not set" << endl;
    return false;
  }

  cout << "Converting PointCloud to schematic..." << endl;

  // create filtered cloud
  PointCloudT cloud_f;
  pcl::VoxelGrid<PointT> vgf;
  vgf.setInputCloud(cloud_);
  vgf.setLeafSize(res_, res_, res_);
  vgf.filter(cloud_f);
  
  // calculate size in meters 
  PointT p_min, p_max;
  pcl::getMinMax3D (cloud_f, p_min, p_max);
  
  double dx = p_max.x - p_min.x;
  double dy = p_max.y - p_min.y;
  double dz = p_max.z - p_min.z;  
      
  // calculate size in voxel units
  int sx = (dx / res_) + 1;  
  int sy = (dy / res_) + 1;  
  int sz = (dz / res_) + 1;  
  
  schematic.size_x = sx;
  schematic.size_y = sy;
  schematic.size_z = sz;

  // resize to full 3d scale
  unsigned int size = sx * sy * sz;
  schematic.voxels.resize(size);
  schematic.data.resize(size);
  
  // initialize voxels and data to 0     
  for (unsigned int idx = 0; idx < size; ++idx)
  {    
    schematic.voxels[idx] = 0;     
    schematic.data[idx] = 0;     
  }
  
  for (unsigned int pt_idx = 0; pt_idx < cloud_f.points.size(); ++pt_idx)
  {
    const PointT& p = cloud_f.points[pt_idx];
    
    // in voxel coords
    int x = (p.x - p_min.x) / res_;
    int y = (p.y - p_min.y) / res_;
    int z = (p.z - p_min.z) / res_;  
        
    // the idnex in the voxel grid
    int idx = z * (sx * sy) + x * sy + y;
    
    // set material type: wool
    schematic.voxels[idx] = 35;
    
    // set material data, based on color   
    schematic.data[idx] = getMaterial(p.r, p.g, p.b); 
  }
      
  return true;
}

} // namespace rgbd_2_schematic
