/**
 *  @file octomap_converter.cpp
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

#include "octomap_converter.h"

namespace rgbd_2_schematic {

using namespace std;

OctomapConverter::OctomapConverter():Converter()
{

}

bool OctomapConverter::load(const std::string& path)
{
  cout << "Opening " << path << "..." << endl;  
   
  octomap::AbstractOcTree* atree = octomap::AbstractOcTree::read(path);
  
  if (atree && atree->getTreeType() == "ColorOcTree")
  {
    tree_ = dynamic_cast<octomap::ColorOcTree*>(atree);
    initTreeParams();
    return true;
  }
  else
  {
    cout << "ERROR: Octree not found, or not ColorOcTree" << endl;
    return false;
  } 
}

void OctomapConverter::initTreeParams()
{
  // minimum of tree bbx
  tree_->getMetricMin(min_x_, min_y_, min_z_);

  // tree resolution
  res_ = tree_->getResolution();
}

void OctomapConverter::setTree(octomap::ColorOcTree* tree)
{
  tree_ = tree;

  initTreeParams();
}

bool OctomapConverter::convert(Schematic& schematic)
{
  if (!tree_)
  {
    cout << "ERROR: tree is not set" << endl;
    return false;
  }

  cout << "Converting Octomap to schematic..." << endl;

  // calculate size in meters
  double dx, dy, dz;
  tree_->getMetricSize(dx, dy, dz);   
  
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
  
  // iterate octomap dimensions       
  for (unsigned int z = 0; z < sz; ++z)    
  for (unsigned int x = 0; x < sx; ++x)
  for (unsigned int y = 0; y < sy; ++y)
  {            
    int idx = z * (sx * sy) + x * sy + y;
  
    double px = (x + 0.5) * res_ + min_x_;
    double py = (y + 0.5) * res_ + min_y_;
    double pz = (z + 0.5) * res_ + min_z_;
    
    octomap::point3d p(px, py, pz);     
    
    octomap::ColorOcTreeNode* n = tree_->search(p);
    
    if (n && n->getValue() >= 0.7)
    {
      octomap::ColorOcTreeNode::Color color = n->getColor();
        
      // set material type: wool
      schematic.voxels[idx] = 35;
      
      // set material data, based on color
      schematic.data[idx] = getMaterial(color.r, color.g, color.b); 
    }
  }
  
  return true;
}

} // namespace rgbd_2_schematic