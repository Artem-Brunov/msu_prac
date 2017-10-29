A = list(eval(input()))
N = eval(input())

def Generator(A):
	j = 0
	while j < len(A):
		for i in A:
			_max = A[j]
			if i <= _max: 
				yield i
		j+=1

number = Generator(A);
j = 0
ansver = "NO"

for i in number:
	if j == N:
		ansver = i;
		break;	
	j+=1

print(ansver)
