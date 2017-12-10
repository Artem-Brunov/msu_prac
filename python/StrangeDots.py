class Dots:
	def __init__(self, a, b):
		self.a = a
		self.b = b
	def __getitem__(self, item):
		if type(item) == type(1):
			return 
		elif type(item) == None:
			return "w"
		else:
			return "e"
		
a = Dots(0,40)
print(*a[5])
print(a[0:5])
print(a[2:5])
print(a[4:5])
print(a[7:5])
print(a[-7:5])
print(*a[1:3:5])
print(*a[:3:5])
print(*a[2::5])
print(*a[::5])
print(*a[-2:6:5])
