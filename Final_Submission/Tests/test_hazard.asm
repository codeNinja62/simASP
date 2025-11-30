# Test Load-Use Hazard
MOV t0, 10
MOV t3, 99
SW t3, 0(t0)    # Mem[10] = 99
LW t1, 0(t0)    # Load 99 into t1
ADD t2, t1, t0  # Hazard! Uses t1 immediately. t2 = 99 + 10 = 109
HALT
