// Implements a dictionary's functionality

#include "dictionary.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

// My Func Signitures
unsigned int traverse_chain(node *curNode, int count);
unsigned int traverse_chain_and_compare(node *curNode, const char *word);
void traverse_chain_and_free(node *curNode);

// Returns true if word is in dictionary, else false
bool check(const char *word) {
  node *wordChain = table[hash(word)];

  if (wordChain != NULL) {
    return traverse_chain_and_compare(wordChain, word);
  }

  return false;
}

// Hashes word to a number
unsigned int hash(const char *word) {
  // TODO: Improve this hash function
  int hashsum = 0;
  for (int i = 0; word[i] != '\0'; i++) {
    hashsum += (int)word[i];
  }

  hashsum = hashsum % N;
  // printf("Hashsum: %i\n", hashsum);
  return hashsum;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary) {
  // TODO
  char c[1];
  int curLetter = 0;
  int hashsum = 0;
  char curWord[LENGTH + 1];
  FILE *dict = fopen(dictionary, "r");

  if (dict == NULL) {
    return false;
  }

  while (fread(c, sizeof(char), 1, dict) != 0) {
    if (c[0] == '\n') {
      curWord[curLetter] = '\0';
      curLetter = 0;
      hashsum = hash(curWord);
      ;
      node *newNode = malloc(sizeof(node));
      strcpy(newNode->word, curWord);
      newNode->next = table[hashsum];
      table[hashsum] = newNode;
    }
    curWord[curLetter] = c[0];
    curLetter++;
  }

  return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void) {
  int count = 0;
  for (int i = 0; i < N; i++) {
    if (table[i] != NULL) {
      count = traverse_chain(table[i], count);
    }
  }

  // printf("DICT SIZE %i\n", count);
  return count;
}

unsigned int traverse_chain(node *curNode, int count) {
  if (curNode->next == NULL) {
    return count + 1;
  }

  return traverse_chain(curNode->next, count + 1);
}

// I think I should be using a "callback" or I think it's curried??? function
// for this and change my original traverse chain. but well, here, we just
// duplicate code and repeat ourselves!
unsigned int traverse_chain_and_compare(node *curNode, const char *word) {
  if (strcmp(word, curNode->word) == 0) {
    return true;
  }

  if (curNode->next == NULL) {
    return false;
  }

  return traverse_chain_and_compare(curNode->next, word);
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void) {
  for (int i = 0; i < N; i++) {
    free(table[i]);
    table[i] = NULL;
  }

  bool all_null = true;
  for (int i = 0; i < N; i++) {
    if (table[i] != NULL) {
      all_null = false;
    }
  }

  if (all_null) {
    printf("returning true");
  } else {
    printf("returning false");
  }
  return true;
}

void traverse_chain_and_free(node *curNode) {
  if (curNode->next == NULL) {
    return free(curNode);
  }

  return traverse_chain_and_free(curNode->next);
}
