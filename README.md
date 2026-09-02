# Parabench

Parabench is a C++ and OpenMP tool that measures and visualizes multi-threaded CPU performance using parallel matrix math.

It multiplies dense matrices with a naive triple-loop kernel, parallelizes the outer loop with OpenMP, and sweeps matrix size and thread count to see how much larger workloads actually benefit from more threads. Results are written to CSV and plotted with Matplotlib.

## Build

Requires a C++17 compiler with OpenMP support and CMake 3.10+.

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

This produces a `parabench` (or `parabench.exe` on Windows) binary in `build/`.

## Run a benchmark

```bash
./build/parabench --sizes 256,512,768,1024 --threads 1,2,4,8 --repeats 3 --output results.csv
```

- `--sizes` — comma-separated N for N x N matrices
- `--threads` — comma-separated OpenMP thread counts to compare
- `--repeats` — timed runs per configuration; the fastest is kept
- `--output` — path to the CSV written (`matrix_size,threads,seconds,gflops`)

Before timing anything, the binary cross-checks a small parallel multiply against the serial baseline and warns if they disagree.

Example output on a 4-core machine:

```
matrix_size,threads,seconds,gflops
256,1,0.006,5.59
256,2,0.003,11.18
256,4,0.001,33.55
512,1,0.048,5.59
512,2,0.027,9.94
512,4,0.014,19.17
```

## Plot the results

```bash
pip install -r scripts/requirements.txt
python scripts/plot_results.py results.csv -o results.png
```

This draws one line per thread count, execution time vs. matrix size, so you can see the crossover point where parallelism starts paying off.

## Project layout

```
CMakeLists.txt
src/
  matrix.hpp / matrix.cpp   # matrix type, serial and OpenMP multiply
  main.cpp                  # benchmark CLI
scripts/
  plot_results.py           # CSV -> Matplotlib chart
```
