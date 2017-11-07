A = input()
B = input()
i = 0
while i < len(A):
	if len(B) > len(A):
		i = len(A)
		j = 0
		break
	if A[i] == B[0] or B[0] == '@' and i < len(A) - 1:
		i+=1
		j = 1
		while j < len(B):
			if A[i] == B[j]:
				i+=1
				j+=1
			elif B[j] == '@':
				i+=1
				j+=1
			else:
				break
		if j == len(B):
			print(i-len(B))
			break
	i+=1	
if i == len(A) and i != j:
	print(-1)	
