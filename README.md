# Arm Joystick Control

## Setup

Clone this repository to the source folder of ROS2 workspace and run the setup script in the `setup/` folder.

The script works if a `$WORKSPACE` environment variable is set to the desired ROS workspace path.

>**Note:** Make sure to set the permissions for `ds4drv` by following the instructions [here](https://github.com/naoki-mizuno/ds4drv/tree/devel?tab=readme-ov-file#permissions). This must be done on the host OS regardless of the use of container.

### Note on running this package in Docker container

Append the following flags in `runArgs` section of `devcontainer.json` when running the container to access the DualShock 4 controller.

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

### Manual setup

Clone the [ds4_driver](https://github.com/naoki-mizuno/ds4_driver) ROS package to source folder and install the DualShock 4 driver [ds4drv](https://github.com/naoki-mizuno/ds4drv/tree/devel).

Doing a `rosdep install` should install rest of the dependencies if missing and the workspace is ready for build.

## Usage

Launch `ds4_driver` and the joystick control nodes using the given launch file

```bash
ros2 launch arm_joystick_control joystick_control.launch.py
```

For now the node should subscribe to the `/raw_report` topic and simply print the left and right analog stick input values to the terminal.
