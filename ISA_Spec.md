# SparseFlow ASP Simulator - ISA Specification

## 1. Overview
The **SparseFlow** Architecture is a specialized subset of RISC-V designed for **Sparse Matrix Operations**. It includes standard integer arithmetic, control flow, and custom extensions for handling sparse data structures (Compressed Sparse Row - CSR) and vector operations.

## 2. Instruction Formats (32-bit)

The ISA uses standard RISC-V 32-bit instruction formats:

### R-Type (Register-Register)
```
 31       25 24   20 19   15 14  12 11    7 6      0
+----------+-------+-------+------+-------+--------+
|  funct7  |  rs2  |  rs1  |funct3|   rd  | opcode |
+----------+-------+-------+------+-------+--------+
     7        5       5       3       5       7
```

### I-Type (Immediate)
```
 31                  20 19   15 14  12 11    7 6      0
+---------------------+-------+------+-------+--------+
|      imm[11:0]      |  rs1  |funct3|   rd  | opcode |
+---------------------+-------+------+-------+--------+
          12             5       3       5       7
```

### S-Type (Store)
```
 31       25 24   20 19   15 14  12 11    7 6      0
+----------+-------+-------+------+-------+--------+
| imm[11:5]|  rs2  |  rs1  |funct3|imm[4:0]| opcode |
+----------+-------+-------+------+-------+--------+
     7        5       5       3       5       7
```

### B-Type (Branch)
```
 31    30     25 24   20 19   15 14  12 11   8  7   6      0
+----+--------+-------+-------+------+------+----+--------+
|imm |imm[10:5]|  rs2  |  rs1  |funct3|imm[4:1]|imm| opcode |
|[12]|        |       |       |      |       |[11]|        |
+----+--------+-------+-------+------+------+----+--------+
  1      6       5       5       3       4     1      7
```

## 3. Complete Instruction Encoding

### 3.1 Standard RISC-V Subset

| Mnemonic | Format | opcode  | funct3 | funct7  | 32-bit Encoding Example |
|----------|--------|---------|--------|---------|-------------------------|
| `ADD`    | R-Type | 0110011 | 000    | 0000000 | `0000000_rs2_rs1_000_rd_0110011` |
| `SUB`    | R-Type | 0110011 | 000    | 0100000 | `0100000_rs2_rs1_000_rd_0110011` |
| `SLT`    | R-Type | 0110011 | 010    | 0000000 | `0000000_rs2_rs1_010_rd_0110011` |
| `ADDI`   | I-Type | 0010011 | 000    | -       | `imm[11:0]_rs1_000_rd_0010011` |
| `LW`     | I-Type | 0000011 | 010    | -       | `imm[11:0]_rs1_010_rd_0000011` |
| `SW`     | S-Type | 0100011 | 010    | -       | `imm[11:5]_rs2_rs1_010_imm[4:0]_0100011` |
| `BEQ`    | B-Type | 1100011 | 000    | -       | `imm[12,10:5]_rs2_rs1_000_imm[4:1,11]_1100011` |
| `JR`     | I-Type | 1100111 | 000    | -       | `000000000000_rs1_000_00000_1100111` |
| `JMP`    | J-Type | 1101111 | -      | -       | `imm[20,10:1,11,19:12]_rd_1101111` |

### 3.2 Custom SparseFlow Extensions

| Mnemonic | Format  | opcode  | funct3 | funct7  | Description |
|----------|---------|---------|--------|---------|-------------|
| `LNZ`    | I-Type  | 1110111 | 000    | -       | Load Non-Zero (auto-skip zeros) |
| `ZMUL`   | R-Type  | 1110111 | 001    | 0000000 | Zero-Skip Multiply |
| `VLOAD`  | I-Type  | 1110111 | 010    | -       | Vector Load (4 words) |
| `BZERO`  | B-Type  | 1110111 | 011    | -       | Branch if Zero |
| `MOV`    | I-Type  | 0010011 | 000    | -       | Pseudo: ADDI rd, rs/x0, imm |
| `HALT`   | Custom  | 1111111 | 111    | 1111111 | Stop simulation |

