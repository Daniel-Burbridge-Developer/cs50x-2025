from cs50 import get_int


def main():
    card = get_int("NUMBER: ")
    card_type = get_card_type(card)
    report_card_type(card_type)


def get_card_type(card):
    type_by_length = check_type_by_length(card)
    print(type_by_length)
    type_by_prefix = check_type_by_prefix(card)
    print(type_by_prefix)
    validate_card(card)

    if type_by_length == type_by_prefix:
        return type_by_length

    return None


def check_type_by_length(card):
    # Refactor to return array of potential types

    AMEX_LENGTH = 15
    MASTERCARD_LENGTH = 16
    VISA_LENGTHS = [13, 16]

    digit_count = len(str(card))
    print(f"DIGIT COUNT: {digit_count}")

    if digit_count == AMEX_LENGTH:
        return "AMEX"

    if digit_count == VISA_LENGTHS[0]:
        return "VISA"

    if digit_count == MASTERCARD_LENGTH:
        return "VISA OR MASTERCARD"

    return None


def check_type_by_prefix(card):
    AMEX_PREFIXS = [34, 37]
    MASTERCARD_PREFIXS = [51, 52, 53, 54, 55]
    VISA_PREFIXS = [40, 41, 42, 43, 44, 45, 46, 47, 48, 49]

    prefix = int(str(card)[0:2])

    print(f"PREFIX: {prefix}")

    if prefix in AMEX_PREFIXS:
        return "AMEX"

    if prefix in MASTERCARD_PREFIXS:
        return "MASTERCARD"

    if prefix in VISA_PREFIXS:
        return "VISA"

    return None


def validate_card(card):
    multiplier_digits = int(str(card)[-2::-2])
    addition_digits = int(str(card)[-1::-2])

    sum_one = 0

    for digit in str(multiplier_digits):
        d = int(digit) * 2
        if d > 9:
            sum_one += (d // 10) + (d % 10)
        else:
            sum_one += d

    sum_two = 0

    for digit in str(addition_digits):
        sum_two += int(digit)

    checkSum = sum_one + sum_two

    return checkSum % 10


def report_card_type(card_type):
    print(card_type)


if __name__ == "__main__":
    main()
