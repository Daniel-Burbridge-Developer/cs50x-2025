#include <cs50.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_PREFIXES 5
#define MAX_LENGTHS 2
#define CARD_VARIATIONS 3

typedef struct {
  string prefixes[MAX_PREFIXES];
  int num_prefixes;
  int valid_lengths[MAX_LENGTHS];
  int num_lengths;
  string display_name;
} CardInformation;

typedef struct {
  string name;
  CardInformation info;
} CreditCard;

typedef struct {
  string number_as_string;
  int digit_count;
} PotentialCard;

PotentialCard request_user_input_as_card(char string_buffer[]) {
  long user_input = get_long("Number: ");
  int chars_written = sprintf(string_buffer, "%ld", user_input);
  string user_input_as_string = string_buffer;

  PotentialCard users_potential_card = {
      .number_as_string = user_input_as_string, .digit_count = chars_written};

  return users_potential_card;
}

bool validate_card(PotentialCard card) {
  string card_number = card.number_as_string;
  int digit_count = card.digit_count;

  int sum = 0;
  int temp_num = 0;
  for (int i = digit_count - 2; i >= 0; i -= 2) {
    temp_num = ((card_number[i] - '0') * 2);
    if (temp_num < 10) {
      sum += temp_num;
    } else {
      int temp_num_one = temp_num % 10;
      int temp_num_two = (temp_num / 10) % 10;
      int temp_num_three = temp_num_one + temp_num_two;
      sum += temp_num_three;
    }
  }

  for (int i = digit_count - 1; i >= 0; i -= 2) {
    sum += (card_number[i] - '0');
  }

  return sum % 10 == 0;
}

void get_card_type_from_length(PotentialCard card, CreditCard *CreditCardStore,
                               string potential_card_types[],
                               int *potential_card_types_count) {
  int digit_count = card.digit_count;

  for (int i = 0; i < CARD_VARIATIONS; i++) {
    for (int j = 0; j < CreditCardStore[i].info.num_lengths; j++) {
      if (digit_count == CreditCardStore[i].info.valid_lengths[j]) {
        potential_card_types[*potential_card_types_count] =
            CreditCardStore[i].info.display_name;
        (*potential_card_types_count)++;
      }
    }
  }

  for (int i = 0; i < *potential_card_types_count; i++) {
    // printf("Potential Card Type by length: %s\n", potential_card_types[i]);
  }
}

void get_card_type_from_prefix(PotentialCard card, CreditCard *CreditCardStore,
                               string potential_card_types[],
                               int *potential_card_types_count) {
  int digit_count = card.digit_count;
  string card_number = card.number_as_string;

  char prefix_buffer[30];

  for (int l = 0; l < digit_count; l++) {
    for (int m = 0; m <= l; m++) {
      prefix_buffer[m] = card_number[m];
      prefix_buffer[m + 1] = '\0';
    }
    string current_prefix = prefix_buffer;
    // printf("Current Prefix: %s\n", current_prefix);
    for (int j = 0; j < CARD_VARIATIONS; j++) {
      // printf("Current Card: %s\n", CreditCardStore[j].info.display_name);
      for (int k = 0; k < CreditCardStore[j].info.num_prefixes; k++) {
        string card_prefix = CreditCardStore[j].info.prefixes[k];
        // printf("Comapring Current Prefix: %s with Card Prefix %s\n",
        //        current_prefix, card_prefix);
        if (strcmp(current_prefix, card_prefix) == 0) {
          // printf("MATCH\n");
          potential_card_types[*potential_card_types_count] =
              CreditCardStore[j].info.display_name;
          (*potential_card_types_count)++;
        }
      }
    }
  }

  for (int i = 0; i < *potential_card_types_count; i++) {
    // printf("Potential Card Type by Prefix: %s\n", potential_card_types[i]);
  }
}

int main(void) {
  CreditCard CreditCardStore[CARD_VARIATIONS] = {
      {"American Express",
       {.prefixes = {"34", "37"},
        .num_prefixes = 2,
        .valid_lengths = {15},
        .num_lengths = 1,
        .display_name = "AMEX\n"}},
      {"MasterCard",
       {.prefixes = {"51", "52", "53", "54", "55"},
        .num_prefixes = 5,
        .valid_lengths = {16},
        .num_lengths = 1,
        .display_name = "MASTERCARD\n"}},
      {"Visa",
       {.prefixes = {"4"},
        .num_prefixes = 1,
        .valid_lengths = {13, 16},
        .num_lengths = 2,
        .display_name = "VISA\n"}},
  };

  char string_buffer[30];
  PotentialCard card_to_check = request_user_input_as_card(string_buffer);
  // printf("card_to_check_number: %s\n", card_to_check.number_as_string);
  bool valid = validate_card(card_to_check);

  if (valid != true) {
    printf("INVALID\n");
  } else {
    string potential_card_types_length[CARD_VARIATIONS];
    int potential_card_types_length_count = 0;
    get_card_type_from_length(card_to_check, CreditCardStore,
                              potential_card_types_length,
                              &potential_card_types_length_count);

    string potential_card_types_prefix[CARD_VARIATIONS];
    int potential_card_types_prefix_count = 0;
    get_card_type_from_prefix(card_to_check, CreditCardStore,
                              potential_card_types_prefix,
                              &potential_card_types_prefix_count);

    string card_type = "INVALID\n";
    for (int i = 0; i < potential_card_types_length_count; i++) {
      for (int k = 0; k < potential_card_types_prefix_count; k++) {
        if (strcmp(potential_card_types_length[i],
                   potential_card_types_prefix[k]) == 0) {
          card_type = potential_card_types_length[i];
          break;
        }
      }
    }

    printf("%s", card_type);
  }
}
