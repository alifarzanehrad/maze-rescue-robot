# Maze Rescue Robot

An archived autonomous **rescue-maze robotics project** developed as a team project around 2019–2020.

The robot was designed to explore a maze autonomously, detect walls and obstacles, track its orientation and position, react to ramps, and support victim-detection logic using temperature sensors.

> **Status:** Archived / Incomplete  
> **MCU:** ATmega128A  
> **Language:** C  
> **Original toolchain:** CodeVisionAVR

## Demo

A development-era video of the physical robot is available on LinkedIn:

[Watch the robot demo on LinkedIn](https://www.linkedin.com/posts/alii-farzaneh_%DB%8C%D8%A7%D8%AF%D9%85-%D9%85%DB%8C%D8%A7%D8%AF-%D8%A8%D8%B1%D8%A7%DB%8C-%D8%A7%DB%8C%D9%86-%D8%AE%DB%8C%D9%84%DB%8C-%D8%B2%D8%AD%D9%85%D8%AA-%DA%A9%D8%B4%DB%8C%D8%AF%DB%8C%D9%85-%D8%AA%D8%A7-%D8%A8%D9%87-activity-7259690621341167617-3mLk?utm_source=share&utm_medium=member_desktop&rcm=ACoAAEJ1R5EBln8NKW5Elea9kdeMdwfz4rEEBuA)

## What the robot implemented

The preserved firmware includes support for:

- autonomous maze exploration
- wall and obstacle detection
- left, right, and 180-degree turning
- internal maze memory
- position and direction tracking
- ultrasonic distance sensing
- analog distance sensing
- compass-based orientation sensing
- encoder-assisted movement
- PWM motor control
- ramp detection
- temperature-based victim detection
- EEPROM-backed calibration and state values
- LCD-based configuration and debugging

## Navigation and maze memory

The robot keeps an internal representation of the explored environment:

```c
signed char mem[60][30];
```

It also tracks its current coordinates and orientation:

```c
int x, y;
int dir = 1;
```

The navigation logic uses the current direction to inspect neighboring cells and evaluate possible movements. The preserved firmware contains dedicated decision-making and movement routines such as `calculate()`, along with turn and motion logic.

This means the project was not limited to simple wall-following; it contained explicit state for position, direction, visited-space information, and navigation decisions.

## Sensors

### Ultrasonic sensors

The firmware contains support for five ultrasonic sensing positions:

- front
- front-left
- front-right
- rear-left
- rear-right

These readings are used for wall detection, obstacle awareness, and alignment inside maze corridors.

### Analog distance sensors

Two additional analog distance channels are used as left/right distance inputs for close-range wall sensing and alignment.

### Compass

The robot reads bearing, pitch, and roll over I2C. Orientation information is used for heading-related logic, while pitch is also used by the ramp-detection code.

A preserved calibration utility is available in:

```text
tools/compass_calibration.c
```

### Temperature sensors

The firmware includes MLX temperature-sensor handling for left, right, and front sensing positions. The corresponding victim-detection routine can stop the robot, indicate a detection, rotate toward the target, and trigger an actuator sequence.

## Motion control

The robot uses two independently controlled drive motors with PWM-based speed control.

The code contains movement and calibration logic for:

- straight motion
- left/right differential turning
- 90-degree turns
- 180-degree turns
- heading correction
- wall alignment

Timing and calibration parameters are stored in EEPROM so they can be tuned on the physical platform.

## Ramp handling

Pitch measurements are used to distinguish upward and downward ramp conditions.

The firmware contains separate logic for entering and leaving ramps and for integrating those transitions with maze position tracking.

## High-level architecture

```text
Distance / orientation / temperature sensors
                    |
                    v
            Environment sensing
                    |
                    v
               Maze memory
                    |
                    v
           Navigation decision
                    |
                    v
              Motor control
                    |
                    v
       Position / direction update
```

## Repository structure

```text
maze-rescue-robot/
├── src/
│   └── main.c
├── include/
│   └── dynamixelPro2018.h
├── tools/
│   └── compass_calibration.c
├── archive/
│   ├── versions/
│   └── unverified/
├── legacy-project/
│   └── code2020.prj
└── README.md
```

### `src/main.c`

The primary preserved firmware version selected from the original project archive.

The original file is also retained as:

```text
archive/versions/code2020.c
```

`code2020.c` and the final dated snapshot `99-1-1.c` are identical in the preserved archive.

### `archive/versions/`

Contains historical development snapshots from the original project directory. They are intentionally preserved to retain the development history rather than being rewritten into a modern codebase.

### `archive/unverified/`

Contains source material whose original formatting or integrity could not be fully verified.

### `legacy-project/`

Contains the original CodeVisionAVR project file.

## Project history

This repository preserves an early robotics project rather than presenting the code as a modern production-ready firmware architecture.

Development went through many hardware tests and firmware iterations. The project ultimately remained incomplete, but the physical robot reached the point where it could move autonomously and navigate portions of a real maze.

The historical source files are kept because they document the evolution of the project and the debugging process used on the original hardware.

## Team project and contribution

This was a **team project**.

The repository is published as an archive of the technical work produced during that project. Individual responsibilities are not claimed for every subsystem in the codebase.

A more detailed contribution breakdown can be added later if the original division of work is reconstructed with confidence.

## Why this repository is archived

The original hardware and toolchain are no longer actively maintained, and the firmware has intentionally not been heavily refactored.

The purpose of this repository is to preserve the original engineering work, including its experiments, calibration routines, historical snapshots, and limitations.
