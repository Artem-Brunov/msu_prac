A = list(eval(input()))
M, N = eval(input())
B = []
j = 0
for i in A:
	if j%M != 0 and i%N != 0:
		B.append(i)
	j+=1
print(B)
