A = eval(input())
ansver = 0
for i in A:
	j = 1
	qq = 0
	flag = 0
	while j < 183:
		p = 1
		if flag == 1:
			break
		while p < 183:
			z = 1
			if flag == 1:
				break
			while z < 183:
				qq = j*j + p*p + z*z
				print(j,"j",p,"p",z,"z")
				print(qq, "qq", i, "i")
				if qq > i:
					flag = 1
					break
				if i == qq:
					ansver+=1
					flag = 1
					break
				z+=1
			p+=1
		j+=1
print(ansver)
