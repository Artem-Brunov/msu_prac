A = str(input())
A = A.lower()
A = A.split(" ")
C = []
maxi = 0
for i in A:
	if i in C:
		continue
	C.append(i)
	if A.count(i) > maxi:
		maxi = A.count(i)
	C.append(A.count(i))
ansver = C.count(maxi)
print(ansver)

