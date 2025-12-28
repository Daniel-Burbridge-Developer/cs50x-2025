def main():
    height = input("Height: ")
    for i in range(int(height)):
        print(" " * (int(height) - (i + 1)) + "#" * (i + 1))


if __name__ == "__main__":
    main()
