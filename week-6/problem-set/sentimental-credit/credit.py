from cs50 import get_int


def main():
    card = get_int("NUMBER: ")
    report_card_type(get_card_type(card), validate_card(card))


def get_card_type(card):
    type_by_length = check_type_by_length(card)
    type_by_prefix = check_type_by_prefix(card)

    for type in type_by_length:
        if type in type_by_prefix:
            return type

    return "INVALID"


def check_type_by_length(card):
    AMEX_LENGTH = 15
    MASTERCARD_LENGTH = 16
    VISA_LENGTHS = [13, 16]

    digit_count = len(str(card))

    potential_cards = []

    if digit_count == AMEX_LENGTH:
        potential_cards.append("AMEX")

    if digit_count == VISA_LENGTHS[0]:
        potential_cards.append("MASTERCARD")

    if digit_count == MASTERCARD_LENGTH:
        potential_cards.append("VISA")

    return potential_cards


def check_type_by_prefix(card):
    AMEX_PREFIXS = [34, 37]
    MASTERCARD_PREFIXS = [51, 52, 53, 54, 55]
    VISA_PREFIXS = [40, 41, 42, 43, 44, 45, 46, 47, 48, 49]

    potential_cards = []

    prefix = int(str(card)[0:2])

    if prefix in AMEX_PREFIXS:
        potential_cards.append("AMEX")

    if prefix in MASTERCARD_PREFIXS:
        potential_cards.append("MASTERCARD")

    if prefix in VISA_PREFIXS:
        potential_cards.append("VISA")

    return potential_cards


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
    return checkSum % 10 == 0


def report_card_type(card_type, valid):
    if valid:
        print(card_type)
    else:
        print("INVALID")


if __name__ == "__main__":
    main()
