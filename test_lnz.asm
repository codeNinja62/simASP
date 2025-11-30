# Test LNZ (Load Non-Zero)
# Setup Memory
MOV t0, 10      # Base address
MOV t3, 0       # Zero
MOV t4, 77      # Non-Zero 1
MOV t5, 88      # Non-Zero 2

SW t3, 0(t0)    # Mem[10] = 0
SW t3, 1(t0)    # Mem[11] = 0
SW t4, 2(t0)    # Mem[12] = 77
SW t3, 3(t0)    # Mem[13] = 0
SW t5, 4(t0)    # Mem[14] = 88

# Now test LNZ
# t0 points to 10.
LNZ t1, 0(t0)   # Should skip 10, 11. Load 77 from 12. t0 becomes 13.
LNZ t2, 0(t0)   # Should skip 13. Load 88 from 14. t0 becomes 15.

HALT
