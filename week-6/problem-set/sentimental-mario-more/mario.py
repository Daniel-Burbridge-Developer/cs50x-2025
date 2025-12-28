from cs50 import get_int


def main():
    num_height = 0
    height = ""
    while (num_height > 8) or (num_height <= 0):
        height = get_int("Height: ")
        num_height = int(height)

    for i in range(num_height):
        print((" " * (int(height) - (i + 1)) + "#" * (i + 1)) + ("  ") + "#" * (i + 1))


if __name__ == "__main__":
    main()
