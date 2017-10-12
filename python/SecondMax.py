A = list(eval(input()))

i = 1
max = A[0]

while i < len(A):
	if A[i] > max:
		max = A[i]
	i+=1
i = 0
j = A.count(max)
while i < j:
	A.remove(max)
	i+=1

i = 1
if len(A) == 0:
	print('NO')
else:
	max = A[0]
	while i < len(A):
		if A[i] > max:
			max = A[i]
		i+=1

	print(max)
