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
- **Branch Prediction**: 1-Bit Dynamic Branch Predictor to reduce control hazard penalties.
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

## Building and Running

### Prerequisites
- C++17 Compiler (GCC/Clang/MSVC)
- CMake

### Build
```bash
mkdir build
cd build
cmake ..
make
```

### Run Simulator
```bash
./simulator benchmarks/sparse_sum.asm
```

### Run Tests
```bash
python run_tests.py
```

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
