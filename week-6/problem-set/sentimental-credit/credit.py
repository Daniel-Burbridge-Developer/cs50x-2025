from cs50 import get_int
import re


def main():
    card = get_int("NUMBER: ")
    card_type = get_card_type(card)
    report_card_type(card_type)


def get_card_type(card):
    type_by_length = check_type_by_length(card)
    print(type_by_length)
    type_by_prefix = check_type_by_prefix(card)
    print(type_by_prefix)

    if type_by_length == type_by_prefix:
        return type_by_length

    return None


def check_type_by_length(card):
    # Refactor to return array of potential types

    AMEX_LENGTH = 15
    MASTERCARD_LENGTH = 16
    VISA_LENGTHS = [13, 16]

    digit_count = re.match("%\{16}", str(card))

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

    prefix = re.split("^\d{2}", str(card))
    print(f"PREFIX: {prefix}")

    if prefix in AMEX_PREFIXS:
        return "AMEX"

    if prefix in MASTERCARD_PREFIXS:
        return "MASTERCARD"

    if prefix in VISA_PREFIXS:
        return "VISA"

    return None


def report_card_type(card_type):
    print(card_type)


if __name__ == "__main__":
    main()
