# Test EX-EX Forwarding
MOV t0, 10
ADD t1, t0, t0  # t1 = 20
ADD t2, t1, t0  # Forwarding t1 from EX stage. t2 = 20 + 10 = 30
HALT
