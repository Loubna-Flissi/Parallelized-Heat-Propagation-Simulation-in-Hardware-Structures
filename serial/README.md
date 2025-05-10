# Heat Propagation Simulation - Serial Version

This project simulates heat propagation in a 2D grid using a sequential algorithm implemented in `heat_sim_serial.c`. It models how temperature evolves over time in a material by averaging neighboring cell values.

## Algorithm Overview

- A fixed-size 2D grid represents temperature values of a material.
- Each cell is initialized with a random temperature.
- For each iteration:
  - A new grid is computed by averaging the temperatures of the four adjacent neighbors (top, bottom, left, right).
  - A sinusoidal component is added based on cell position to simulate environmental temperature variation.
  - The new grid replaces the old one after each iteration.

## Features

- Simple and clear implementation for understanding heat diffusion principles.
- Acts as a performance baseline for parallel versions.

## How to Compile

```bash
gcc -o heat_sim_serial heat_sim_serial.c -lm
