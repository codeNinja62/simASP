# SparseFlow Simulator Documentation

## 1. Project Overview

The **SparseFlow Simulator** is a cycle-accurate simulator for a custom 
processor designed to accelerate sparse matrix operations.

### Goals
- Model a 5-stage pipelined processor
- Implement custom ISA extensions for sparse data handling
- Provide performance metrics and analysis

## Phase 1: Single-Cycle Model

The initial implementation uses a single-cycle execution model where
each instruction completes in one cycle. This serves as:

1. A correctness baseline for the pipelined version
2. A simpler debugging environment
3. A performance comparison reference

### Completed Features
- Basic RISC-V instruction subset (ADD, SUB, LW, SW, BEQ, JMP)
- Register file with 32 scalar registers
- Memory system with separate instruction/data memory
- Assembly loader with label support
