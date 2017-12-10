class Stroka(str):
	def __neg__(self):
		return self.reverse()
	def __mul__(self, other):
		A = Stroka()
		if type(other) == type(1):
			return super().__mul__(other)
		for i in self:
			for j in other:
				A += i+j
		return Stroka(A)
	def __pow__(self, other):
		A = self
		if other == 0:
			return Stroka()
		for i in range(1, other):	
			A *= self
		return A 
