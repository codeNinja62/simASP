# Sparse Matrix Benchmark
# Size: 1000 elements
# Sparsity: 90% zeros (900 zeros, 100 non-zeros)
# Expected Sum: 4848

INIT:
    MOV t0, 0       ; Base Address

    # Initializing 100 non-zero elements
    MOV t3, 37
    SW  t3, 16(t0)
    MOV t3, 85
    SW  t3, 33(t0)
    MOV t3, 24
    SW  t3, 36(t0)
    MOV t3, 39
    SW  t3, 42(t0)
    MOV t3, 68
    SW  t3, 43(t0)
    MOV t3, 72
    SW  t3, 55(t0)
    MOV t3, 67
    SW  t3, 86(t0)
    MOV t3, 23
    SW  t3, 93(t0)
    MOV t3, 4
    SW  t3, 117(t0)
    MOV t3, 17
    SW  t3, 125(t0)
    MOV t3, 21
    SW  t3, 127(t0)
    MOV t3, 56
    SW  t3, 150(t0)
    MOV t3, 93
    SW  t3, 164(t0)
    MOV t3, 15
    SW  t3, 172(t0)
    MOV t3, 60
    SW  t3, 182(t0)
    MOV t3, 52
    SW  t3, 186(t0)
    MOV t3, 73
    SW  t3, 187(t0)
    MOV t3, 23
    SW  t3, 194(t0)
    MOV t3, 57
    SW  t3, 208(t0)
    MOV t3, 31
    SW  t3, 213(t0)
    MOV t3, 28
    SW  t3, 230(t0)
    MOV t3, 50
    SW  t3, 231(t0)
    MOV t3, 81
    SW  t3, 241(t0)
    MOV t3, 78
    SW  t3, 242(t0)
    MOV t3, 47
    SW  t3, 263(t0)
    MOV t3, 18
    SW  t3, 267(t0)
    MOV t3, 53
    SW  t3, 270(t0)
    MOV t3, 77
    SW  t3, 272(t0)
    MOV t3, 80
    SW  t3, 280(t0)
    MOV t3, 93
    SW  t3, 311(t0)
    MOV t3, 34
    SW  t3, 316(t0)
    MOV t3, 25
    SW  t3, 322(t0)
    MOV t3, 75
    SW  t3, 325(t0)
    MOV t3, 67
    SW  t3, 373(t0)
    MOV t3, 45
    SW  t3, 380(t0)
    MOV t3, 60
    SW  t3, 383(t0)
    MOV t3, 66
    SW  t3, 388(t0)
    MOV t3, 13
    SW  t3, 401(t0)
    MOV t3, 77
    SW  t3, 409(t0)
    MOV t3, 3
    SW  t3, 437(t0)
    MOV t3, 66
    SW  t3, 443(t0)
    MOV t3, 25
    SW  t3, 455(t0)
    MOV t3, 98
    SW  t3, 465(t0)
    MOV t3, 89
    SW  t3, 472(t0)
    MOV t3, 42
    SW  t3, 516(t0)
    MOV t3, 5
    SW  t3, 527(t0)
    MOV t3, 89
    SW  t3, 534(t0)
    MOV t3, 17
    SW  t3, 551(t0)
    MOV t3, 41
    SW  t3, 565(t0)
    MOV t3, 7
    SW  t3, 570(t0)
    MOV t3, 2
    SW  t3, 573(t0)
    MOV t3, 35
    SW  t3, 577(t0)
    MOV t3, 82
    SW  t3, 578(t0)
    MOV t3, 56
    SW  t3, 579(t0)
    MOV t3, 22
    SW  t3, 591(t0)
    MOV t3, 15
    SW  t3, 592(t0)
    MOV t3, 8
    SW  t3, 598(t0)
    MOV t3, 44
    SW  t3, 617(t0)
    MOV t3, 94
    SW  t3, 618(t0)
    MOV t3, 4
    SW  t3, 629(t0)
    MOV t3, 23
    SW  t3, 634(t0)
    MOV t3, 68
    SW  t3, 651(t0)
    MOV t3, 50
    SW  t3, 667(t0)
    MOV t3, 67
    SW  t3, 682(t0)
    MOV t3, 69
    SW  t3, 683(t0)
    MOV t3, 69
    SW  t3, 690(t0)
    MOV t3, 45
    SW  t3, 693(t0)
    MOV t3, 95
    SW  t3, 694(t0)
    MOV t3, 53
    SW  t3, 708(t0)
    MOV t3, 29
    SW  t3, 715(t0)
    MOV t3, 44
    SW  t3, 716(t0)
    MOV t3, 89
    SW  t3, 726(t0)
    MOV t3, 2
    SW  t3, 739(t0)
    MOV t3, 75
    SW  t3, 754(t0)
    MOV t3, 87
    SW  t3, 758(t0)
    MOV t3, 80
    SW  t3, 759(t0)
    MOV t3, 31
    SW  t3, 761(t0)
    MOV t3, 42
    SW  t3, 764(t0)
    MOV t3, 64
    SW  t3, 767(t0)
    MOV t3, 31
    SW  t3, 783(t0)
    MOV t3, 18
    SW  t3, 789(t0)
    MOV t3, 30
    SW  t3, 792(t0)
    MOV t3, 40
    SW  t3, 793(t0)
    MOV t3, 10
    SW  t3, 819(t0)
    MOV t3, 85
    SW  t3, 830(t0)
    MOV t3, 98
    SW  t3, 833(t0)
    MOV t3, 12
    SW  t3, 846(t0)
    MOV t3, 77
    SW  t3, 855(t0)
    MOV t3, 72
    SW  t3, 866(t0)
    MOV t3, 71
    SW  t3, 867(t0)
    MOV t3, 64
    SW  t3, 894(t0)
    MOV t3, 5
    SW  t3, 909(t0)
    MOV t3, 69
    SW  t3, 928(t0)
    MOV t3, 84
    SW  t3, 937(t0)
    MOV t3, 18
    SW  t3, 939(t0)
    MOV t3, 13
    SW  t3, 967(t0)
    MOV t3, 66
    SW  t3, 971(t0)
    MOV t3, 24
    SW  t3, 973(t0)
    MOV t3, 38
    SW  t3, 978(t0)
    MOV t3, 13
    SW  t3, 981(t0)

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
