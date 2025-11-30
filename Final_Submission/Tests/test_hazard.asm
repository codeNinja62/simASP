# Test Data Hazards
# Verify stall and forward behavior

# Test 1: RAW hazard requiring stall (load-use)
ADDI t0, zero, 100
SW   t0, 0(zero)      # Mem[0] = 100
LW   t1, 0(zero)      # t1 = 100
ADD  t2, t1, t1       # t2 = 200 (needs stall + forward)

# Test 2: No hazard (enough distance)
ADDI t3, zero, 10
NOP
NOP
ADD  t4, t3, t3       # t4 = 20 (no hazard)

# Test 3: WAW hazard (write-after-write, no stall needed in our design)
ADDI t5, zero, 1
ADDI t5, zero, 2
ADD  t6, t5, zero     # t6 should be 2

# Test 4: Multiple forwards in one instruction
ADDI a0, zero, 3
ADDI a1, zero, 4
ADD  a2, a0, a1       # a2 = 7 (both operands forwarded)

HALT
