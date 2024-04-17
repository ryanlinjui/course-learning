from Crypto.Cipher import AES
from Crypto.Util.Padding import pad

def find_key(plaintext, ciphertext, IV):
    data = bytearray(plaintext, encoding="utf-8")
    ciphertext = bytearray.fromhex(ciphertext)
    iv = bytearray.fromhex(IV)

    with open("./words.txt") as f:
        keys = f.readlines()

    for k in keys:
        k = k.rstrip('\n')
        if len(k) <= 16:
            key = k + '#' * (16 - len(k))
            cipher = AES.new(key=bytearray(key,encoding='utf-8'), mode=AES.MODE_CBC, iv=iv)
            guess = cipher.encrypt(pad(data, 16))
            if guess == ciphertext:
                return key.rstrip('#')

    print("Key not found")

if __name__ == "__main__":
    plaintext = "This is a top secret."
    ciphertext = "764aa26b55a4da654df6b19e4bce00f4ed05e09346fb0e762583cb7da2ac93a2"
    IV = "aabbccddeeff00998877665544332211"

    key = find_key(plaintext, ciphertext, IV)
    
    if key is not None:
        print("Found key: ", key)
   