import random
def generate_n(sequence):
    n = random.randint(
        sum(sequence)+1,
        sum(sequence) + 10
    )
    return n

def generate_w(n):
    import math

    for w in range(2, n):
        if math.gcd(w, n) == 1:
            return w

    raise ValueError("Could not find a valid w.")

import random

def generate_superincreasing_sequence(size):
    sequence = []
    running_sum = 0

    for _ in range(size):
        value = random.randint(
            running_sum + 1,
            running_sum + 10
        )

        sequence.append(value)
        running_sum += value

    return sequence

def mod_inverse(a, m):
    m0, x0, x1 = m, 0, 1
    if m == 1:
        return 0
    while a > 1:
        q = a // m
        m, a = a % m, m
        x0, x1 = x1 - q * x0, x0
    return x1 + m0 if x1 < 0 else x1

def encrypt(plaintext, sequence, H):
    binary_plaintext = ''.join(format(ord(c), '08b') for c in plaintext)  # Convert plaintext to binary
    block_size = len(sequence)  # Size of the block
    ciphertext = []
    
    # Split the binary plaintext into blocks
    for i in range(0, len(binary_plaintext), block_size):
        block = binary_plaintext[i:i+block_size]
        block = block.ljust(block_size, '0')  # Zero-padding if the last block is smaller
        
        # Encrypt the block
        sum_cipher = 0
        for j in range(block_size):
            if j < len(block):  # Check if index is valid
                sum_cipher += int(block[j]) * H[j]
        ciphertext.append(sum_cipher)
    
    return ciphertext

def decrypt(ciphertext, sequence, w_inv, n):
    decrypted_text = ''
    
    for cipher in ciphertext:
        # Multiply the ciphertext by the modular inverse of w mod n
        Ai = (cipher * w_inv) % n
        
        # Find the original bits using the superincreasing sequence
        block_bits = ['0'] * len(sequence)
        for i in range(len(sequence) - 1, -1, -1):
            if Ai >= sequence[i]:
                Ai -= sequence[i]
                block_bits[i] = '1'
        
        # Convert the bits back to characters (each block is 8 bits)
        binary_string = ''.join(block_bits)
        for j in range(0, len(binary_string), 8):
            if j + 8 <= len(binary_string):  # Ensure there is a full 8 bits to convert
                decrypted_text += chr(int(binary_string[j:j+8], 2))
    
    return decrypted_text

def process_input():
    import math
    
    test_cases = int(input("Number of test cases: "))
    index = 1
    
    for t in range(test_cases):
        print(f"Test Case {t + 1}")
        plaintext = input("Enter Plaintext: ")  # Read the plaintext
        index += 1
        sequence_size = 8
        sequence = generate_superincreasing_sequence(sequence_size)

        S_sum = sum(sequence)
        n = generate_n(sequence)
        w = generate_w(n)

        H = [(w * s) % n for s in sequence]

        print("\nPrivate key sequence:", sequence)
        print("Sequence sum:", S_sum)
        print("n:", n)
        print("w:", w)
        print("Public key:", H)

        # Encrypt the plaintext
        ciphertext = encrypt(plaintext, sequence, H)
        print("Ciphertext:", ciphertext)
        
        # Calculate w_inverse (modular inverse of w mod n)
        w_inv = mod_inverse(w, n)
        print("Modular inverse of w:", w_inv)
        
        # Decrypt the ciphertext
        decrypted_text = decrypt(ciphertext, sequence, w_inv, n)
        print("Decrypted text:", decrypted_text)
        if decrypted_text == plaintext:
            print("Verification: SUCCESS")
        else:
            print("Verification: FAILED")

if __name__ == "__main__":
    try:
        process_input()
    except FileNotFoundError:
        print("Input file not found.")
    except Exception as e:
        print(f"An error occurred: {e}")
