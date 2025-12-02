# SparseFlow Simulator Documentation

**Project Name:** SparseFlow Simulator  
**Version:** 1.0  
**Date:** November 26, 2025  
**Language:** C++17  

---

## 1. Project Overview
The **SparseFlow Simulator** is a custom cycle-accurate simulator for a 5-stage pipelined processor based on a subset of the RISC-V ISA. It introduces custom extensions optimized for sparse data processing (e.g., `LNZ` - Load Non-Zero, `ZMUL` - Zero-Skipping Multiply).

The simulator models:
*   **5-Stage Pipeline**: Fetch (IF), Decode (ID), Execute (EX), Memory (MEM), Writeback (WB).
*   **Hazard Handling**: Data forwarding, Load-Use stalls, and Control hazard flushing.
*   **Memory Hierarchy**: Simple instruction memory and data memory with a simulated cache latency model.
*   **Branch Prediction**: 2-bit saturating counter branch predictor.
*   **Custom ISA Extensions**: Specialized instructions for sparse matrix operations.

---

## 2. Directory Structure

```
Project - ASP/
├── src/
│   ├── core/               # Core pipeline logic
│   │   ├── SparseFlowCore.cpp/.h   # Main pipeline controller
│   │   └── PipelineRegisters.h     # Pipeline register definitions (IF/ID, etc.)
│   ├── hardware/           # Hardware component models
│   │   ├── Memory.cpp/.h           # RAM and Cache model
│   │   ├── RegisterFile.cpp/.h     # Scalar (x0-x31) and Vector (v0-v7) registers
│   │   ├── BranchPredictor.cpp/.h  # Branch prediction logic
│   │   └── Cache.cpp/.h            # Cache simulation
│   ├── isa/                # Instruction Set Architecture
│   │   ├── Instruction.h           # Opcode enums and Instruction struct
│   │   └── ISA.h                   # General ISA constants
│   ├── utils/              # Utility classes
│   │   ├── Loader.cpp/.h           # Assembly file parser
│   │   ├── Stats.cpp/.h            # Performance statistics tracker
│   │   └── TraceLogger.cpp/.h      # Cycle-by-cycle CSV logger
│   └── main.cpp            # Entry point
├── assignment3_prog1.asm   # Test Program 1 (Arithmetic)
├── assignment3_prog2.asm   # Test Program 2 (Loop/Threshold)
├── assignment3_func.asm    # Test Program 3 (Function Call)
└── simulator.exe           # Compiled executable
```

---

## 3. Architecture Details

### 3.1. Core Pipeline (`SparseFlowCore`)
The core implements a classic 5-stage pipeline.
1.  **Fetch (IF)**: Fetches instruction from memory at `PC`. Uses Branch Predictor for `BEQ`/`JMP`.
2.  **Decode (ID)**: Reads registers (`rs1`, `rs2`). Detects **Load-Use Hazards** and inserts stalls (bubbles) if necessary.
3.  **Execute (EX)**: Performs ALU operations.
    *   **Forwarding Unit**: Forwards data from MEM or WB stages to EX to resolve data hazards.
    *   **Zero-Skipping**: `ZMUL` checks if operands are zero; if so, it skips execution cycles.
    *   **Branch Resolution**: Verifies branch prediction. If mispredicted, flushes IF/ID and corrects PC.
4.  **Memory (MEM)**: Accesses data memory.
    *   **Cache Model**: Simulates latency (1 cycle hit, 10 cycle miss). Stalls pipeline on miss.
    *   **LNZ Optimization**: `LNZ` checks if loaded value is zero. If zero, it auto-increments the pointer and skips the value (simulating hardware sparse skipping).
5.  **Writeback (WB)**: Writes results back to the Register File.

### 3.2. Memory System (`Memory`)
*   **Instruction Memory**: Read-only, indexed by PC.
*   **Data Memory**: 4KB addressable space.
*   **Cache**: Direct-mapped cache simulation.
    *   `requestAccess(addr)` returns latency cycles.
    *   Core stalls if latency > 1.

### 3.3. Register File (`RegisterFile`)
*   **Scalar Registers**: 32 x 32-bit registers (`x0`-`x31`).
    *   `x0` is hardwired to 0.
    *   Standard RISC-V ABI names supported (`zero`, `ra`, `sp`, `t0`-`t6`, `a0`-`a7`, `s0`-`s1`).
*   **Vector Registers**: 8 x 128-bit registers (`v0`-`v7`), modeled as 4 integers each.

---

## 4. Instruction Set Architecture (ISA)

The simulator supports a subset of RISC-V plus custom extensions.

