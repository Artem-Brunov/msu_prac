A = tuple(eval(input()))

B = len(A) - 1

C = []	
j = 0
i = 0
while i <= B:
	if B % 2 == 0:
		if B - i*2 >= 0:
			C.append(A[B - i*2])
		else:
			C.append(A[j*2 + 1])
			j+=1
	else:
		if B - 1 - i*2 >= 0:
			C.append(A[B-1-i*2])

		else:
			C.append(A[j*2 + 1])
			j+=1
	i+=1
C = tuple(C) 
print(C)
