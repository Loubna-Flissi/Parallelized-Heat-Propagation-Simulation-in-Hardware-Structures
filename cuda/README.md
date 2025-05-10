# Heat Propagation Simulation - CUDA Version

This project implements a parallel simulation of heat propagation using NVIDIA's CUDA platform. It takes advantage of the GPU's massive parallel processing power to accelerate the simulation over large 2D grids.

## Algorithm Overview

- A 2D grid models the material, where each cell represents a temperature value.
- For each iteration:
  - Each GPU thread computes the new temperature of a single cell based on the average of its four neighbors (top, bottom, left, right).
  - A sinusoidal component is added to simulate periodic temperature variation.
  - The updated values are written back to a new grid.
  - The grid is synchronized and updated between iterations.

## CUDA Parallelization Strategy

- The grid is divided into blocks of threads.
- Each thread is responsible for one cell, based on its `(i, j)` coordinates.
- Two CUDA kernels are used:
  1. `calculer_nouvelle_grille`: Computes new temperatures.
  2. `mettre_a_jour_grille`: Copies the new grid into the main grid.
- Synchronization using `cudaDeviceSynchronize()` ensures consistency across iterations.
- At the end of all iterations, results are copied back to the host (CPU).

## How to Compile

```bash
nvcc -o heat_sim_cuda heat_sim_cuda.cu
