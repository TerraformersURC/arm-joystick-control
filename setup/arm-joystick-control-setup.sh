#!/bin/bash

set -e

# This script will handle the first-time setup for your package only.
cd $WORKSPACE

# Add your setup steps (Install dependencies, clone additional git repositories etc.)

if [ ! -d $WORKSPACE/src/ds4_driver ]
then
  git clone -b humble-devel https://github.com/naoki-mizuno/ds4_driver.git $WORKSPACE/src/ds4_driver
fi

sudo apt update
sudo apt install python3-pip python3-evdev -y
pip3 install pyudev

if [ ! -d ~/ds4drv ]
then
  git clone -b devel https://github.com/naoki-mizuno/ds4drv.git ~/ds4drv
  cd ~/ds4drv
  sudo python3 setup.py install
fi

cd $WORKSPACE

sudo apt install jstest-gtk joystick

sudo apt update
rosdep update --rosdistro $ROS_DISTRO
rosdep install --from-paths src --ignore-src --rosdistro $ROS_DISTRO -r -y

# Don't add anything else below this line.
# User should now be able to "colcon build" your package cleanly after the script exits.
