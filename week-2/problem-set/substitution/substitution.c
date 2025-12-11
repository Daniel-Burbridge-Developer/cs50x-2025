#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool validate_key(string arg);

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
  // Do Stuff
  return 0;
}

bool validate_key(string arg) {
  if (strlen(arg) != 26) {
    return false;
  }

  bool seen[26];
  for (int i = 0, n = strlen(arg); i < n; i++) {
    if (!isalpha(arg[i])) {
      return false;
    } else {
      int position = arg[i] - (int)arg[i];
      if (seen[position]) {
        return false;
      } else {
        seen[position] = true;
      }
    }
  }

  return true;
}
