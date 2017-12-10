A = eval(input())
count = 0
B = dir(A)
for i in B:
	if int == type(eval("A."+i)):
		count+=1
print(count)
