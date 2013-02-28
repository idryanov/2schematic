2Schematic
===================================
The closest you can come to destroying your office with a pickaxe (without legal repercussions).

#![Minecraft room](https://raw.github.com/idryanov/2schematic/master/data/images/mcedit.png "Minecraft room")

**2schematic** is a set of tools for converting colored 3D models of real-world environements 
into Minecraft .schematic files. The models can be built using an RGB-D camera (such as the Microsfot Kinect) 
and the [ccny_rgbd](github.com/ccny_rgbd/tools) software. 

The supported input formats are:
 * Octomap (.ot) files
 * PCL pointcloud (.pcd) files

The output schematics can be imported into Minecraft world editors such as [mcedit](http://www.mcedit.net/), 
which allow you to save worlds you can load and play inside [MineCraft](http://minecraft.net).

Building
-----------------------------------

First, obtain the dependencies. You can get either or both, depending on what input files you want to convert:

 * [PCL](http://pointclouds.org/downloads/linux.html)
 * [Octomap](https://github.com/OctoMap/octomap)

If one of the dependencies is not installed, the corresponding converter executable will not be built.

Download the package from github:

    git clone https://github.com/idryanov/2schematic.git

To compile:    
    
    cd 2schematic
    mkdir build
    cd build
    cmake ..
    make

The executables will be generated in `2schematic/bin`

Usage
-----------------------------------

### Octomap to schematic: ###

    octomap2schematic [file_in] [file_out] [filter_size]
    
Where the arguments are:

 * `file_in`: an Octomap file, (.ot format), with color.
 * `file_out`: a .schematic file
 * `filter_size`: The window size, in voxel units, to perform color median filtering. 
Set this to a small value (like 1 or 2) to make colors more uniform and remove random color blobs.
Setting this to 0 will disable color filtering.

Example:
    ./bin/octomap2schematic data/room.ot data/room.schematic 1
    
### PCL to schematic: ###
    
    pcd2schematic [file_in] [file_out] [resolution] [filter_size]
    
Where the arguments are:

 * `file_in`: a PCL PointCloud file, (.pcd format), with color.
 * `file_out`: a .schematic file
 * `resolution`: the size, in meters, of each block. For example, 0.05 will 
produce one block for each 5cm of real-world space.
 * `filter_size`: The window size, in voxel units, to perform color median filtering. 
Set this to a small value (like 1 or 2) to make colors more uniform and remove random color blobs.
Setting this to 0 will disable color filtering.

Example    
    ./bin/pcd2schematic data/room.pcd data/room.schematic 0.05 1

Acknowledgements
-----------------------------------

Special thanks to [Patrick Min](http://www.patrickmin.com/minecraft) for the schematic output code and the 
initial discussion.

Why?
-----------------------------------

Because I needed an excuse to procrastinate the actual research I have to do. 

Feedback
-----------------------------------

Please drop me a line with any questions, comments or suggestions.

License
-----------------------------------
**2schematic** is licensed under GPLv3.

