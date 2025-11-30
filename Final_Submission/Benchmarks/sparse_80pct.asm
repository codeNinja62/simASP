# Sparse Matrix Benchmark
# Size: 1000 elements
# Sparsity: 80% zeros (800 zeros, 200 non-zeros)
# Expected Sum: 9682

INIT:
    MOV t0, 0       ; Base Address

    # Initializing 200 non-zero elements
    MOV t3, 64
    SW  t3, 4(t0)
    MOV t3, 36
    SW  t3, 11(t0)
    MOV t3, 28
    SW  t3, 12(t0)
    MOV t3, 78
    SW  t3, 23(t0)
    MOV t3, 54
    SW  t3, 41(t0)
    MOV t3, 26
    SW  t3, 58(t0)
    MOV t3, 7
    SW  t3, 60(t0)
    MOV t3, 42
    SW  t3, 76(t0)
    MOV t3, 21
    SW  t3, 78(t0)
    MOV t3, 14
    SW  t3, 82(t0)
    MOV t3, 7
    SW  t3, 121(t0)
    MOV t3, 10
    SW  t3, 122(t0)
    MOV t3, 99
    SW  t3, 128(t0)
    MOV t3, 42
    SW  t3, 134(t0)
    MOV t3, 24
    SW  t3, 140(t0)
    MOV t3, 10
    SW  t3, 143(t0)
    MOV t3, 27
    SW  t3, 151(t0)
    MOV t3, 66
    SW  t3, 154(t0)
    MOV t3, 93
    SW  t3, 155(t0)
    MOV t3, 75
    SW  t3, 157(t0)
    MOV t3, 6
    SW  t3, 164(t0)
    MOV t3, 54
    SW  t3, 172(t0)
    MOV t3, 28
    SW  t3, 173(t0)
    MOV t3, 14
    SW  t3, 174(t0)
    MOV t3, 88
    SW  t3, 183(t0)
    MOV t3, 18
    SW  t3, 185(t0)
    MOV t3, 49
    SW  t3, 194(t0)
    MOV t3, 18
    SW  t3, 197(t0)
    MOV t3, 44
    SW  t3, 201(t0)
    MOV t3, 71
    SW  t3, 205(t0)
    MOV t3, 83
    SW  t3, 206(t0)
    MOV t3, 9
    SW  t3, 218(t0)
    MOV t3, 20
    SW  t3, 224(t0)
    MOV t3, 29
    SW  t3, 226(t0)
    MOV t3, 37
    SW  t3, 228(t0)
    MOV t3, 58
    SW  t3, 235(t0)
    MOV t3, 2
    SW  t3, 236(t0)
    MOV t3, 26
    SW  t3, 245(t0)
    MOV t3, 61
    SW  t3, 247(t0)
    MOV t3, 90
    SW  t3, 249(t0)
    MOV t3, 58
    SW  t3, 253(t0)
    MOV t3, 52
    SW  t3, 275(t0)
    MOV t3, 60
    SW  t3, 282(t0)
    MOV t3, 36
    SW  t3, 285(t0)
    MOV t3, 53
    SW  t3, 293(t0)
    MOV t3, 28
    SW  t3, 295(t0)
    MOV t3, 23
    SW  t3, 301(t0)
    MOV t3, 2
    SW  t3, 305(t0)
    MOV t3, 99
    SW  t3, 306(t0)
    MOV t3, 19
    SW  t3, 307(t0)
    MOV t3, 29
    SW  t3, 313(t0)
    MOV t3, 25
    SW  t3, 333(t0)
    MOV t3, 68
    SW  t3, 344(t0)
    MOV t3, 91
    SW  t3, 353(t0)
    MOV t3, 74
    SW  t3, 354(t0)
    MOV t3, 58
    SW  t3, 359(t0)
    MOV t3, 86
    SW  t3, 361(t0)
    MOV t3, 32
    SW  t3, 372(t0)
    MOV t3, 95
    SW  t3, 383(t0)
    MOV t3, 50
    SW  t3, 384(t0)
    MOV t3, 93
    SW  t3, 388(t0)
    MOV t3, 44
    SW  t3, 395(t0)
    MOV t3, 95
    SW  t3, 399(t0)
    MOV t3, 43
    SW  t3, 407(t0)
    MOV t3, 73
    SW  t3, 410(t0)
    MOV t3, 99
    SW  t3, 413(t0)
    MOV t3, 83
    SW  t3, 414(t0)
    MOV t3, 28
    SW  t3, 419(t0)
    MOV t3, 6
    SW  t3, 420(t0)
    MOV t3, 30
    SW  t3, 421(t0)
    MOV t3, 37
    SW  t3, 423(t0)
    MOV t3, 36
    SW  t3, 426(t0)
    MOV t3, 85
    SW  t3, 427(t0)
    MOV t3, 58
    SW  t3, 428(t0)
    MOV t3, 33
    SW  t3, 429(t0)
    MOV t3, 86
    SW  t3, 437(t0)
    MOV t3, 25
    SW  t3, 447(t0)
    MOV t3, 23
    SW  t3, 450(t0)
    MOV t3, 37
    SW  t3, 454(t0)
    MOV t3, 37
    SW  t3, 465(t0)
    MOV t3, 2
    SW  t3, 470(t0)
    MOV t3, 46
    SW  t3, 473(t0)
    MOV t3, 33
    SW  t3, 475(t0)
    MOV t3, 72
    SW  t3, 477(t0)
    MOV t3, 52
    SW  t3, 479(t0)
    MOV t3, 28
    SW  t3, 482(t0)
    MOV t3, 37
    SW  t3, 483(t0)
    MOV t3, 25
    SW  t3, 488(t0)
    MOV t3, 98
    SW  t3, 493(t0)
    MOV t3, 23
    SW  t3, 499(t0)
    MOV t3, 4
    SW  t3, 501(t0)
    MOV t3, 35
    SW  t3, 504(t0)
    MOV t3, 32
    SW  t3, 507(t0)
    MOV t3, 99
    SW  t3, 512(t0)
    MOV t3, 94
    SW  t3, 529(t0)
    MOV t3, 7
    SW  t3, 541(t0)
    MOV t3, 93
    SW  t3, 550(t0)
    MOV t3, 36
    SW  t3, 551(t0)
    MOV t3, 93
    SW  t3, 556(t0)
    MOV t3, 99
    SW  t3, 560(t0)
    MOV t3, 52
    SW  t3, 562(t0)
    MOV t3, 89
    SW  t3, 566(t0)
    MOV t3, 55
    SW  t3, 568(t0)
    MOV t3, 92
    SW  t3, 570(t0)
    MOV t3, 45
    SW  t3, 571(t0)
    MOV t3, 13
    SW  t3, 577(t0)
    MOV t3, 46
    SW  t3, 580(t0)
    MOV t3, 45
    SW  t3, 581(t0)
    MOV t3, 50
    SW  t3, 587(t0)
    MOV t3, 75
    SW  t3, 588(t0)
    MOV t3, 44
    SW  t3, 591(t0)
    MOV t3, 74
    SW  t3, 598(t0)
    MOV t3, 51
    SW  t3, 599(t0)
    MOV t3, 20
    SW  t3, 604(t0)
    MOV t3, 85
    SW  t3, 605(t0)
    MOV t3, 37
    SW  t3, 607(t0)
    MOV t3, 61
    SW  t3, 610(t0)
    MOV t3, 88
    SW  t3, 625(t0)
    MOV t3, 52
    SW  t3, 627(t0)
    MOV t3, 54
    SW  t3, 630(t0)
    MOV t3, 18
    SW  t3, 631(t0)
    MOV t3, 31
    SW  t3, 636(t0)
    MOV t3, 68
    SW  t3, 642(t0)
    MOV t3, 18
    SW  t3, 646(t0)
    MOV t3, 28
    SW  t3, 651(t0)
    MOV t3, 91
    SW  t3, 658(t0)
    MOV t3, 44
    SW  t3, 660(t0)
    MOV t3, 49
    SW  t3, 661(t0)
    MOV t3, 15
    SW  t3, 663(t0)
    MOV t3, 27
    SW  t3, 664(t0)
    MOV t3, 38
    SW  t3, 665(t0)
    MOV t3, 87
    SW  t3, 675(t0)
    MOV t3, 35
    SW  t3, 687(t0)
    MOV t3, 21
    SW  t3, 688(t0)
    MOV t3, 32
    SW  t3, 689(t0)
    MOV t3, 95
    SW  t3, 693(t0)
    MOV t3, 56
    SW  t3, 701(t0)
    MOV t3, 78
    SW  t3, 703(t0)
    MOV t3, 72
    SW  t3, 706(t0)
    MOV t3, 78
    SW  t3, 709(t0)
    MOV t3, 58
    SW  t3, 711(t0)
    MOV t3, 35
    SW  t3, 716(t0)
    MOV t3, 14
    SW  t3, 717(t0)
    MOV t3, 88
    SW  t3, 724(t0)
    MOV t3, 82
    SW  t3, 726(t0)
    MOV t3, 47
    SW  t3, 730(t0)
    MOV t3, 35
    SW  t3, 734(t0)
    MOV t3, 21
    SW  t3, 738(t0)
    MOV t3, 40
    SW  t3, 743(t0)
    MOV t3, 29
    SW  t3, 747(t0)
    MOV t3, 58
    SW  t3, 749(t0)
    MOV t3, 72
    SW  t3, 752(t0)
    MOV t3, 24
    SW  t3, 761(t0)
    MOV t3, 4
    SW  t3, 776(t0)
    MOV t3, 98
    SW  t3, 777(t0)
    MOV t3, 84
    SW  t3, 778(t0)
    MOV t3, 24
    SW  t3, 781(t0)
    MOV t3, 1
    SW  t3, 783(t0)
    MOV t3, 25
    SW  t3, 802(t0)
    MOV t3, 84
    SW  t3, 812(t0)
    MOV t3, 81
    SW  t3, 821(t0)
    MOV t3, 39
    SW  t3, 822(t0)
    MOV t3, 17
    SW  t3, 824(t0)
    MOV t3, 8
    SW  t3, 830(t0)
    MOV t3, 59
    SW  t3, 836(t0)
    MOV t3, 92
    SW  t3, 837(t0)
    MOV t3, 92
    SW  t3, 842(t0)
    MOV t3, 100
    SW  t3, 853(t0)
    MOV t3, 70
    SW  t3, 855(t0)
    MOV t3, 87
    SW  t3, 857(t0)
    MOV t3, 14
    SW  t3, 860(t0)
    MOV t3, 97
    SW  t3, 863(t0)
    MOV t3, 49
    SW  t3, 864(t0)
    MOV t3, 52
    SW  t3, 865(t0)
    MOV t3, 81
    SW  t3, 869(t0)
    MOV t3, 37
    SW  t3, 871(t0)
    MOV t3, 84
    SW  t3, 874(t0)
    MOV t3, 31
    SW  t3, 880(t0)
    MOV t3, 16
    SW  t3, 881(t0)
    MOV t3, 17
    SW  t3, 883(t0)
    MOV t3, 33
    SW  t3, 886(t0)
    MOV t3, 62
    SW  t3, 890(t0)
    MOV t3, 63
    SW  t3, 896(t0)
    MOV t3, 4
    SW  t3, 907(t0)
    MOV t3, 11
    SW  t3, 917(t0)
    MOV t3, 94
    SW  t3, 924(t0)
    MOV t3, 5
    SW  t3, 927(t0)
    MOV t3, 68
    SW  t3, 935(t0)
    MOV t3, 5
    SW  t3, 937(t0)
    MOV t3, 54
    SW  t3, 944(t0)
    MOV t3, 52
    SW  t3, 950(t0)
    MOV t3, 23
    SW  t3, 952(t0)
    MOV t3, 21
    SW  t3, 953(t0)
    MOV t3, 18
    SW  t3, 959(t0)
    MOV t3, 14
    SW  t3, 960(t0)
    MOV t3, 42
    SW  t3, 974(t0)
    MOV t3, 87
    SW  t3, 981(t0)
    MOV t3, 74
    SW  t3, 988(t0)
    MOV t3, 14
    SW  t3, 990(t0)
    MOV t3, 58
    SW  t3, 997(t0)

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
