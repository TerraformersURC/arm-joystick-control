# Arm Joystick Control

## Setup

Clone this repository to the source folder of ROS2 workspace and run the setup script in the `setup/` folder.

```bash
./setup/arm-joystick-control-setup.sh
```

The script works if a `$WORKSPACE` environment variable is set to the desired ROS workspace path.

The setup script sets up to support both the DualShock4 and Logitech F310 controllers.

### Note on running this package in Docker container

Append the following flags in `runArgs` section of `devcontainer.json` when running the container to access the controller.

```json
"runArgs": [

// Other flags ...

"--volume=/dev:/dev:rw",
"--device=/dev/uinput:/dev/uinput",
"--device=/dev/input:/dev/input",
"--device=/dev/hidraw1:/dev/hidraw1",

]
```

Or when running from terminal using `docker run ...`

```bash
--volume=/dev:/dev:rw \
--device=/dev/uinput:/dev/uinput \
--device=/dev/input:/dev/input \
--device=/dev/hidraw1:/dev/hidraw1
```

### Manual setup for using DualShock 4

Clone the [ds4_driver](https://github.com/naoki-mizuno/ds4_driver) ROS package to source folder and install the DualShock 4 driver [ds4drv](https://github.com/naoki-mizuno/ds4drv/tree/devel).

>**Note:** Make sure to set the permissions for `ds4drv` by following the instructions [here](https://github.com/naoki-mizuno/ds4drv/tree/devel?tab=readme-ov-file#permissions). This must be done on the host OS regardless of the use of container.

Doing a `rosdep install` should install rest of the dependencies if missing and the workspace is ready for build.

```bash
rosdep install --from-paths src --ignore-src -y --rosdistro $ROS_DISTRO
```

## Usage

Launch `ds4_driver` and the joystick control nodes using the given launch file

```bash
ros2 launch arm_joystick_control joystick_control.launch.py
```

For now the node should subscribe to the `/raw_report` topic and simply print the left and right analog stick input values to the terminal.
