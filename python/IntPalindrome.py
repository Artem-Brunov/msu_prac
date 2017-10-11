
a = int(input())
b = a
i = 0
j = 1
ansver = 'YES'
while b:
	b = b//10
	i+=1

if i % 2 == 0:
	j = i//2
else:
	j = i//2 + 1
while j:
	b = a - a//10*10
	
	c = a//10**(i-1)
	if b != c:
		ansver = 'NO'
		break
	a = a - c*10**(i-1)
	a = a//10
	i-=2
	j-=1

print(ansver)
