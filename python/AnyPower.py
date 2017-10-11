a = int(input())
i = 2
j = 2
flag = 0
ansver = "NO"
while 1:
	if flag == 1:
		break
	j = 2
	while 1:
		b = i**j
		if b == a:
			ansver = "YES"
			flag = 1
			break
		if b > a:
			break
		j+=1
	
	i+=1
	if i > a/2:
		break
		
print(ansver)
