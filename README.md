# Parallelized Heat Propagation Simulation in Hardware Structures

This project focuses on the **parallelization** of heat propagation simulation across a 2D grid, utilizing **Pthreads** and **CUDA** to optimize performance. The project includes both parallelized implementations for CPU and GPU, along with a **sequential** baseline for comparison.

## Objectives

- Model heat diffusion in a 2D grid.
- Implement parallelization using:
  - **Pthreads** for CPU-based parallelism.
  - **CUDA** for GPU-based parallelism.
- Compare performance and scalability between parallel approaches and the **sequential** version.
- Benchmark execution times based on grid size and hardware configurations.

## Project Structure

parallel-heat-simulation/
├── serial/       # Sequential implementation (baseline)
├── pthread/      # Pthreads parallelization
├── cuda/         # CUDA parallelization
├── results/      # Performance data (benchmark results)
├── Makefile      # Compilation script for different implementations
└── README.md     # This file

## How to Run

1. **Pthreads Version**:
   - Navigate to the `pthread/` directory.
   - Compile with `make` (requires a C compiler).
   - Run with `./heat_sim_pthreads`.

2. **CUDA Version**:
   - Navigate to the `cuda/` directory.
   - Ensure you have the CUDA toolkit installed.
   - Compile with `nvcc heat_sim_cuda.cu -o heat_sim_cuda`.
   - Run with `./heat_sim_cuda`.

3. **Sequential Version**:
   - Navigate to the `serial/` directory.
   - Compile with `make`.
   - Run with `./heat_sim_serial`.

## Author

FLISSI Loubna – Computer Science student at ESI, specializing in Information Systems  
Project developed as part of HPC coursework focusing on parallel algorithm design and performance optimization.

