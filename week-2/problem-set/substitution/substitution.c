#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool validate_key(string arg);
string rotate_string(string text, string key);

int main(int argument_count, string* argv) {
  if (argument_count != 2) {
    printf("Usage: ./substitution key\n");
    return 1;
  }

  if (!validate_key(argv[1])) {
    printf("Key must contain exactly 26 unique alphabetic characters\n");
    return 1;
  }

  string plaintext = get_string("plaintext: ");
  printf("ciphertext: %s\n", rotate_string(plaintext, argv[1]));
  return 0;
}

bool validate_key(string arg) {
  if (strlen(arg) != 26) {
    return false;
  }

  bool seen[26] = {false};
  for (int i = 0, n = strlen(arg); i < n; i++) {
    // printf("letter: %c\n", arg[i]);
    if (!isalpha(arg[i])) {
      return false;
    } else {
      int position = toupper(arg[i]) - (int)'A';
      // printf("position: %d\n", position);
      if (seen[position]) {
        return false;
      } else {
        seen[position] = true;
      }
    }
  }

  return true;
}

string rotate_string(string text, string key) {
  for (int i = 0, n = strlen(text); i < n; i++) {
    if (isupper(text[i])) {
      text[i] = toupper(key[text[i] - (int)'A']);
    }
    if (islower(text[i])) {
      text[i] = tolower(key[text[i] - (int)'a']);
    }
  }

  return text;
}
