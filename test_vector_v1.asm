# Test VLOAD (Vector Load) with v1
# Setup Memory
MOV t0, 10      # Base address

# Initialize Memory [10, 11, 12, 13]
MOV t1, 1
SW t1, 0(t0)    # Mem[10] = 1
MOV t1, 2
SW t1, 1(t0)    # Mem[11] = 2
MOV t1, 3
SW t1, 2(t0)    # Mem[12] = 3
MOV t1, 4
SW t1, 3(t0)    # Mem[13] = 4

# Test VLOAD
# Should load [1, 2, 3, 4] into v1
VLOAD v1, 0(t0)

HALT
