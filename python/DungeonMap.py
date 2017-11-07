ansver = "NO"
C = []
i = 0
while 1:
	A = input()
	if " " in A:
		C.append(A)
	else:
		ansver_1 = A
		ansver_2 = input()
		break
while i < len(c):
	if ansver_1 in C[i]:
		ansver = "YES"
	i+=1
print(ansver)
