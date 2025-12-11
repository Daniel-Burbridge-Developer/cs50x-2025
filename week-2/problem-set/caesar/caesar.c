#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
bool only_digits(string arg);
int normalise_value(string arg);
string rotate_string(string text, int key);
char rotate_char(char c, int key);

int main(int argument_count, string* argv) {
  if (argument_count != 2) {
    printf("Usage: ./caesar key\n");
    return 1;
  }

  if (!only_digits(argv[1])) {
    printf("Usage: ./caesar key\n");
    return 1;
  }

  int key = normalise_value(argv[1]);
  string plain_text = get_string("plaintext: ");
  string encrypted_text = rotate_string(plain_text, key);
  printf("%s", encrypted_text);
}

bool only_digits(string arg) {
  for (int i = 0, n = strlen(arg); i < n; i++) {
    if (!isdigit(arg[i])) {
      return false;
    }
  }

  return true;
}

int normalise_value(string arg) {
  int value = atoi(arg);
  int key = value % 26;
  return key;
}

string rotate_string(string text, int key) {
  for (int i = 0, n = strlen(text); i < n; i++) {
    text[i] = rotate_char(text[i], key);
  }
  return text;
}

char rotate_char(char c, int key) {
  int new_char_int = c - key;
  printf("int rep of new char: %d\n", new_char_int);
  if (new_char_int < 97) {
    new_char_int += 26;
  }
  char new_char_char = (char)new_char_int;
  printf("char rep of new char: %c\n", new_char_char);

  return new_char_char;
}

// Pseudocode
// If 0 command line arguments => Return 1
// If 1 command line argument => Proceed
// if 2+ command line arguments => Return 1

// Check if command line argument is a digit.
// if not Digits => Return 1
// if Digits => Return as int

// Request Input
// If Alpha => Rotate by digits
// If not Alpha => Return as is.
// Output
