#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int get_letter_count(string text) {
  int count = 0;

  for (int i = 0, n = strlen(text); i < n; i++) {
    if (isalpha(text[i])) {
      count++;
    }
  }
  return count;
}

int get_word_count(string text) {
  // wasSpace set to 1 to ensure first word in text is captured and counted.
  int count = 0;
  int wasSpace = 1;

  for (int i = 0, n = strlen(text); i < n; i++) {
    if ((isalpha(text[i]) || ispunct(text[i])) && (wasSpace == 1)) {
      wasSpace = 0;
      count++;
    }
    if (isspace(text[i])) {
      wasSpace = 1;
    }
  }

  return count;
}

int get_sentence_count(string text) {
  int count = 0;
  int wasNonPunct = 0;

  for (int i = 0, n = strlen(text); i < n; i++) {
    if (ispunct(text[i]) && wasNonPunct == 1) {
      wasNonPunct = 0;
      count++;
    }
    if ((isalpha(text[i]) || isspace(text[i]))) {
      wasNonPunct = 1;
    }
  }

  return count;
}

int main(void) {
  string text = get_string("Text: ");

  int letter_count = get_letter_count(text);
  printf("Letter Count: %d\n", letter_count);
  int word_count = get_word_count(text);
  printf("Word Count: %d\n", word_count);
  int sentence_count = get_sentence_count(text);
  printf("Sentence Count: %d\n", sentence_count);
}
