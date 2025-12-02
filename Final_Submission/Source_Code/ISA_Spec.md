# SparseFlow ASP Simulator - ISA Specification

## 1. Overview
The **SparseFlow** Architecture is a specialized subset of RISC-V designed for **Sparse Matrix Operations**. It includes standard integer arithmetic, control flow, and custom extensions for handling sparse data structures (Compressed Sparse Row - CSR) and vector operations.

## 2. Instruction Formats
The ISA uses standard 32-bit RISC-V instruction formats:
- **R-Type**: Register-Register operations
- **I-Type**: Immediate operations and Loads
- **S-Type**: Stores
- **B-Type**: Conditional Branches
- **J-Type**: Unconditional Jumps (Simulated via I-Type JMP for simplicity)

## 3. Instruction Set

### 3.1 Standard RISC-V Subset

| Mnemonic | Type | Opcode | Description |
|----------|------|--------|-------------|
| `ADD`    | R    | 0x33   | `rd = rs1 + rs2` |
| `SUB`    | R    | 0x33   | `rd = rs1 - rs2` |
| `MUL`    | R    | 0x33   | `rd = rs1 * rs2` |
| `AND`    | R    | 0x33   | `rd = rs1 & rs2` |
| `OR`     | R    | 0x33   | `rd = rs1 | rs2` |
| `XOR`    | R    | 0x33   | `rd = rs1 ^ rs2` |
| `SLT`    | R    | 0x33   | `rd = (rs1 < rs2) ? 1 : 0` |
| `ADDI`   | I    | 0x13   | `rd = rs1 + imm` |
| `LW`     | I    | 0x03   | `rd = Mem[rs1 + imm]` |
| `SW`     | S    | 0x23   | `Mem[rs1 + imm] = rs2` |
| `BEQ`    | B    | 0x63   | `if (rs1 == rs2) PC += imm` |
| `BNE`    | B    | 0x63   | `if (rs1 != rs2) PC += imm` |

### 3.2 Custom Extensions (SparseFlow)

#### `LNZ` - Load Non-Zero
**Format**: I-Type
**Opcode**: `0x77` (Custom)
**Syntax**: `LNZ rd, rs1, imm`
**Description**: 
Designed for iterating through sparse arrays. It checks the value at `Mem[rs1]`.
- If `Mem[rs1] == 0`: The hardware automatically increments `rs1` (pointer) and repeats the check in the next cycle (stall/skip), effectively skipping zeros in hardware.
- If `Mem[rs1] != 0`: The value is loaded into `rd`, and `rs1` is incremented to point to the next element.
**Benefit**: Eliminates software loop overhead for skipping zeros in sparse matrices.

#### `VLOAD` - Vector Load
**Format**: Custom
**Opcode**: `0x88` (Custom)
**Syntax**: `VLOAD vD, rs1`
**Description**: 
Loads 4 consecutive integers from memory starting at `rs1` into a vector register `vD` (v0-v7).
**Benefit**: Increases memory bandwidth utilization for dense sections of matrices.

#### `BZERO` - Branch if Zero
**Format**: B-Type
**Opcode**: `0x99` (Custom)
**Syntax**: `BZERO rs1, label`
**Description**: 
`if (rs1 == 0) PC += imm`. Optimized check for zero, common in null-pointer checks or loop counters.

#### `JMP` - Unconditional Jump
**Format**: I-Type (Simplified)
**Opcode**: `0x6F`
**Syntax**: `JMP label`
**Description**: 
Unconditionally jumps to the target label.

## 4. Pipeline Stages
1. **IF (Fetch)**: Fetch instruction from memory. Update PC (or predict branch).
2. **ID (Decode)**: Decode instruction, read register file, check for hazards.
3. **EX (Execute)**: ALU operations, address calculation, branch resolution.
4. **MEM (Memory)**: Access data memory (L1 Cache simulated).
5. **WB (Writeback)**: Write result to register file.

## 5. Hazard Handling
- **Data Hazards**: Solved via **Forwarding** (EX->EX, MEM->EX) and **Stalling** (Load-Use hazard).
- **Control Hazards**: Handled via **2-Bit Saturating Counter Branch Predictor**. Mispredictions cause a pipeline flush.
