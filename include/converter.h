#ifndef RGBD_2_SCHEMATIC_CONVERTER_H
#define RGBD_2_SCHEMATIC_CONVERTER_H

#include <iostream>
#include <math.h>

#include "schematic.h"
#include "colors.h"

namespace rgbd_2_schematic {

class Converter
{ 
  public:

    Converter();

    virtual bool convert(Schematic& schematic) = 0;
    
    void filter(Schematic& schematic, int window = 1);
    
  protected:   
    
    int getMaterial(int r, int g, int b);
    int getMaterialNearestRGB(int r, int g, int b);
    int getMaterialNearestHue(int r, int g, int b);
    
    void rgb2hsv(int r, int g, int b,
                 double& h, double& s, double& v);
             
    double colorDiff(const int rgb_A[3], const int rgb_B[3]);
    
  private:
   
    int window_;
    
    int getMedianColor(const Schematic& schematic, 
                       int x, int y, int z);
};

} // namespace rgbd_2_schematic

#endif // RGBD_2_SCHEMATIC_CONVERTER_H
