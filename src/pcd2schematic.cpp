/**
 *  @file pcd2schematic.cpp
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

#include "pcd2schematic.h"

using namespace std;
using namespace rgbd_2_schematic;

int main(int argc, char** argv)
{
  // get parameters
  if (argc != 5)
  {
    cout << "ERROR: Usage is " << argv[0]; 
    cout << " input.pcd output.schematic resolution filter_window" << endl;
    return -1;
  }
  
  const string input_path  = argv[1];
  const string output_path = argv[2];
  double resolution = atof(argv[3]);
  int window = atoi(argv[4]);
    
  // convert octree
  Schematic schematic; 
  PcdConverter converter;
  converter.setResolution(resolution);
  converter.load(input_path);
  converter.convert(schematic);
  converter.filter(schematic, window);
  
  // write out
  Writer writer(output_path);
  writer.write(schematic);

  cout << "Done." << endl;

  return 0;
}
