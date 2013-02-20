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

    void setTree(octomap::ColorOcTree* tree);
    bool convert(Schematic& schematic);
    
  private:

    octomap::ColorOcTree* tree_;
    
    // minimum of tree bbx
    double min_x_, min_y_, min_z_;
    
    // tree resolution
    double res_;   
};

} // namespace rgbd_2_schematic

#endif // RGBD_2_SCHEMATIC_OCTOMAP_CONVERTER_H
