#ifndef RGBD_2_SCHEMATIC_WRITER_H
#define RGBD_2_SCHEMATIC_WRITER_H

#define BUFLEN      16384

#include <iostream>
#include <fstream>
#include <zlib.h>

#include "schematic.h"

namespace rgbd_2_schematic {

const char TAG_END        = 0;
const char TAG_SHORT      = 2;
const char TAG_BYTE_ARRAY = 7;
const char TAG_STRING     = 8;
const char TAG_LIST       = 9;
const char TAG_COMPOUND   = 10;

class Writer
{ 
  public:

    Writer(const std::string& path);

    void write(const Schematic& schematic);              
         
  private:

    std::string path_;
    std::ofstream stream_;

    void writeSchematic(const Schematic& schematic);
    bool compressSchematic();
    
    void write_schematic_short(short value);
    void write_schematic_int(int value);
    void write_schematic_string(const std::string& text);
};

} // namespace rgbd_2_schematic

#endif // RGBD_2_SCHEMATIC_WRITER_H
