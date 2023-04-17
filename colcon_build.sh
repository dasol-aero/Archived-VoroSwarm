#!/bin/bash
WORKING_DIRECTORY=$(pwd)

cd ~/ws_VoroSwarm
colcon build --symlink-install

cd $WORKING_DIRECTORY
