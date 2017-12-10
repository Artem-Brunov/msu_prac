import math
A = eval(input())
A = set(A)
M = max(A)
ansver = 0
for i in range(1, int(math.sqrt(M))+1):
	for j in range(i, int(math.sqrt(M - i*i))+1):
		for k in range(j, int(math.sqrt(M - i*i - j*j))+1):
			summ = i*i + j*j + k*k
			if summ in A:
				ansver+=1
				A.remove(summ)
print(ansver)
