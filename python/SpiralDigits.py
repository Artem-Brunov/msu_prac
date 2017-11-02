M,N = eval(input())

def right(A,i,j,p,q,n):
	s = 0
	while s < q:
		A[i][j] = p
		p+=1
		j+=1
		s+=1
		n+=1
		if p == 10:
			p = 0
	return A, p, n, i+1, j-1

def down(A,i,j,p,b,n):
	s = 0
	while s < b:
		A[i][j] = p
		p+=1
		s+=1
		i+=1
		n+=1
		if p == 10:
			p = 0
	return A, p, n, i-1, j-1

def left(A,i,j,p,q,n):
	s = 0
	while s < q:
		A[i][j] = p
		p+=1
		j-=1
		s+=1
		n+=1
		if p == 10:
			p = 0
	return A, p, n, i-1, j+1

def up(A,i,j,p,b,n):
	s = 0
	while s < b:
		A[i][j] = p
		p+=1
		i-=1
		s+=1
		n+=1
		if p == 10:
			p = 0
	return A, p, n, i + 1, j+1

A = [[0] * M for i in range(N)]

n = 0
j = 0
i = 0
p = 0
q = M
b = N 
while 1:
	A,p,n,i,j = right(A,i,j,p,q,n)
	b-=1
	if n == N*M:
		break
	A,p,n,i,j = down(A,i,j,p,b,n)
	q-=1
	if n == M*N:
		break
	A,p,n,i,j = left(A,i,j,p,q,n)
	b-=1
	if n == M*N:
		break
	A,p,n,i,j = up(A,i,j,p,b,n)
	q-=1
	if n == N*M:
		break
i = 0
while i < N:
	j = 0
	while j < M:
		print(A[i][j], end = " ")
		j+=1
	print("")
	i+=1
