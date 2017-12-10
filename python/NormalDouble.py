class Normal:
	def __init__(self, start):
		self.value = start
	def swap(self, other):
		self.value, other.value = other.value, self.value
	def what(self):
		return self.value
class Double:
	def __init__(self, start):
		self.value = start*2
	def swap(self, other):
		self.value, other.value = other.value*2, self.value*2
	def what(self):
		return self.value * 2
