import math
x, y, r = eval(input())
ansver = 'YES'

while 1:
	x1, y1 = eval(input())
	if not x1 and not y1:
		break	
	if math.sqrt((x - x1)**2 + (y - y1)**2) > r:
		ansver = 'NO'	
print (ansver)
