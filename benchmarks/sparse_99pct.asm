# Sparse Matrix Benchmark
# Size: 1000 elements
# Sparsity: 99% zeros (990 zeros, 10 non-zeros)
# Expected Sum: 518

INIT:
    MOV t0, 0       ; Base Address

    # Initializing 10 non-zero elements
    MOV t3, 23
    SW  t3, 13(t0)
    MOV t3, 30
    SW  t3, 123(t0)
    MOV t3, 69
    SW  t3, 147(t0)
    MOV t3, 69
    SW  t3, 224(t0)
    MOV t3, 17
    SW  t3, 486(t0)
    MOV t3, 48
    SW  t3, 646(t0)
    MOV t3, 55
    SW  t3, 670(t0)
    MOV t3, 43
    SW  t3, 841(t0)
    MOV t3, 92
    SW  t3, 904(t0)
    MOV t3, 72
    SW  t3, 931(t0)

    # Sentinel at end
    MOV t3, -1
    SW  t3, 1000(t0)

# ========== METHOD 1: Hardware LNZ Sparse Scan ==========
LNZ_TEST:
    MOV t0, 0       ; Reset Pointer
    MOV t5, 0                 ; Accumulator (LNZ Result)
    MOV s1, -1                ; Sentinel Value

LNZ_LOOP:
    LNZ t3, 0(t0)             ; Load Non-Zero (skips zeros in HW)
    BEQ t3, s1, LNZ_DONE      ; If Sentinel, Exit
    ADD t5, t5, t3            ; Sum += Val
    JMP LNZ_LOOP

LNZ_DONE:
    # t5 now contains sum using LNZ

# ========== METHOD 2: Software LW Loop ==========
SW_TEST:
    MOV t0, 0       ; Reset Pointer
    MOV t1, 1000    ; Loop Count
    MOV t6, 0                 ; Accumulator (SW Result)
    MOV s0, 0                 ; Zero constant for comparison

SW_LOOP:
    BZERO t1, SW_DONE         ; If counter == 0, Exit
    LW   t3, 0(t0)            ; Load value (no skip)
    BEQ  t3, s0, SW_SKIP      ; If value == 0, skip add
    ADD  t6, t6, t3           ; Sum += Val
SW_SKIP:
    ADDI t0, t0, 1            ; Increment pointer
    ADDI t1, t1, -1           ; Decrement counter
    JMP  SW_LOOP

SW_DONE:
    # t6 now contains sum using standard LW
    HALT
