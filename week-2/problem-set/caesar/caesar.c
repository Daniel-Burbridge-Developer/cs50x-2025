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
  printf("ciphertext: %s\n", encrypted_text);
  return 0;
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
  int key = atoi(arg);
  return key;
}

string rotate_string(string text, int key) {
  for (int i = 0, n = strlen(text); i < n; i++) {
    text[i] = rotate_char(text[i], key);
  }
  return text;
}

char rotate_char(char c, int key) {
  if (isupper(c)) {
    c = (char)((((c - (int)'A') + key) % 26) + (int)'A');
  }

  if (islower(c)) {
    c = (char)((((c - (int)'a') + key) % 26) + (int)'a');
  }

  return c;
}
