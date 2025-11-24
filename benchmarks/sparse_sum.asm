# Sparse Sum Benchmark
# Sums non-zero elements from an array using LNZ

# 1. Initialize Registers
MOV t0, 100     # Start Address
MOV t6, 110     # End Address (10 elements for brevity)
MOV s0, 0       # Accumulator (Sum)

# 2. Initialize Memory (Sparse Pattern)
# [100] = 5
MOV t1, 5
SW t1, 0(t0)

# [101] = 0
MOV t1, 0
SW t1, 1(t0)

# [102] = 0
SW t1, 2(t0)

# [103] = 8
MOV t1, 8
SW t1, 3(t0)

# [104] = 0
MOV t1, 0
SW t1, 4(t0)

# [105] = 12
MOV t1, 12
SW t1, 5(t0)

# [106] = 0
MOV t1, 0
SW t1, 6(t0)

# [107] = 0
SW t1, 7(t0)

# [108] = 3
MOV t1, 3
SW t1, 8(t0)

# [109] = 7 (Changed from 0 to ensure termination)
MOV t1, 7
SW t1, 9(t0)

# [110] = Sentinel (Non-Zero)
MOV t1, 99
SW t1, 10(t0)

# 3. The Loop
# Reset t0 to start
MOV t0, 100

loop:
BEQ t0, t6, done
LNZ t1, 0(t0)   # Load Non-Zero. Skips zeros. Increments t0.
ADD s0, s0, t1  # Sum += val
JMP loop

done:
# 4. Vector Burst (Just to show off)
VLOAD v0, 0(t0) # Load whatever is after the array (garbage or zeros)

HALT
