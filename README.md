# Lighthouse
CSC513 Designing Creativity Support Tools - Lighthouse Project

## Assignment 1: Sun Simulator

Sun Simulator is a tangible creativity support tool developed as part of the Lighthouse project. 
It allows lighting designers, architects, and interior designers to simulate daylight conditions using an RGB LED and a programmable interface controlled via IR remote.

### Features

- IR remote input for intuitive interaction
- Smooth time lapse lighting transitions across a 24-hour cycle
- Manual scrubbing through hourly daylight states
- LCD display for system status feedback
- Expandable framework for future integration with spatial position sensors and motorized daylight tracking

### Components

See [sun-simulator_components-list.pdf](./A1/Documentation/sun-simulator_components-list.pdf) for a full list of hardware.

### Usage

Upload sunsimulator.ino to your Arduino Uno. Use the IR remote to:

- Power on/off
- Start, pause, or stop a timelapse
- Scrub through specific hours
- View system status on the LCD


## Assignment 2: Helios

## Replication Instructions

For a complete step-by-step guide to reproducing the build, including wiring procedures, component tests, and soldering order, see:

[replication-instructions.md](./A2/hardware/replication-instructions.md)

### Components

See [components-list.md](./A2/hardware/components-list.md) for a full list of hardware and electronic components.

### Physical Design: Vehicle Housing

The physical layout of the vehicle housing—including component placement for the MPU6050, battery, NodeMCU, and wiring channels—was prototyped in [Tinkercad](https://www.tinkercad.com/).

- The model includes:
  - Component slots and clearances for each board/module
  - Cable routing paths
  - Magnet mounting positions for frame
  - Alignment with laser-cut parts
  - Air vents for electronics heat management

[Click here to view the interactive 3D model on Tinkercad](https://www.tinkercad.com/things/7dStJ63O6l6-helios-led-vehicle-mockup?sharecode=OOx2I1GtN9w_u_0MqxNnp-95iOZiNa8bC63oy1-xb5w)

See [Rendering A](./A2/hardware/photos/vehicle_rendering_A.png) and [Rendering B](./A2/hardware/photos/vehicle_rendering_B.png) for static renderings of the final design before preparing the laser cut [pattern](./A2/hardware/laser_cut).

Component color key:
- Dark Purple: NodeMCU 
- Blue: Boost converter
- Magenta: LiPo 
- Yellow: MPU 
- Brown: Charging Module

This prototype was used to inform final dimensions and component placement strategies. Glueing and fastening strategies were implemented when designing the cut pattern in Adobe Illustrator.

### Data
See the [README](./A2/data/README.md) in `/data/` for information about the dataset used, and how it will be implemented.

### Code
See the [README](./A2/code/README.md) in `/code/` for information about the code written, and how it will be expanded to achieve the goal functionality.