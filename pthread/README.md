# Heat Propagation Simulation - Pthreads Version

This version of the heat propagation simulation is implemented in `heat_sim_pthreads.c` and uses POSIX threads (Pthreads) to parallelize the computation across multiple CPU cores for improved performance.

## Algorithm Overview

- The simulation operates on a 2D grid where each cell represents a temperature value.
- Each thread is assigned a portion of the grid (e.g., a set of rows).
- For each iteration:
  - Threads independently compute new temperatures by averaging the four neighboring cells for each assigned cell.
  - A sinusoidal component is added to simulate environmental variation.
  - A synchronization barrier ensures all threads complete their computation before updating the main grid.

## Parallelization Strategy

- Work is divided evenly among threads based on the number of rows.
- Each thread processes its assigned section independently.
- `pthread_barrier_t` is used to synchronize threads at the end of each iteration.
- The number of threads can be specified at runtime.

## How to Compile

```bash
gcc -o heat_sim_pthreads heat_sim_pthreads.c -lpthread -lm
