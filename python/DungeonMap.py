Tunnels = {}
From = input()
while " " in From:
	From, To = From.split()
	Tunnels.setdefault(From,set()).add(To)
	Tunnels.setdefault(To,set()).add(From)
	From = input()
To = input()
Res, Plan = set(), {From}
while Plan:
	New = set()
	for e in Plan:
		New |= Tunnels[e]
	Res |= Plan
	Plan = New - Res
print("YES" if To in Res else "NO") 
