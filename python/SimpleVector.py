class Vector:
	def __init__(self, X, Y, Z):
		self.x = float(X)
		self.y = float(Y)
		self.z = float(Z)
	
	def __add__(self, other):
		return Vector(self.x + other.x, self.y + other.y, self.z + other.z)
	
	def __sub__(self, other):
		return Vector(self.x - other.x, self.y - other.y, self.z - other.z)
	
	def __mul__(self, other):
		return Vector(self.x * other, self.y * other, self.z * other)
	
	def __rmul__(self, other):
		return Vector(self.x * other, self.y * other, self.z * other)
	
	def __truediv__(self, other):
		return Vector(self.x / other, self.y / other, self.z / other)

	def __matmul__(self, other):
		return self.x * other.x + self.y * other.y + self.z * other.z

	def __str__(self):
		return "{}:{}:{}".format("%.2f" % self.x, "%.2f" % self.y, "%.2f" % self.z)

