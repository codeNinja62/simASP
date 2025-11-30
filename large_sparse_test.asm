# Large Sparse Matrix Test (512x512)
# Size: 262144 elements
# Strategy: Initialize random non-zeros, then scan with LNZ

INIT:
    MOV t0, 0       ; Base Address
    # Initializing 50 random non-zero elements
    MOV t3, 48
    SW  t3, 13563(t0)
    MOV t3, 69
    SW  t3, 30185(t0)
    MOV t3, 9
    SW  t3, 34867(t0)
    MOV t3, 18
    SW  t3, 34904(t0)
    MOV t3, 64
    SW  t3, 38060(t0)
    MOV t3, 99
    SW  t3, 41902(t0)
    MOV t3, 63
    SW  t3, 61350(t0)
    MOV t3, 66
    SW  t3, 72167(t0)
    MOV t3, 8
    SW  t3, 78115(t0)
    MOV t3, 16
    SW  t3, 78342(t0)
    MOV t3, 37
    SW  t3, 84419(t0)
    MOV t3, 85
    SW  t3, 92841(t0)
    MOV t3, 33
    SW  t3, 103246(t0)
    MOV t3, 91
    SW  t3, 113426(t0)
    MOV t3, 21
    SW  t3, 113559(t0)
    MOV t3, 63
    SW  t3, 115578(t0)
    MOV t3, 42
    SW  t3, 120513(t0)
    MOV t3, 17
    SW  t3, 121720(t0)
    MOV t3, 38
    SW  t3, 127956(t0)
    MOV t3, 19
    SW  t3, 137103(t0)
    MOV t3, 87
    SW  t3, 137631(t0)
    MOV t3, 9
    SW  t3, 137699(t0)
    MOV t3, 65
    SW  t3, 147339(t0)
    MOV t3, 14
    SW  t3, 152247(t0)
    MOV t3, 53
    SW  t3, 158594(t0)
    MOV t3, 53
    SW  t3, 160596(t0)
    MOV t3, 12
    SW  t3, 161232(t0)
    MOV t3, 29
    SW  t3, 163684(t0)
    MOV t3, 61
    SW  t3, 175140(t0)
    MOV t3, 16
    SW  t3, 187303(t0)
    MOV t3, 70
    SW  t3, 188876(t0)
    MOV t3, 88
    SW  t3, 193896(t0)
    MOV t3, 54
    SW  t3, 204606(t0)
    MOV t3, 68
    SW  t3, 205036(t0)
    MOV t3, 78
    SW  t3, 205194(t0)
    MOV t3, 10
    SW  t3, 207782(t0)
    MOV t3, 68
    SW  t3, 211654(t0)
    MOV t3, 45
    SW  t3, 216689(t0)
    MOV t3, 72
    SW  t3, 219203(t0)
    MOV t3, 61
    SW  t3, 222335(t0)
    MOV t3, 63
    SW  t3, 224097(t0)
    MOV t3, 90
    SW  t3, 226488(t0)
    MOV t3, 1
    SW  t3, 230886(t0)
    MOV t3, 95
    SW  t3, 240078(t0)
    MOV t3, 27
    SW  t3, 242920(t0)
    MOV t3, 78
    SW  t3, 244554(t0)
    MOV t3, 48
    SW  t3, 248663(t0)
    MOV t3, 32
    SW  t3, 253040(t0)
    MOV t3, 19
    SW  t3, 255014(t0)
    MOV t3, 87
    SW  t3, 255955(t0)
    # Sentinel at end
    MOV t3, -1
    SW  t3, 262144(t0)

PROCESS:
    MOV t0, 0       ; Reset Pointer
    MOV t1, 262144     ; End Index (approx)
    MOV t6, 0                 ; Accumulator
    MOV s1, -1    ; Sentinel Value

LOOP:
    LNZ t3, 0(t0)             ; Load Non-Zero
    BEQ t3, s1, DONE          ; If Sentinel, Exit
    ADD t6, t6, t3            ; Sum += Val
    JMP LOOP

DONE:
    HALT
