class Unary:
	def __init__(self, string):
		self.count = len(string)
		self.counter = 0
	def __len__(self):
		return self.count
	def __or__(self, other):
		return Unary("|"*(self.count + other.count))
	def __invert__(self):
		self.count = self.count//2
		return self
	def __next__(self):
		if self.counter == self.count:
			self.counter = 0
			raise StopIteration
		self.counter+=1
		return Unary("|")
	def __iter__(self):
		return self
	def __pos__(self):
		self.count+=1
		return self		
	def __str__(self):
		A = ""
		for i in range(0, self.count):
			A += "|"
		return A




