import sys

with open(sys.argv[1], "rb") as binary:
    word = [0] * 4
    word[0] = binary.read(1)
    word[1] = binary.read(1)
    word[2] = binary.read(1)
    word[3] = binary.read(1)
    while word[0] != b"":
        print("0x" + word[0].hex() + ",0x" + word[1].hex() + ",0x" + word[2].hex() + ",0x" + word[3].hex() + ",")
        word[0] = binary.read(1)
        word[1] = binary.read(1)
        word[2] = binary.read(1)
        word[3] = binary.read(1)