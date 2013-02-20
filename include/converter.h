/**
 *  @file converter.h
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
    
    virtual bool load(const std::string& path) = 0;
    
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
