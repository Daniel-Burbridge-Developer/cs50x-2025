from cs50 import get_float


def main():
    change = get_float("Change: ")
    coin_types = [0.25, 0.10, 0.05, 0.01]

    while change < 0:
        change = get_float("Change: ")

    coin_count = 0
    for coin in coin_types:
        print(f"floating point error {change}")
        while change >= coin:
            coin_count += 1
            change -= coin

    print(f"{coin_count}")


if __name__ == "__main__":
    main()
