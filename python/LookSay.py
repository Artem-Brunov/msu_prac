N = eval(input())
def Colculator(A):
	j = 0
	i = 0
	c = []
	while len(A) > i:
		d = A[i]
		while A[i] == d:
			i+=1
			j+=1
			if len(A) <= i:
				break
		c.append(j)
		c.append(d)
		j = 0
	return c
	
def Generator():	
	A = [1]
	while 1:
		A = Colculator(A)
		yield A
j = 1
flag = 0
for i in Generator():
	p = 0
	if N == 0:
		print(1)
		break
	while p < len(i):
		if j == N:
			print(i[p])
			flag = 1
			break
		j+=1
		p+=1
	if flag == 1:
		break
