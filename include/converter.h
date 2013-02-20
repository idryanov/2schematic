#ifndef OCTOMAP_2_SCHEMATIC_CONVERTER_H
#define OCTOMAP_2_SCHEMATIC_CONVERTER_H

#include <iostream>
#include <octomap/octomap.h>
#include <octomap/ColorOcTree.h>

#include "schematic.h"
#include "colors.h"

class Converter
{ 
  public:

    Converter();

    void setTree(octomap::ColorOcTree* tree);
    bool convert(Schematic& schematic);
    void filter(Schematic& schematic, int window = 1);
    
  private:

    octomap::ColorOcTree* tree_;
    
    // minimum of tree bbx
    double min_x_, min_y_, min_z_;
    
    // tree resolution
    double res_;
    
    int window_;
    
    int getMaterial(int r, int g, int b);
    int getMaterialNearestRGB(int r, int g, int b);
    int getMaterialNearestHue(int r, int g, int b);
    
    void rgb2hsv(int r, int g, int b,
                 double& h, double& s, double& v);
             
    double colorDiff(const int rgb_A[3], const int rgb_B[3]);

    int getMedianColor(const Schematic& schematic, 
                       int x, int y, int z);
};

#endif // OCTOMAP_2_SCHEMATIC_CONVERTER_H
