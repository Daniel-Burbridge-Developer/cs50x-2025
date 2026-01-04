from cs50 import get_string


def main():
    text = get_string("Text: ")
    counts = generate_counts(text)
    rank = calculate_reading_level(text, counts)

    if rank < 1:
        print("Before Grade 1")
    elif rank >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {rank}")


def generate_counts(text):
    LETTERS = [
        "a",
        "b",
        "c",
        "d",
        "e",
        "f",
        "g",
        "h",
        "i",
        "j",
        "k",
        "l",
        "m",
        "n",
        "o",
        "p",
        "q",
        "r",
        "s",
        "t",
        "u",
        "v",
        "w",
        "x",
        "y",
        "z",
        "A",
        "B",
        "C",
        "D",
        "E",
        "F",
        "G",
        "H",
        "I",
        "J",
        "K",
        "L",
        "M",
        "N",
        "O",
        "P",
        "Q",
        "R",
        "S",
        "T",
        "U",
        "V",
        "W",
        "X",
        "Y",
        "Z",
    ]
    SEPERATORS = [" "]
    PUNCTUATION = [".", "!", "?"]

    # Words initated as 1, to account for the face a space sperates 2 words. This will cause an error on sentences texts with 0 words, I don't believe I need to account for this edge-case but if I needed to I could see if there is atleast a single space in the text and go from there.
    counts = {"letters": 0, "words": 1, "sentences": 0}
    for character in text:
        if character in LETTERS:
            counts["letters"] += 1
        if character in SEPERATORS:
            counts["words"] += 1
        if character in PUNCTUATION:
            counts["sentences"] += 1

    return counts


def calculate_reading_level(text, counts):
    L = (counts["letters"] / counts["words"]) * 100
    S = (counts["sentences"] / counts["words"]) * 100

    return round(0.0588 * L - 0.296 * S - 15.8)


if __name__ == "__main__":
    main()
