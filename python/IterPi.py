import math

E = eval(input())
E = E/2
def Generator():
	_pi = 0
	k = -1
	j = 1
	while 1:
		_pi += (4/(k+2)) * j
		k+=2
		if j == 1:
			j = -1
		else:
			j = 1
		yield _pi

_pi = Generator()
j = 1
for i in _pi:
	if  math.pi - E < i < math.pi + E:
		break
	j+=1

print(j)
