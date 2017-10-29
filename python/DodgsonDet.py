def WithoutZero(A, D):
	i = 1
	while A[0][0] == 0:
		A[0],A[i] = A[i],A[0]
		D *= -1
		i+=1
	return A, D

def Det(A, D):
	i = 0
	hight = len(A) - 1
	B = [[0] * hight for i in range(hight)]
	A, D = WithoutZero(A, D)
	while i < hight:
		j = 0
		while j < hight:
			B[i][j] = A[0][0] * A[i+1][j+1] - A[i+1][0] * A[0][j+1]
			j+=1
		i+=1
	D *= A[0][0] ** (hight - 1)
	print(B)
	A = B.copy()
	return A, D
A = []
A.append(list(eval(input())))
for i in range(len(A[0]) - 1):
	A.append(list(eval(input())))
D = 1
while len(A) != 1:
	A, D = Det(A, D)
	print(D)
ansver = A[0][0] // D
print(ansver)
