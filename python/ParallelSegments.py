
x1,y1,x2,y2,x3,y3,x4,y4 = eval(input())
ansver = "NO"


n1 = -(y2 - y1)
n2 = x2 - x1
n3 = -(y4 - y3)
n4 = x4 - x3

if n1*n4 == n2*n3:
	ansver = "YES"

print(ansver)
