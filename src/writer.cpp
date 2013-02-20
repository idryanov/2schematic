#include "writer.h"

using namespace std;

Writer::Writer(const std::string& path):
  path_(path)
{

}

void Writer::write(const Schematic& schematic)
{
  writeSchematic(schematic);
  compressSchematic();
  cout << "Done." << endl;
}

void Writer::writeSchematic(const Schematic& schematic)
{
  stream_.open(path_.c_str(), ofstream::binary);

  cout << "Writing schematic to file..." << endl;
  
  unsigned short width  = schematic.size_y; 
  unsigned short height = schematic.size_x; 
  unsigned short depth  = schematic.size_z;
  long size = schematic.voxels.size();
    
  cout << "  width:  " << width  << endl;
  cout << "  height: " << height << endl;
  cout << "  depth:  " << depth  << endl;
  cout << "  total " << size << " voxels" << endl;
  
  // write header

  stream_.write((const char *) &TAG_COMPOUND, 1);
  write_schematic_string("Schematic");

  // ordering of these three seems to vary per program

  stream_.write((const char *) &TAG_SHORT, 1);
  write_schematic_string("Width");  // along X according to spec
  write_schematic_short(width);

  stream_.write((const char *) &TAG_SHORT, 1);
  write_schematic_string("Length");  // along Z according to spec
  write_schematic_short(height);

  stream_.write((const char *) &TAG_SHORT, 1);
  write_schematic_string("Height");  // along Y according to spec
  write_schematic_short(depth);

  stream_.write((const char *) &TAG_STRING, 1);
  write_schematic_string("Materials");
  write_schematic_string("Alpha");
  
  stream_.write((const char *) &TAG_BYTE_ARRAY, 1);
  write_schematic_string("Blocks"); 
  write_schematic_int(size);
  for (int idx = 0; idx < size; ++idx)
  {
    unsigned char block_id = schematic.voxels[idx];
    stream_.write((const char *) &block_id, 1);
  }

  stream_.write((const char *) &TAG_BYTE_ARRAY, 1);
  write_schematic_string("Data");
  write_schematic_int(size);
  for (int idx = 0; idx < size; ++idx)
  {
    unsigned char data_id = schematic.data[idx];  
    stream_.write((const char *) &data_id, 1);
  }

  // no entities, no tile entities
  
  stream_.write((const char *) &TAG_LIST, 1);
  write_schematic_string("Entities");
  stream_.write((const char *) &TAG_COMPOUND, 1);
  write_schematic_int(0);  // will this work, 0 entries?

  stream_.write((const char *) &TAG_LIST, 1);
  write_schematic_string("TileEntities");
  stream_.write((const char *) &TAG_COMPOUND, 1);
  write_schematic_int(0);  // will this work, 0 entries?

  stream_.write((const char *) &TAG_END, 1);
  
  stream_.close();
}

void Writer::write_schematic_short(short value)
{
  char *byte_ptr = (char *) &value;

  stream_.write((const char *)(byte_ptr + 1), 1);
  stream_.write((const char *)(byte_ptr), 1);
}

void Writer::write_schematic_int(int value)
{
  // convert to big endian
  char *byte_ptr = (char *) &value;

  stream_.write((const char *)(byte_ptr + 3), 1);
  stream_.write((const char *)(byte_ptr + 2), 1);
  stream_.write((const char *)(byte_ptr + 1), 1);
  stream_.write((const char *)(byte_ptr), 1); 
}

void Writer::write_schematic_string(const std::string& text)
{
  const char * ctext = text.c_str();
  short length = text.length();
  write_schematic_short(length);
  stream_.write((const char *) ctext, length);
}

bool Writer::compressSchematic()
{
  cout << "Compressing schematic..." << endl;

  gzFile outfile = gzopen("temp.schematic", "wb");
  FILE *in = fopen(path_.c_str(), "r");
  
  char buf[BUFLEN];
  int len;

  for (;;) 
  {
    len = (int) fread(buf, 1, sizeof(buf), in);
    if (ferror(in)) 
    {
      cout << "could not read from uncompressed schematic file" << endl;
      return false;
    }
    if (len == 0) break;
    
    if (gzwrite(outfile, buf, (unsigned) len) != len) 
    {
      cout << "gzip compression failed" << endl;
      return false;
    }
  }
  fclose(in);
  if (gzclose(outfile) != Z_OK) 
  {
    cout << "could not close compressed file" << endl;
    return false;
  }

  remove(path_.c_str());
  rename("temp.schematic", path_.c_str());
  return true;
}

