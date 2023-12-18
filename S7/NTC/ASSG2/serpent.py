# This code uses fixed S-boxes and doesn't implement key schedule used in actual serpent implementation

ascii = {'A': 0, 'B': 1, 'C': 2, 'D': 3, 'E': 4, 'F': 5, 'G': 6, 'H': 7, 'I': 8, 'J': 9, 'K': 10, 'L': 11, 'M': 12, 'N': 13, 'O': 14, 'P': 15, 'Q': 16, 'R': 17, 'S': 18, 'T': 19, 'U': 20, 'V': 21, 'W': 22, 'X': 23, 'Y': 24, 'Z': 25, 'a': 26, 'b': 27, 'c': 28, 'd': 29, 'e': 30, 'f': 31,
         'g': 32, 'h': 33, 'i': 34, 'j': 35, 'k': 36, 'l': 37, 'm': 38, 'n': 39, 'o': 40, 'p': 41, 'q': 42, 'r': 43, 's': 44, 't': 45, 'u': 46, 'v': 47, 'w': 48, 'x': 49, 'y': 50, 'z': 51, '1': 52, '2': 53, '3': 54, '4': 55, '5': 56, '6': 57, '7': 58, '8': 59, '9': 60, '0': 61, ' ': 62, '.': 63}

char = {0: 'A', 1: 'B', 2: 'C', 3: 'D', 4: 'E', 5: 'F', 6: 'G', 7: 'H', 8: 'I', 9: 'J', 10: 'K', 11: 'L', 12: 'M', 13: 'N', 14: 'O', 15: 'P', 16: 'Q', 17: 'R', 18: 'S', 19: 'T', 20: 'U', 21: 'V', 22: 'W', 23: 'X', 24: 'Y', 25: 'Z', 26: 'a', 27: 'b', 28: 'c', 29: 'd', 30: 'e', 31: 'f', 32: 'g', 33: 'h', 34: 'i', 35: 'j', 36: 'k', 37: 'l', 38: 'm', 39: 'n', 40: 'o', 41: 'p', 42: 'q', 43: 'r', 44: 's', 45: 't', 46: 'u', 47: 'v', 48: 'w', 49: 'x', 50: 'y', 51: 'z', 52: '1', 53: '2', 54: '3', 55: '4', 56: '5', 57:
        '6', 58: '7', 59: '8', 60: '9', 61: '0', 62: ' ', 63: '.'}

sbox = {
    "0000": ["0011", "1111", "1000", "0000", "0001", "1111", "0111", "0001"],
    "0001": ["1000", "1100", "0110", "1111", "1111", "0101", "0010", "1101"],
    "0010": ["1111", "0010", "0111", "1011", "1000", "0010", "1100", "1111"],
    "0011": ["0001", "0111", "1001", "1000", "0011", "1011", "0101", "0000"],
    "0100": ["1010", "1001", "0011", "1100", "1100", "0100", "1000", "1110"],
    "0101": ["0110", "0000", "1100", "1001", "0000", "1010", "0100", "1000"],
    "0110": ["0101", "0101", "1010", "0110", "1011", "1001", "0110", "0010"],
    "0111": ["1011", "1010", "1111", "0011", "0110", "1100", "1011", "1011"],
    "1000": ["1110", "0001", "1101", "1101", "0010", "0000", "1110", "0111"],
    "1001": ["1101", "1011", "0001", "0001", "0101", "0011", "1001", "0100"],
    "1010": ["0100", "1110", "1110", "0010", "0100", "1110", "0001", "1100"],
    "1011": ["0010", "1000", "0100", "0100", "1010", "1000", "1111", "1010"],
    "1100": ["0111", "0110", "0000", "1010", "1001", "1101", "1101", "1001"],
    "1101": ["0000", "1101", "1011", "0111", "1110", "0110", "0011", "0011"],
    "1110": ["1001", "0011", "0101", "0101", "0111", "0111", "1010", "0101"],
    "1111": ["1100", "0100", "0010", "1110", "1101", "0001", "0000", "0110"]
}

