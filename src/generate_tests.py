import random


def write_file(file_name: str, mul):
    K = 50
    values = {chr(ord('A') + i): random.randint(0, 100) for i in range(K)}
    A = "".join([chr(ord('A') + random.randint(0, K)) for _ in range(mul*25)])
    B = "".join([chr(ord('A') + random.randint(0, K)) for _ in range(mul*25)])

    with open(file_name, "w") as f:
        f.write(str(K))
        f.write("\n")
        for key, value in values.items():
            f.write(key)
            f.write(" ")
            f.write(str(value))
            f.write("\n")
        f.write(A)
        f.write("\n")
        f.write(B)
        f.write("\n")

def main():
    for i in range(1, 21):
        write_file("inputs/test" + str(i) + ".txt", i)



if __name__ == "__main__":
    main()