def xor(first, second):
    return bytearray(x^y for x, y in zip(first, second))

def decrypt(p1, c1, c2):
    p1 = bytes(p1, 'utf-8')
    c1 = bytearray.fromhex(c1)  # Convert c1 to a bytearray
    c2 = bytearray.fromhex(c2)
    tmp = xor(p1, c1)
    p2 = xor(tmp, c2)
    return p2

if __name__ == "__main__":
    p1 = "This is a known message!"
    c1 = "a469b1c502c1cab966965e50425438e1bb1b5f9037a4c159"
    c2 = "bf73bcd3509299d566c35b5d450337e1bb175f903fafc159"
    p2 = decrypt(p1, c1, c2)

    print(p2.hex())
    print(p2.decode())