inverse_sbox = {
    "0000": ["1101", "0101", "1100", "0000", "0101", "1000", "1111", "0011"],
    "0001": ["0011", "1000", "1001", "1001", "0000", "1111", "1010", "0000"],
    "0010": ["1011", "0010", "1111", "1010", "1000", "0010", "0001", "0110"],
    "0011": ["0000", "1110", "0100", "0111", "0011", "1001", "1101", "1101"],
    "0100": ["1010", "1111", "1011", "1011", "1010", "0100", "0101", "1001"],
    "0101": ["0110", "0110", "1110", "1110", "1001", "0001", "0011", "1110"],
    "0110": ["0101", "1100", "0001", "0110", "0111", "1101", "0110", "1111"],
    "0111": ["1100", "0011", "0010", "1101", "1110", "1110", "0000", "1000"],
    "1000": ["0001", "1011", "0000", "0011", "0010", "1011", "0100", "0101"],
    "1001": ["1110", "0100", "0011", "0101", "1100", "0110", "1001", "1100"],
    "1010": ["0100", "0111", "0110", "1100", "1011", "0101", "1110", "1011"],
    "1011": ["0111", "1001", "1101", "0010", "0110", "0011", "0111", "0111"],
    "1100": ["1111", "0001", "0101", "0100", "0100", "0111", "0010", "1010"],
    "1101": ["1001", "1101", "1000", "1000", "1111", "1100", "1100", "0001"],
    "1110": ["1000", "1010", "1010", "1111", "1101", "1010", "1000", "0100"],
    "1111": ["0010", "0000", "0111", "0001", "0001", "0000", "1011", "0010"]
}


def convert_to_binary(string):
    res = ""
    for ch in string:
        word = "000000" + bin(ascii[ch])[2:]
        res += word[-6:]
    return res


def padding(pbinary):
    n = len(pbinary)
    rem = n % 128
    return pbinary + "1"*(128 - rem)


def convert_to_text(binary):
    n = len(binary)
    text = ""
    # print(binary, n)
    for start in range(0, n - 5, 6):
        text += char[int(binary[start:start+6], 2)]
    return text


def run_sbox(binary, round):
    word1 = binary[:32]
    word2 = binary[32:64]
    word3 = binary[64:96]
    word4 = binary[96:128]

    new1, new2, new3, new4 = "", "", "", ""
    for i in range(32):
        four_bits = word1[i] + word2[i] + word3[i] + word4[i]
        word = sbox[four_bits][round % 8]
        new1 += word[0]
        new2 += word[1]
        new3 += word[2]
        new4 += word[3]
    return new1 + new2 + new3 + new4


def reverse_sbox(binary, round):
    word1 = binary[:32]
    word2 = binary[32:64]
    word3 = binary[64:96]
    word4 = binary[96:128]

    new1, new2, new3, new4 = "", "", "", ""
    for i in range(32):
        four_bits = word1[i] + word2[i] + word3[i] + word4[i]
        word = inverse_sbox[four_bits][round % 8]
        new1 += word[0]
        new2 += word[1]
        new3 += word[2]
        new4 += word[3]
    return new1 + new2 + new3 + new4


def make_multiple6(binary):
    n = len(binary)
    rem = n % 6
    return binary + "1"*(6 - rem)


def make_multiple128(binary):
    n = len(binary)
    q = n // 128
    return binary[:q*128]


def serpent_encrypt(ptext):
    # print(ptext)
    pbinary = convert_to_binary(ptext)
    # print(pbinary, len(pbinary))
    pbinary_padded = padding(pbinary)
    # print(pbinary_padded, len(pbinary_padded))
    for round in range(32):
        cbinary_padded = ""
        for start in range(0, len(pbinary_padded)-127, 128):
            cbinary_padded += run_sbox(pbinary_padded[start:start+128], round)
        pbinary_padded = cbinary_padded[:]
        # print(round, pbinary_padded)
    pbinary_padded = make_multiple6(pbinary_padded)
    ctext = convert_to_text(pbinary_padded)
    # print(ctext, len(ctext))
    return ctext


def serpent_decrypt(ctext):
    cbinary = convert_to_binary(ctext)
    cbinary_trimmed = make_multiple128(cbinary)
    for round in range(31, -1, -1):
        pbinary = ""
        for start in range(0, len(cbinary_trimmed)-127, 128):
            pbinary += reverse_sbox(cbinary_trimmed[start:start+128], round)
        cbinary_trimmed = pbinary[:]
        # print(round, cbinary_trimmed)
    pbinary = make_multiple6(cbinary_trimmed)
    ptext = convert_to_text(pbinary)
    return ptext


if __name__ == "__main__":
    print("\n-------------------- S E R P E N T   C I P H E R --------------------")
    while True:
        ch = input("\nChoose option (e/d/q):  ")
        if ch == 'q':
            break
        elif ch == 'e':
            ptext = input("Enter plaintext to encrypt:  ")
            print("Encrypted String is:  {}".format(serpent_encrypt(ptext)))
        elif ch == 'd':
            ctext = input("Enter ciphertext to decrypt:  ")
            print("Decrypted String is:  {}".format(serpent_decrypt(ctext)))
        else:
            print("Invalid Choice!!!\n")
