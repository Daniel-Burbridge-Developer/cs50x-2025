def main():
    num_height = 0
    height = ""
    while (num_height > 8) and (num_height <= 0):
        height = input("Height: ")
        num_height = int(height)

    for i in range(int(height)):
        print(" " * (int(height) - (i + 1)) + "#" * (i + 1))


if __name__ == "__main__":
    main()
