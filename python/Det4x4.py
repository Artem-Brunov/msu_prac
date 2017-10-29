A = eval(input());

def det(B):
	ansver = B[0] * B[4] * B[8] + B[1] * B[5] * B[6] + B[2] * B[3] * B[7] - B[2] * B[4] * B[6] - B[1] * B[3] * B[8] - B[0] * B[5] * B[7]

	return ansver

ansver = 0
B = A[0]
C = A[1] + A[2] + A[3]

ans = det(C[1:4] + C[5:8] + C[-3:])
ansver += ans * B[0]
ans = det(C[0:1] + C[2:5] + C[6:9] + C[-2:])
ansver -= ans * B[1] 
ans = det(C[0:2] + C[3:6] + C[7:10] + C[-1:])
ansver += ans * B[2]
ans = det(C[0:3] + C[4:7] + C[8:11])
ansver -= ans * B[3]

print(ansver)
