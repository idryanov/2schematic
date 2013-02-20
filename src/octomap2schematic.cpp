#include "octomap2schematic.h"

using namespace std;

int main(int argc, char** argv)
{
  // get parameters

  if (argc != 3)
  {
    cout << "ERROR: Usage is " << argv[0]; 
    cout << " <input.ot> <output.schematic>" << endl;
    return -1;
  }
  
  std::string input_path  = argv[1];
  std::string output_path = argv[2];
  
  // load octree
  
  cout << "Opening " << input_path << "..." << endl;  
   
  octomap::AbstractOcTree* atree = octomap::AbstractOcTree::read(input_path);
  octomap::ColorOcTree* tree;
  
  if (atree && atree->getTreeType() == "ColorOcTree")
    tree = dynamic_cast<octomap::ColorOcTree*>(atree);
  else
  {
    cout << "ERROR: Octree not found, or not ColorOcTree" << endl;
    return -1;
  } 
  
  // convert octree
  rgbd_2_schematic::Schematic schematic;
  
  rgbd_2_schematic::OctomapConverter converter;
  converter.setTree(tree);
  converter.convert(schematic);
  converter.filter(schematic);
  
  // wrtie out
  rgbd_2_schematic::Writer writer(output_path);
  writer.write(schematic);

  return 0;
}


