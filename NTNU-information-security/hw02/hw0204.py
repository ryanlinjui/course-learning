# https://www.geeksforgeeks.org/multiplicative-inverse-under-modulo-m/
# https://planetcalc.com/3311/

from math import gcd

def mod_inverse(A, M):

	g = gcd(A, M)

	if (g != 1):
		print("Inverse doesn't exist")

	else:
		print("Modular multiplicative inverse:", (A**(M-2)) % M)


if __name__ == "__main__":
	
	A = int(input("Enter A: "))
	M = int(input("Enter Prime number M: "))

	mod_inverse(A, M)