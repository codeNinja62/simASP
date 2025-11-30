# Test Branch Prediction (Taken)
MOV t0, 5
MOV t1, 5
BEQ t0, t1, target # Should be taken
MOV t2, 999        # Should be skipped
HALT
target:
MOV t2, 777        # Correct path
HALT
