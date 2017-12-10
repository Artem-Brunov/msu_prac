class Delay:
	def __init__(self, value):
		self.slot = value
	def delay(self,new):
		slot_2 = self.slot
		self.slot = new
		return slot_2
		
