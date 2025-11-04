# SparseFlow Test Program
# Tests: LNZ and ZMUL instructions

# Setup
MOV t0, 10          # t0 = 10 (base address)

# Test LNZ (Load Non-Zero)
LW t1, 0(t0)        # Load from Mem[10]
ADD t2, t1, t0      # t2 = t1 + t0

# Test ZMUL (Zero-Skip Multiply)
MOV t4, 0           # t4 = 0
ZMUL a0, t1, t4     # Should skip (t4 is 0)

# Test with non-zero
MOV t5, 5
ZMUL a1, t5, t0     # a1 = 5 * 10 = 50

HALT
