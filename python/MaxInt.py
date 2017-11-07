C = []
B = []
while 1:
	A = input()
	if len(A) == 0:
		break
	A = A.split(' ')
	C = C + A
for i in C:
	if i[0].isdigit():
		if i.isdigit():
			B.append(i)
	else:
		if len(i) > 1:
			j = 1
			b = 0
			while j < len(i):
				if i[j].isdigit():
					b+=1
				j+=1
			if b == len(i) - 1:
				B.append(i)
			
print(max(B,key = int))
