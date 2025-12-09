#include <cs50.h>
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

  long user_input = get_long("Number: ");
  printf("This is your number: %li", user_input);
}
