# Neuvisys Simulator

A CoppeliaSim simulator for event vision.

## Requirements

### Coppeliasim / ROS

Download and install the Coppeliasim framework: https://www.coppeliarobotics.com/

There is 3 available versions, **player**, **edu** and **pro**. Player is enough to work with neuvisys, but you will not be able to save the scene if you change it.

Install ROS Noetic (Other ROS distribution might work, but this is uncertain): http://wiki.ros.org/noetic/Installation/Ubuntu

It is advised to use the **Desktop-Full Install**, though other lighter version may also work.

## Launch

To compile the Neuvisys library, in the root folder:
- Run ``mkdir build``, ``cd build``, ``cmake -DCMAKE_BUILD_TYPE=Release ..``

If there is some errors, you may have to install the following python packages:
``pip install empy``
``pip install catkin-pkg``

- Run ``make -j`` to compile all targets

Compiled target can be found in the "build/" folder.

## CoppeliaSim usage

Before launching CoppeliaSim, you need to activate ros:
- ``roscore``

Then launch CoppeliaSim. If ros is working, the **ROS interface was found.** message should appear on the CoppeliaSim console at the bottom.

You can open the Neuvisys Coppelia scene with:
- ``File/Open scene...``
- Open ``src/coppelia-scenes/Neuvisys.ttt``

Then just launch the neuvisys-simulator target with:
- ``./build/src/neuvisys-simulator``
