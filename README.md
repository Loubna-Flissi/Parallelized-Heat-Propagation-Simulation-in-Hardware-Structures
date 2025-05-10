# Heat Propagation Simulation Project

This project simulates heat propagation in 2D material structures using three different approaches:
1. A **serial implementation** (CPU-based, single-threaded),
2. A **Pthreads-based parallel implementation** (multi-threaded CPU),
3. A **CUDA-based GPU implementation**.

The simulation models the transfer of heat over time within a grid by updating each cell based on its surrounding neighbors. The objective is to evaluate how parallel programming techniques (Pthreads and CUDA) can improve computational efficiency compared to a baseline serial approach.

---

## Project Objectives

- Simulate 2D heat diffusion using a numerical method.
- Explore and implement parallel computing techniques (multi-core CPU and GPU).
- Compare the performance of:
  - Serial C implementation,
  - Parallel version using Pthreads,
  - GPU-accelerated version using CUDA.
- Analyze the trade-offs and benefits of each method.

---

## Folder Structure

├── serial/ # Contains heat_sim_serial.c
├── pthreads/ # Contains heat_sim_pthreads.c
├── cuda/ # Contains heat_sim_cuda.cu


Each folder includes a dedicated `README.md` with compilation and execution instructions.

---

## Performance Comparison

### Grid Size: 1000 x 1000  
### Metric: Execution Time (in seconds)

| Method           | Threads     | Execution Time |
|------------------|-------------|----------------|
| **Serial**       | 1           | 102.81 s       |
| **Pthreads**     | 2           | 54.23 s        |
|                  | 4           | 31.83 s        |
|                  | 6           | 25.97 s        |
|                  | 8           | 23.01 s        |
|                  | 16          | 21.97 s        |
|                  | 24          | 20.92 s        |
|                  | 50          | 21.52 s        |
| **CUDA**         | 2           | 7.10 s         |
|                  | 4           | 3.78 s         |
|                  | 6           | 2.54 s         |
|                  | 8           | 1.92 s         |
|                  | 16          | 1.11 s         |
|                  | 24          | **0.77 s**     |
|                  | 50          | **0.77 s**     |

---

## Analysis

- **Serial**: Slowest; used as a correctness and performance baseline.
- **Pthreads**: Good speedup up to 8 threads. After that, improvements plateau due to CPU core limitations and thread management overhead.
- **CUDA**: Fastest approach; fully leverages GPU parallelism and memory hierarchy. Achieves up to **~93% time reduction** compared to serial.

---

## Conclusion

- Parallelism drastically improves performance for compute-intensive tasks like heat simulation.
- **Pthreads** offers a straightforward way to leverage multi-core CPUs.
- **CUDA** is the most efficient for large-scale simulations, thanks to the GPU’s massive parallelism.
- The best approach depends on the hardware and the size of the problem: small grids may not benefit from GPU overhead, but large grids do.

---

## Requirements

- C compiler (`gcc`) for serial and Pthreads versions
- CUDA Toolkit (`nvcc`) for GPU version
- Linux-based system or WSL is recommended for pthread and CUDA execution

---

## Future Improvements

- Dynamic grid size and iteration control via CLI arguments
- Visualization of temperature distribution
- Real-time animation or heatmap output
- Comparison with OpenMP and MPI versions
