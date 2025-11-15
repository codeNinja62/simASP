# Test Branch Prediction
# Various branch patterns to test predictor

# Initialize
ADDI t0, zero, 5      # Loop counter
ADDI t1, zero, 0      # Sum

# Simple loop (should predict well after warmup)
loop:
    ADD  t1, t1, t0   # sum += counter
    ADDI t0, t0, -1   # counter--
    BNE  t0, zero, loop  # branch back if counter != 0

# Result: t1 should be 5+4+3+2+1 = 15

# Alternating pattern (harder to predict)
ADDI t2, zero, 1
ADDI t3, zero, 0
BEQ  t2, zero, skip1  # not taken
ADDI t3, t3, 1
skip1:
BNE  t2, zero, skip2  # taken
ADDI t3, t3, 10
skip2:
BEQ  t2, zero, skip3  # not taken
ADDI t3, t3, 1
skip3:

HALT
