# SparseFlow Test Program
# Tests: Hazards, Forwarding, Zero-Skipping, Branching

# 1. Setup
MOV t0, 10          # t0 = 10

# 2. Test Load-Use Hazard (Stall)
LW t1, 0(t0)        # Load from Mem[10] into t1 (Should be 99)
ADD t2, t1, t0      # Uses t1 immediately. Should Stall 1 cycle.

# 3. Test Forwarding (EX-EX)
SUB s4, t2, t0      # t2 is in EX/MEM (from ADD), t0 is in Reg.

# 4. Test Zero-Skipping
MOV t4, 0           # t4 = 0
ZMUL a0, t1, t4     # Should Skip (t4 is 0)

# 5. Test Branching
BZERO t4, target    # Taken (t4 is 0). Skips next instruction.

MOV a1, 777         # Should be SKIPPED

target:
MOV a1, 888         # Target of Branch
HALT
