#include <cs50.h>
#include <stdbool.h>
#include <stdio.h>

#define MAX_PREFIXES 5
#define MAX_LENGTHS 2
#define CARD_VARIATIONS 3

int main(void) {
  // This seems terrible ineffecient to allocate large arrays, and then use less
  // of their space. But that's okay, one day I'll know how to avoid doing it
  // this way.

  typedef struct {
    int prefixes[MAX_PREFIXES];
    int num_prefixes;
    int valid_lengths[MAX_LENGTHS];
    int num_lengths;
    string display_name;
  } CardInformation;

  typedef struct {
    string name;
    CardInformation info;
  } CreditCard;

  CreditCard CreditCardStore[CARD_VARIATIONS] = {
      {"American Express",
       {.prefixes = {34, 37},
        .num_prefixes = 2,
        .valid_lengths = {15},
        .num_lengths = 1,
        .display_name = "AMEX"}},
      {"MasterCard",
       {.prefixes = {51, 52, 53, 54, 55},
        .num_prefixes = 5,
        .valid_lengths = {16},
        .num_lengths = 1,
        .display_name = "MASTERCARD"}},
      {"Visa",
       {.prefixes = {4},
        .num_prefixes = 1,
        .valid_lengths = {13, 16},
        .num_lengths = 2,
        .display_name = "VISA"}},
  };

  // There is an error in my logic here that I cannot solve. Numbers such as
  // "01" (leading with a 0) digits are incorrectly assessed, as storing them as
  // a long immediately truncates the leading 0. As none of the credit-cards can
  // be pre-fixed with a 0, I'm choosing to ignore this error for now instead of
  // changing implementation to ask the user for a string and deal with
  // type-casting.

  printf("USER INPUT:\n");
  long user_input = get_long("Number: ");
  int cc_length = 0;
  if (user_input == 0) {
    cc_length = 1;
  } else {
    long temp = user_input;
    while (temp > 0) {
      temp /= 10;
      cc_length++;
    }
  }

  int cc_prefix = user_input / ((cc_length));

  // string potential_cards_based_on_prefix[CARD_VARIATIONS];
  // int potential_cards_based_on_prefix_count = 0;
  string potential_cards_based_on_length[CARD_VARIATIONS];
  int potential_cards_based_on_length_count = 0;

  printf("\nCARD CHECKS BEGIN:\n");
  // Determine if a Card matches the length of a known Card.
  for (int i = 0; i < CARD_VARIATIONS; i++) {
    printf("Checking Card: %s\n", CreditCardStore[i].name);
    for (int j = 0; j < CreditCardStore[i].info.num_lengths; j++) {
      printf("Checking CC length of %d against valid length of %d\n", cc_length,
             CreditCardStore[i].info.valid_lengths[j]);
      if (cc_length == CreditCardStore[i].info.valid_lengths[j]) {
        printf("Match found!\n");
        potential_cards_based_on_length[potential_cards_based_on_length_count] =
            CreditCardStore[i].info.display_name;
        potential_cards_based_on_length_count++;
      }
    }
  }

  // // Determine if a Card matches the prefix of a known Card.
  // for (int i = 0; i < CARD_VARIATIONS; i++) {
  //   for (int j = 0; j < CreditCardStore[i].info.num_prefixes; j++) {
  //     if (cc_length == CreditCardStore[i].info.prefixes[j]) {
  //       potential_cards_based_on_prefix[potential_cards_based_on_prefix_count]
  //       =
  //           CreditCardStore[i].info.display_name;
  //     }
  //   }
  // }

  printf("\nDEBUG LOG:\n");
  printf("This is your number: %li\n", user_input);
  printf("Just so I'm using the variable and make stops yelling at me - %s\n",
         CreditCardStore[1].info.display_name);

  printf("your input was %d digit(s) long\n", cc_length);

  printf("Your numbers starts with the digits %d\n\n", cc_prefix);

  printf("You have %d potential matches based on length\n",
         potential_cards_based_on_length_count);

  for (int i = 0; i < potential_cards_based_on_length_count; i++) {
    printf("Based off the length of your card, it could be a: %s\n",
           potential_cards_based_on_length[i]);
  }
}