### 4.1. Standard RISC-V Subset
| Opcode | Format | Description |
| :--- | :--- | :--- |
| `ADD rd, rs1, rs2` | R-Type | `rd = rs1 + rs2` |
| `SUB rd, rs1, rs2` | R-Type | `rd = rs1 - rs2` |
| `ADDI rd, rs1, imm` | I-Type | `rd = rs1 + imm` |
| `LW rd, off(rs1)` | I-Type | `rd = Mem[rs1 + off]` |
| `SW rs2, off(rs1)` | S-Type | `Mem[rs1 + off] = rs2` |
| `BEQ rs1, rs2, label` | B-Type | Branch if `rs1 == rs2` |
| `JMP label` | J-Type | Unconditional Jump |
| `JR rs1` | I-Type | Jump to address in `rs1` (Return) |
| `SLT rd, rs1, rs2` | R-Type | `rd = (rs1 < rs2) ? 1 : 0` |

### 4.2. Custom Extensions (SparseFlow)
| Opcode | Format | Description |
| :--- | :--- | :--- |
| `LNZ rd, off(rs1)` | I-Type | **Load Non-Zero**. Loads value. If 0, skips writeback and increments `rs1` to next address automatically. |
| `ZMUL rd, rs1, rs2` | R-Type | **Zero-Skip Multiply**. If `rs1` or `rs2` is 0, result is 0 (1 cycle). Else, performs multiply (4 cycles). |
| `VLOAD vd, off(rs1)` | I-Type | **Vector Load**. Loads 4 consecutive words into vector register `vd`. |
| `BZERO rs1, label` | B-Type | **Branch Zero**. Branch if `rs1 == 0`. Optimized for sparse checks. |
| `MOV rd, val/reg` | Pseudo | Pseudo-instruction. `MOV rd, 5` -> `ADDI rd, x0, 5`. `MOV rd, rs` -> `ADDI rd, rs, 0`. |
| `HALT` | X-Type | Stops simulation. |

---

## 5. Build and Usage

### 5.1. Compilation
Use `g++` with C++17 standard.

**Windows (PowerShell):**
```powershell
g++ -std=c++17 -I src/core -I src/utils -I src/hardware -I src/isa src/main.cpp src/core/SparseFlowCore.cpp src/utils/Loader.cpp src/hardware/Memory.cpp src/hardware/RegisterFile.cpp src/hardware/BranchPredictor.cpp src/utils/Stats.cpp src/utils/TraceLogger.cpp src/hardware/Cache.cpp -o simulator
```

### 5.2. Running
```powershell
./simulator <assembly_file.asm>
```

**Example:**
```powershell
./simulator assignment3_prog2.asm
```

### 5.3. Output
The simulator prints:
1.  **Loader Output**: Parsed instructions and labels.
2.  **Cycle-by-Cycle Trace**: (Optional debug prints).
3.  **Performance Report**:
    *   Total Cycles
    *   Instructions Retired
    *   CPI / IPC
    *   Stall Cycles
    *   Branch Mispredictions
4.  **Register Dump**: Final state of all registers.

---

## 6. Key Features Implementation

### 6.1. Hazard Detection
*   **Load-Use Hazard**: Detected in **Decode** stage. If `ID` needs a register that `EX` (which is a Load) is about to write, a bubble is inserted in `EX`, and `PC`/`IF_ID` are stalled.
*   **Control Hazard**: Detected in **Execute** stage. If branch is taken (and not predicted), `IF_ID` is flushed, and `PC` is updated to target.

### 6.2. Forwarding
*   **EX-to-EX**: Forwards ALU result from `EX/MEM` pipeline register to `ID/EX` inputs if `rs1` or `rs2` matches `rd` of previous instruction.
*   **MEM-to-EX**: Forwards Writeback result from `MEM/WB` (shadow) to `ID/EX` inputs if `rs1` or `rs2` matches `rd` of instruction 2 cycles ago.

### 6.3. Loader
*   Supports comments (`#`, `//`, `;`).
*   Supports labels (`LOOP:`).
*   Supports register aliases (`t0`, `a0`, `sp`, `ra`).
*   Auto-translates `MOV` pseudo-instructions.

---

## 7. Performance Benchmarks

### 7.1. Sparsity Level Comparison (1000 elements)
Tests across matrices with varying sparsity levels demonstrate consistent performance gains:

| Sparsity | Pipelined Cycles | Single-Cycle | Speedup | Zero-Skips |
|----------|------------------|--------------|---------|------------|
| 60%      | 12,093           | 35,615       | 2.95x   | 599        |
| 70%      | 11,405           | 33,165       | 2.91x   | 700        |
| 80%      | 10,708           | 30,785       | 2.87x   | 799        |
| 90%      | 9,962            | 28,477       | 2.86x   | 899        |
| 99%      | 9,270            | 26,441       | 2.85x   | 989        |

**Key Observations:**
- Pipeline speedup is consistent (~2.9x) across all sparsity levels
- Zero-skips increase proportionally with sparsity
- Even at 60% sparsity (40% dense), LNZ provides significant benefit

### 7.2. Large-Scale Test (512x512 Matrix)
Matrix Size: 262,144 elements | Sparsity: ~99.98% | Non-Zeros: 50

| Metric              | Pipelined | Single-Cycle |
|---------------------|-----------|--------------|
| Total Cycles        | 566,038   | 566,919      |
| Zero-Skips          | 262,093   | 262,093      |
| Instructions Retired| 311       | 311          |

---
