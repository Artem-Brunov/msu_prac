A = list(eval(input()))

B = []
B.append(A[0])
B.append(A[1])
for i in range(2, len(A)):
	B.append(min(B[i-1], B[i-2]) + A[i])

print(B[len(B) - 1])

