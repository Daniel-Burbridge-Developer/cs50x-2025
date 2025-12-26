// Implements a dictionary's functionality

#include "dictionary.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

// Represents a node in a hash table
typedef struct node {
  char word[LENGTH + 1];
  struct node *next;
} node;

// TODO: Choose number of buckets in hash table
#define N 26

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word) {
  // TODO
  return false;
}

// Hashes word to a number
unsigned int hash(const char *word) {
  // TODO: Improve this hash function
  return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary) {
  // TODO
  char c[1];
  int curLetter = 0;
  char curWord[LENGTH + 1];
  FILE *dict = fopen(dictionary, "r");

  if (dict == NULL) {
    return false;
  }

  while (fread(c, sizeof(char), 1, dict) != 0) {
    curWord[curLetter] = c[0];
    curLetter++;
    if (c[0] == '\n') {
      curWord[curLetter] = '\0';
      curLetter = 0;
      printf("%s", curWord);
    }
  }

  return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void) {
  // TODO
  return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void) {
  // TODO
  return false;
}
