# SparseFlow: Application-Specific Processor Simulator

## Project Overview
**SparseFlow** is a custom 5-stage pipelined processor simulator designed to accelerate **Sparse Matrix Operations**. It is implemented in C++ and models a RISC-V subset with specialized hardware extensions for handling sparse data structures efficiently.

## Features

### 1. 5-Stage Pipeline
- **IF, ID, EX, MEM, WB** stages fully modeled.
- **Pipeline Registers** (`IF/ID`, `ID/EX`, `EX/MEM`, `MEM/WB`) simulate data propagation.
- **Hazard Detection Unit**: Automatically inserts stalls for Load-Use hazards.
- **Forwarding Unit**: Bypasses data from MEM and WB stages to EX to resolve data hazards without stalling.

### 2. Custom ISA Extensions
- **`LNZ` (Load Non-Zero)**: A hardware-accelerated instruction that automatically skips zero values in memory, significantly reducing instruction count for sparse matrix traversals.
- **`VLOAD` (Vector Load)**: Loads 4 integers at once into specialized vector registers (`v0`-`v7`), increasing throughput.

### 3. Advanced Architecture Features
- **Branch Prediction**: 2-Bit Saturating Counter Branch Predictor to reduce control hazard penalties.
- **Memory Hierarchy**: Simulated Direct-Mapped Cache with configurable latency (Hit: 1 cycle, Miss: 10 cycles).
- **Trace Logging**: Generates `pipeline_trace.csv` for cycle-by-cycle visualization of instruction flow.

## Project Structure
```
.
├── benchmarks/          # Assembly benchmark files
│   └── sparse_sum.asm   # Sparse Vector Summation benchmark
├── src/
│   ├── core/            # Core pipeline logic (SparseFlowCore)
│   ├── hardware/        # Hardware components (RegFile, Memory, Cache, BranchPredictor)
│   ├── isa/             # Instruction definitions
│   ├── utils/           # Loader, Stats, TraceLogger
│   └── main.cpp         # Entry point
├── ISA_Spec.md          # Detailed Instruction Set Architecture specification
├── CMakeLists.txt       # Build configuration
└── run_tests.py         # Automated test runner
```


## Step-by-Step Guide: Building and Running SparseFlow from Scratch

### 1. Prerequisites

Before you begin, ensure you have the following installed:

- **C++17 Compiler**: GCC (Linux), Clang (macOS), or MSVC (Windows)
- **CMake**: For cross-platform build configuration
- **Python 3.x**: For running test scripts (optional, for automated tests)

#### Windows Setup
1. Install [MinGW-w64](https://www.mingw-w64.org/) or [Visual Studio Build Tools](https://visualstudio.microsoft.com/visual-cpp-build-tools/).
2. Install [CMake](https://cmake.org/download/).
3. Add compiler and CMake to your system PATH.

#### Linux/macOS Setup
1. Install build tools:
	- **Ubuntu/Debian**: `sudo apt update && sudo apt install build-essential cmake python3`
	- **Fedora**: `sudo dnf install gcc-c++ make cmake python3`
	- **macOS**: Install Xcode Command Line Tools (`xcode-select --install`) and [Homebrew](https://brew.sh/), then `brew install cmake python3`.

### 2. Clone or Download the Project

If you received a ZIP, extract it. If using git:
```bash
git clone <repo-url>
cd SimASP
```

### 3. Build the Simulator

1. Open a terminal (or PowerShell on Windows) in the project root directory.
2. Create a build directory and configure the project:
	```bash
	mkdir build
	cd build
	cmake ..
	```
3. Compile the project:
	- **Linux/macOS**: `make`
	- **Windows (MinGW)**: `mingw32-make`
	- **Windows (MSVC)**: Open the generated `.sln` in Visual Studio and build, or use `cmake --build .`

4. The executable (`simulator` or `simulator.exe`) will be created in the `build` directory.

### 4. Run the Simulator

To run a benchmark or test program:
```bash
./simulator ../benchmarks/sparse_sum.asm
```
Or, for Windows:
```powershell
simulator.exe ..\benchmarks\sparse_sum.asm
```

#### Command-Line Options
- `--single-cycle` : Run in single-cycle (non-pipelined) mode
- `--show-pipeline` : Display ASCII pipeline diagram after execution
- `--interactive` : Step-by-step interactive mode
- `--help` : Show usage information

Example:
```bash
./simulator ../benchmarks/sparse_sum.asm --show-pipeline
```

### 5. Run Automated Tests (Optional)

To run all test cases and verify correctness:
```bash
python ../run_tests.py
```

### 6. Output Files
- `pipeline_trace.csv` : Cycle-by-cycle trace of pipeline execution
- `test_results.txt` : Test results summary

### 7. Troubleshooting
- Ensure all dependencies are installed and available in your PATH.
- If you encounter build errors, check your compiler version (must support C++17).
- For Windows, use the correct generator in CMake if using MSVC or MinGW.

---

This guide ensures you can build and run the SparseFlow simulator on any major platform from scratch. For further details, see the documentation files in the repository.

## Performance Metrics
The simulator outputs a detailed report including:
- Total Cycles
- Instructions Retired
- CPI (Cycles Per Instruction)
- Cache Hit/Miss Rates
- Branch Prediction Accuracy
- Zero-Skipping Savings (specific to `LNZ`)

### Benchmark Results (1000-element arrays)
| Sparsity | Pipelined | Single-Cycle | Speedup |
|----------|-----------|--------------|---------|
| 60%      | 12,093    | 35,615       | 2.95x   |
| 70%      | 11,405    | 33,165       | 2.91x   |
| 80%      | 10,708    | 30,785       | 2.87x   |
| 90%      | 9,962     | 28,477       | 2.86x   |
| 99%      | 9,270     | 26,441       | 2.85x   |

## Design Rationale
The "SparseFlow" domain was chosen because sparse matrix operations (like SpMV) are memory-bound and control-heavy (checking for zeros). 
- **Pipelining** improves general throughput.
- **`LNZ`** moves the control-flow overhead of checking zeros from software (branches) to hardware, allowing the pipeline to flow smoother.
- **Vector Registers** allow for future SIMD-like parallelism.
