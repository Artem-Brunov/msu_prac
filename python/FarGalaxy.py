def nachalo():
	C = []
	while 1:
		A = input()
		if not " " in A:
			break
		A = A.split(" ")
		C.append((eval(A[0]), eval(A[1]), eval(A[2]), A[3]))
	return C
def chislo(C):
	maxm = 0
	ansver = [0,0]
	for i in range(0, len(C) - 1):
		for j in range(i+1,len(C)):
			B = abs(C[j][0]-C[i][0]) + abs(C[j][1]-C[i][1]) + abs(C[j][2]-C[i][2])
			if maxm <= B:
				ansver[0] = C[i][3]
				ansver[1] = C[j][3]
				maxm = B
	return ansver
C = []
C = nachalo()
ansver = chislo(C)
ansver.sort()
print(ansver[0], ansver[1])
