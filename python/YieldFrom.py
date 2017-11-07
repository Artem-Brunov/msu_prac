A = eval(input())
k = eval(input())
def divadd(s, d, m, n):
	prev, curr = None, s
	while prev!=curr:
		yield curr
		prev, curr = curr, (curr+n) if curr%d else (curr//d+m)
def catseq(A):
	for four in A:
		yield from divadd(*four)

for i,e in enumerate(catseq(A)):
	if i == k:
		print(e)
		break
else:
	print("NO")
	
