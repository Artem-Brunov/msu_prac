import math
class Triangle:
	def __init__(self, a, b, c):
		self.a = a
		self.b = b
		self.c = c
	def __len__(self):
		maxi = max(self.a, self.b, self.c)
		if(self.a < 0 or self.b < 0 or self.c < 0 or self.a+self.b < maxi or self.a+self.c < maxi or self.c+self.b < maxi):
			return 0
		else:
			return 1
	def __abs__(self):
		if len(self) > 0:
			p = (self.a + self.b + self.c)/2
			return math.sqrt(p*(p-self.a)*(p-self.b)*(p-self.c))
		else:
			return 0
	def __lt__(self, other):
		return abs(self) < abs(other)
		
	def __le__(self, other):
		return abs(self) <= abs(other)
	def __eq__(self, other):
		if sorted([self.a, self.b, self.c]) == sorted([other.a, other.b, other.c]):
			return True
		else:
			return False
	def __ne__(self, other):
		if len(self) > 0 and len(other) > 0:
			if self.a == other.a:
				if self.b == other.b:
					if self.c == other.c:
						return False
			elif self.a == other.b:
				if self.b == other.c:
					if self.c == other.a:
						return False
			elif self.a == other.c:
				if self.b == other.a:
					if self.c == other.b:
						return False
			else:
				return True
		else:
			return False

	def __gt__(self, other):
		return abs(self) > abs(other)
	def __ge__(self, other):
		return abs(self) >= abs(other)
	def __str__(self):
		return "{}:{}:{}".format("%.1f" % self.a, "%.1f" % self.b, "%.1f" % self.c)

