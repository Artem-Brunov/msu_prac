class Sem():
	def __init__(self, a):
		self.a = a
	def lock(self):

a, b = Sem("A"), Sem("B")
print("Locked:",a.lock) # A взводит опущенный семафор
print("Locked:",a.lock) # Семафор взведён A
print("Locked:",b.lock) # Семафор взведён A
del(b.lock)             # B пытается сбросить семафор
print("Locked:",b.lock) # Семафор взведён A
print("Locked:",a.lock) # Семафор взведён A
del(a.lock)             # А сбрасывает семафор
print("Locked:",b.lock) # B взводит опущенный семафор
print("Locked:",a.lock) # Семафор взведён B

