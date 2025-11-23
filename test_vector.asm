# Test Vector Operations
# SparseFlow custom vector instructions

# Initialize scalar values
ADDI t0, zero, 100    # Base address for vector A
ADDI t1, zero, 200    # Base address for vector B
ADDI t2, zero, 300    # Base address for result

# Store test vectors in memory
ADDI a0, zero, 1
SW   a0, 100(zero)    # A[0] = 1
ADDI a0, zero, 2
SW   a0, 104(zero)    # A[1] = 2
ADDI a0, zero, 3
SW   a0, 108(zero)    # A[2] = 3
ADDI a0, zero, 4
SW   a0, 112(zero)    # A[3] = 4

ADDI a1, zero, 10
SW   a1, 200(zero)    # B[0] = 10
ADDI a1, zero, 20
SW   a1, 204(zero)    # B[1] = 20
ADDI a1, zero, 30
SW   a1, 208(zero)    # B[2] = 30
ADDI a1, zero, 40
SW   a1, 212(zero)    # B[3] = 40

# Vector Add: C = A + B
VADD v0, t0, t1       # v0 = vector load from A + B
VST  v0, 0(t2)        # Store result at address 300

# Expected: C = [11, 22, 33, 44]

HALT
