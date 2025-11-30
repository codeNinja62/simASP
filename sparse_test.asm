# Sparse Matrix Test
# Demonstrates ZMUL (Zero-Skipping Multiply) and LNZ (Load Non-Zero)

INIT:
    # --- Initialize Vector A (Sparse) at 100 ---
    MOV  t0, 100
    MOV  t3, 0
    SW   t3, 0(t0)   ; A[0] = 0
    MOV  t3, 5
    SW   t3, 1(t0)   ; A[1] = 5
    MOV  t3, 0
    SW   t3, 2(t0)   ; A[2] = 0
    MOV  t3, 4
    SW   t3, 3(t0)   ; A[3] = 4

    # --- Initialize Vector B (Dense) at 110 ---
    MOV  t1, 110
    MOV  t3, 2
    SW   t3, 0(t1)   ; B[0] = 2
    MOV  t3, 3
    SW   t3, 1(t1)   ; B[1] = 3
    MOV  t3, 4
    SW   t3, 2(t1)   ; B[2] = 4
    MOV  t3, 5
    SW   t3, 3(t1)   ; B[3] = 5

    # --- Initialize Vector C (Sparse with Sentinel) at 120 ---
    MOV  s0, 120
    MOV  t3, 0
    SW   t3, 0(s0)   ; C[0] = 0
    SW   t3, 1(s0)   ; C[1] = 0
    MOV  t3, 10
    SW   t3, 2(s0)   ; C[2] = 10
    MOV  t3, 0
    SW   t3, 3(s0)   ; C[3] = 0
    MOV  t3, 20
    SW   t3, 4(s0)   ; C[4] = 20
    MOV  t3, -1
    SW   t3, 5(s0)   ; C[5] = -1 (Sentinel)

    # --- PART 1: ZMUL Dot Product ---
    # Result should be: 0*2 + 5*3 + 0*4 + 4*5 = 0 + 15 + 0 + 20 = 35
    MOV  t0, 100     ; Reset Base A
    MOV  t1, 110     ; Reset Base B
    MOV  t2, 4       ; Loop Count
    MOV  t5, 0       ; Accumulator (Result)

LOOP_ZMUL:
    BZERO t2, PART2
    
    LW   t3, 0(t0)   ; Load A[i]
    LW   t4, 0(t1)   ; Load B[i]
    
    ZMUL t3, t3, t4  ; t3 = A[i] * B[i] (Hardware skips if 0)
    ADD  t5, t5, t3  ; Accumulate
    
    ADDI t0, t0, 1   ; Inc A Ptr
    ADDI t1, t1, 1   ; Inc B Ptr
    ADDI t2, t2, -1  ; Dec Counter
    JMP  LOOP_ZMUL

    # --- PART 2: LNZ Sparse Sum ---
    # Result should be: 10 + 20 = 30
PART2:
    MOV  s0, 120     ; Reset Base C
    MOV  t6, 0       ; Accumulator (Result)
    MOV  s1, -1      ; Sentinel

LOOP_LNZ:
    LNZ  t3, 0(s0)   ; Load Non-Zero. Skips 0s. Updates s0 to next addr.
    
    BEQ  t3, s1, DONE ; If Sentinel (-1), Break
    
    ADD  t6, t6, t3  ; Sum
    JMP  LOOP_LNZ

DONE:
    HALT
