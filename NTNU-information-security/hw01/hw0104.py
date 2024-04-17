# Convert the plaintext "I love cryptography." to binary ASCII
original_message = "I love cryptography."
binary_original_message = ''.join(format(ord(c), '08b') for c in original_message)

# Convert the ciphertext to binary
ciphertext_hex = "49913FF7731C1E74510611018BE35110495CCAA7"
binary_ciphertext = bin(int(ciphertext_hex, 16))[2:].zfill(len(ciphertext_hex) * 4)

# XOR the binary original message with the binary ciphertext to find the key stream
key_stream = ''.join(str(int(a) ^ int(b)) for a, b in zip(binary_original_message, binary_ciphertext))

print(binary_original_message, binary_ciphertext, key_stream, sep='\n=====================\n')

# Convert the new plaintext "I hate cryptography." to binary ASCII
new_message = "I hate cryptography."
binary_new_message = ''.join(format(ord(c), '08b') for c in new_message)

# XOR the binary new message with the key stream to find the new ciphertext
binary_new_ciphertext = ''.join(str(int(a) ^ int(b)) for a, b in zip(binary_new_message, key_stream))

# Convert the binary new ciphertext to hexadecimal
new_ciphertext_hex = '%0*X' % ((len(binary_new_ciphertext) + 3) // 4, int(binary_new_ciphertext, 2))

print(binary_new_message, binary_new_ciphertext, new_ciphertext_hex, sep='\n=====================\n')
