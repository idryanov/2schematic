#include "converter.h"

namespace rgbd_2_schematic {

using namespace std;
  
Converter::Converter()
{

}

int Converter::getMaterial(int r, int g, int b)
{
  int mat;

  //mat = getMaterialNearestRGB(r, g, b);
  mat = getMaterialNearestHue(r, g, b);

  return mat;
}

void Converter::filter(Schematic& schematic, int window)
{
  window_ = window;

  cout << "Filtering schematic colors (window: " << window_ << ")" << endl;

  std::vector<unsigned char> data_new;
  data_new.resize(schematic.data.size());

  int sx = schematic.size_x;
  int sy = schematic.size_y;
  int sz = schematic.size_z;
  
  for (int z = 0; z < sz; ++z)    
  for (int x = 0; x < sx; ++x)
  for (int y = 0; y < sy; ++y)
  {            
    int idx = z * (sx * sy) + x * sy + y;
    
    if (schematic.voxels[idx] == 0) continue;
    
    data_new[idx] = getMedianColor(schematic, x, y, z);
  }
  
  schematic.data = data_new;
}

int Converter::getMedianColor(
  const Schematic& schematic, 
  int x, int y, int z)
{
  int hist[16];
  for (int i = 0; i < 16; ++i) hist[i] = 0;
  
  int sx = schematic.size_x;
  int sy = schematic.size_y;
  int sz = schematic.size_z;
  
  int x_min = std::max(x - window_, 0);
  int y_min = std::max(y - window_, 0);  
  int z_min = std::max(z - window_, 0);  
  
  int x_max = std::min(x + window_, sx);
  int y_max = std::min(y + window_, sy);  
  int z_max = std::min(z + window_, sz);  
  
  for (unsigned int zz = z_min; zz <= z_max; ++zz)    
  for (unsigned int xx = x_min; xx <= x_max; ++xx)
  for (unsigned int yy = y_min; yy <= y_max; ++yy)
  {    
    int idx = zz * (sx * sy) + xx * sy + yy;
    
    if (schematic.voxels[idx] == 0) continue;
    
    int color_data = schematic.data[idx];
    
    hist[color_data]++;
  }
  
  // the original color
  int base_idx = z * (sx * sy) + x * sy + y;
  int base_data_idx = schematic.data[base_idx];
  int base_data_val = hist[base_data_idx];
  
  // get the max of the histogram
  int hist_max_idx = 0;
  int hist_max_val = 0;
  
  for (int i = 0; i < 16; ++i)
  {
    if (hist[i] > hist_max_val)
    {
      hist_max_val = hist[i];
      hist_max_idx = i;
    }
  }

  // return new color if its strictly more than prev color
  if (hist_max_val > base_data_val)
    return hist_max_idx;
  else 
    return base_data_idx;
}

int Converter::getMaterialNearestRGB(int r, int g, int b)
{
  int mat;
  const int color[3] = {r, g, b};

  double min = 9999;
  int d;

  if ((d = colorDiff(color, WHITE)) < min)
  {  min = d; mat = 0; }
  if ((d = colorDiff(color, ORANGE)) < min)
  {  min = d; mat = 1; }
  if ((d = colorDiff(color, MAGENTA)) < min)
  {  min = d; mat = 2; }
  if ((d = colorDiff(color, LIGHT_BLUE)) < min)
  {  min = d; mat = 3; }
  if ((d = colorDiff(color, YELLOW)) < min)
  {  min = d; mat = 4; }
  if ((d = colorDiff(color, LIME)) < min)
  {  min = d; mat = 6; }
  if ((d = colorDiff(color, PINK)) < min)
  {  min = d; mat = 7; }
  if ((d = colorDiff(color, GRAY)) < min)
  {  min = d; mat = 8; }
  if ((d = colorDiff(color, LIGHT_GRAY)) < min)
  {  min = d; mat = 9; }
  if ((d = colorDiff(color, PURPLE)) < min)
  {  min = d; mat = 10; }
  if ((d = colorDiff(color, BLUE)) < min)
  {  min = d; mat = 11; }
  if ((d = colorDiff(color, BROWN)) < min)
  {  min = d; mat = 12; }
  if ((d = colorDiff(color, GREEN)) < min)
  {  min = d; mat = 13; }
  if ((d = colorDiff(color, RED)) < min)
  {  min = d; mat = 14; }    
  if ((d = colorDiff(color, BLACK)) < min)
  {  min = d; mat = 15; }    

  return mat;
}

int Converter::getMaterialNearestHue(int r, int g, int b)
{
  int mat;
  
  const int color[3] = {r, g, b};
  
  // convert to HSV space
  double h, s, v;
  rgb2hsv(r, g, b, h, s, v);
  
  if (s < SAT_MIN || v < VAL_MIN)
  {
    if      (v < 0.25) mat = MAT_BLACK; 
    else if (v < 0.50) mat = MAT_GRAY;
    else if (v < 0.75) mat = MAT_LIGHT_GRAY;
    else               mat = MAT_WHITE;
  }
  else
  {
    if (h >= 320 || h < 13)
    {
      if (colorDiff(color, RED) <  colorDiff(color, PINK))
        mat = MAT_RED; 
      else
        mat = MAT_PINK;
    }
    if (h >= 13 && h < 30)
    {
      if (colorDiff(color, ORANGE) < colorDiff(color, BROWN))
        mat = MAT_ORANGE; 
      else
       mat = MAT_BROWN;   
    }
    if (h >= 30 && h < 70)
      mat = MAT_YELLOW;
    if (h >= 70 && h < 100)
      mat = MAT_GREEN;
    if (h >= 100 && h < 155)
      mat = MAT_LIME;
    if (h >= 155 && h < 210)
      mat = MAT_CYAN;
    if (h >= 210 && h < 255)  
    {
      if (colorDiff(color, LIGHT_BLUE) < colorDiff(color, BLUE))
        mat = MAT_LIGHT_BLUE;
      else
        mat = MAT_BLUE; 
    }
    if (h >= 255 && h < 285)  
      mat = MAT_PURPLE;
    if (h >= 285 && h < 320)  
      mat = MAT_MAGENTA;
  }
  
  return mat;
}

double Converter::colorDiff(const int rgb_A[3], const int rgb_B[3])
{
  int dr = rgb_A[0] - rgb_B[0];
  int dg = rgb_A[1] - rgb_B[1];
  int db = rgb_A[2] - rgb_B[2];
  return sqrt(dr*dr + dg*dg + db*db);
}

void Converter::rgb2hsv(
  int r, int g, int b,
  double& h, double& s, double& v)
{
  double in_r = r / 255.0;
  double in_g = g / 255.0;
  double in_b = b / 255.0;
  
  double min = in_r < in_g ? in_r : in_g;
  min = min  < in_b ? min  : in_b;

  double max = in_r > in_g ? in_r : in_g;
  max = max  > in_b ? max  : in_b;

  v = max;                                // v
    
  double delta = max - min;
  
  if(v != 0.0) 
  {
    s = (delta / max);                  // s
    
    if (s != 0.0)
    {     
      if(in_r >= max)                     // > is bogus, just keeps compilor happy
        h = (in_g - in_b) / delta;        // between yellow & magenta
      else if(in_g >= max)
        h = 2.0 + (in_b - in_r) / delta;  // between cyan & yellow
      else
        h = 4.0 + (in_r - in_g) / delta;   // between magenta & cyan

      h *= 60.0;                          // degrees

      if( h < 0.0 ) h += 360.0;  
    }
    else
    {
      h = 0; //NaN
    }
  }
  else 
  {
    // r = g = b = 0                        // s = 0, v is undefined
    s = 0.0;
    h = 0; //NaN                          // its now undefined
    return;
  } 
}

} // namespace rgbd_2_schematic