### 3.3 Encoding Examples

**Example 1: ADD t0, t1, t2**
```
ADD x5, x6, x7
R-Type: funct7=0000000, rs2=00111, rs1=00110, funct3=000, rd=00101, opcode=0110011
Binary: 0000000_00111_00110_000_00101_0110011
Hex:    0x007302B3
```

**Example 2: ADDI t0, t1, 10**
```
ADDI x5, x6, 10
I-Type: imm=000000001010, rs1=00110, funct3=000, rd=00101, opcode=0010011
Binary: 000000001010_00110_000_00101_0010011
Hex:    0x00A30293
```

**Example 3: LW t0, 4(t1)**
```
LW x5, 4(x6)
I-Type: imm=000000000100, rs1=00110, funct3=010, rd=00101, opcode=0000011
Binary: 000000000100_00110_010_00101_0000011
Hex:    0x00432283
```

**Example 4: SW t0, 8(t1)**
```
SW x5, 8(x6)
S-Type: imm[11:5]=0000000, rs2=00101, rs1=00110, funct3=010, imm[4:0]=01000, opcode=0100011
Binary: 0000000_00101_00110_010_01000_0100011
Hex:    0x00532423
```

**Example 5: BEQ t0, t1, +8**
```
BEQ x5, x6, 8
B-Type: imm=0000000001000 (offset 8)
Binary: 0_000000_00110_00101_000_0100_0_1100011
Hex:    0x00628463
```

**Example 6: LNZ t0, 0(t1) [Custom]**
```
LNZ x5, 0(x6)
I-Type: imm=000000000000, rs1=00110, funct3=000, rd=00101, opcode=1110111
Binary: 000000000000_00110_000_00101_1110111
Hex:    0x000302F7
```

## 4. Register File

| Register | ABI Name | Description |
|----------|----------|-------------|
| x0       | zero     | Hardwired zero |
| x1       | ra       | Return address |
| x2       | sp       | Stack pointer |
| x5-x7    | t0-t2    | Temporaries |
| x10-x11  | a0-a1    | Function arguments/return |
| x28-x31  | t3-t6    | Additional temporaries |
| v0-v7    | -        | Vector registers (4x32-bit each) |

## 5. Pipeline Stages
1. **IF (Fetch)**: Fetch instruction from memory. Update PC (or predict branch).
2. **ID (Decode)**: Decode instruction, read register file, check for hazards.
3. **EX (Execute)**: ALU operations, address calculation, branch resolution.
4. **MEM (Memory)**: Access data memory (L1 Cache simulated).
5. **WB (Writeback)**: Write result to register file.

## 6. Hazard Handling
- **Data Hazards**: Solved via **Forwarding** (EX->EX, MEM->EX) and **Stalling** (Load-Use hazard).
- **Control Hazards**: Handled via **2-Bit Saturating Counter Branch Predictor**. 
  - States: Strongly Not Taken (00) → Weakly Not Taken (01) → Weakly Taken (10) → Strongly Taken (11)
  - Mispredictions cause a pipeline flush.
  - Typical accuracy: 85-95% on loop-heavy workloads.

## 7. Custom Instruction Details

### LNZ (Load Non-Zero) - Hardware Sparse Acceleration
**Purpose**: Efficiently iterate through sparse arrays by skipping zero values in hardware.

**Operation**:
```
value = Mem[rs1 + imm]
if (value == 0):
    rs1 += 4          # Auto-increment pointer
    repeat next cycle # Hardware stall/skip
else:
    rd = value
    rs1 += 4          # Move to next element
```

**Benefit**: Eliminates branch overhead for zero-checking in sparse matrix traversal.

### ZMUL (Zero-Skip Multiply)
**Purpose**: Fast-path multiplication that detects zero operands.

**Operation**:
```
if (rs1 == 0 OR rs2 == 0):
    rd = 0            # 1-cycle fast path
else:
    rd = rs1 * rs2    # Normal multiply
```

**Benefit**: Reduces average multiply latency in sparse computations.
