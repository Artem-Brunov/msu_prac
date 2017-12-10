class A():
	def __init__(self, a):
		self.a = a
	def __add__(self, other):
		return type(self)(self.a + other.a)
	def __radd__(self, other):
		return type(self)(self.a + other.a)
	def __str__(self):
		return "/{}/".format(self.a)
class B():
	def __init__(self, a):
		self.a = a
	def __mul__(self, other):
		return type(self)(self.a * other.a)
	def __rmul__(self, other):
		return type(self)(self.a * other.a)
	def __str__(self):
		return "|{}|".format(self.a)
class C(B, A):
	pass
