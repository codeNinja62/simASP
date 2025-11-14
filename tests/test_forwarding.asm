# Test Forwarding Paths
# Verify EX-EX and MEM-EX forwarding

# Test 1: EX-EX forwarding (back-to-back ALU)
ADDI t0, zero, 10     # t0 = 10
ADD  t1, t0, t0       # t1 = t0 + t0 = 20 (needs EX-EX forward)
ADD  t2, t1, t0       # t2 = t1 + t0 = 30 (needs EX-EX forward)

# Test 2: MEM-EX forwarding (2 cycles apart)
ADDI t3, zero, 5      # t3 = 5
NOP                   # gap
ADD  t4, t3, t0       # t4 = t3 + t0 = 15 (needs MEM-EX forward)

# Test 3: Load followed by ALU (Load-Use stall then forward)
SW   t0, 0(zero)      # Store 10 at addr 0
LW   t5, 0(zero)      # t5 = 10 (load)
ADD  t6, t5, t0       # t6 = t5 + t0 = 20 (stall then MEM-EX forward)

HALT
