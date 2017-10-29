M,N = eval(input())

def Colculate(M,N):
	A = [[0] * M for i in range(N)]
		 
			
	return A
def Generator(M,N):
	i = 0
	A = Colculate(M,N)
	while i < M*N:
		yield A[i]
		i+=1
d = 1
for i in Generator(M,N):
	print(i, end = ' ')
	if d == M:
		print('')
		d = 0
	d+=1
