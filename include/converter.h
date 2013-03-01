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

    enum MaterialMode {
      WOOL_HUE_COLOR,
      WOOL_HEIGHT_COLOR,
      STONE
    };

    Converter();

    bool convert(Schematic& schematic);

    virtual bool load(const std::string& path) = 0;
    
    virtual bool convertData(Schematic& schematic) = 0;
    
    void filter(Schematic& schematic);

    void setMaterialMode(MaterialMode mode);
    
    void setColorFilterWindow(int window);

  protected:   
    
    int getMaterial(const Schematic& schematic, int x, int y, int z) const;

    int getMaterialColor(const Schematic& schematic,
                         int x, int y, int z,
                         int r, int g, int b) const;

  private:
   
    int window_;
    
    MaterialMode mode_;

    int getMedianColor(const Schematic& schematic, 
                       int x, int y, int z);

    int getMaterialColorByHeight(const Schematic& schematic, int z) const;

    int getMaterialColorNearestRGB(int r, int g, int b) const;
    int getMaterialColorNearestHue(int r, int g, int b) const;

    void rgb2hsv(int r, int g, int b,
                 double& h, double& s, double& v) const;

    double colorDiff(const int rgb_A[3], const int rgb_B[3]) const;
};

} // namespace rgbd_2_schematic

#endif // RGBD_2_SCHEMATIC_CONVERTER_H
