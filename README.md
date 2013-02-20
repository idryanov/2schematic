RGB-D To Schematic
===================================
The closest you can come to destroying your office with a pickaxe (without legal repercussions).

**rgbd2schematic** is a set of tools for converting colored 3D models of real-world environements 
into Minecraft .schematic files. The models can be built using an RGB-D camera (such as the Microsfot Kinect) 
and the [ccny_rgbd](github.com/ccny_rgbd/tools) software. 

The supported input formats are:
 * Octomap (.ot) files
 * PCL pointcloud (.pcd) files

The output schematics can be imported into Minecraft world editors such as [mcedit](http://www.mcedit.net/)

Building
-----------------------------------

First, obtain the dependencies. You can get either or both, depending on what input files you want to convert:

 * [PCL](http://pointclouds.org/downloads/linux.html)
 * [Octomap](https://github.com/OctoMap/octomap)

If one of the dependencies is not installed, the corresponding converter executable will not be built.

Download the package from github:

    git clone https://github.com/idryanov/rgbd2schematic.git

To compile:    
    
    cd rgbd2schematic
    mkdir build
    cd build
    cmake ..
    make

The executables will be generated in `rgbd2schematic/bin`

Usage
-----------------------------------

Octomap to schematic:

    ./bin/octomap2schematic data/room.ot data/room.schematic

PCL to schematic:
    
    ./bin/pcd2schematic data/room.pcd data/room.schematic

Acknowledgements
-----------------------------------

Special thanks to [Patrick Min](http://www.patrickmin.com/minecraft) for the schematic output code.

License
-----------------------------------
**rgbd2schematic** is licensed under GPLv3.

