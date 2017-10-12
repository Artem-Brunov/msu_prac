A = list(eval(input()))

i = 0
sum = 0
while 1:
	if len(A) <= 2:
		sum += A[len(A) - 1]
		break;
	if len(A) == 3:
		if A[0] > A[1]:
			sum += A[1] + A[2]
			break
		else:
			sum += A[0] + A[2]
			break

	if A[i] + A[i+2] <= A[i+1]:
		sum += A[i]
		i+=1
	else:
		sum += A[i+1]
		i+=2
	if len(A) - 2 <= i:
		sum += A[len(A) - 1]
		break
print(sum)
