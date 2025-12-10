#include <cs50.h>
#include <stdio.h>

string get_input_from_player(int player) {
  return get_string("Player %d: ", player + 1);
}

int score_answer(string answer) {
  printf("Answer: %s\n", answer);
  return 1;
}

int main(void) {
  const int PLAYERS = 2;
  string answers[PLAYERS];

  for (int i = 0; i < PLAYERS; i++) {
    answers[i] = get_input_from_player(i);
  }

  for (int i = 0; i < PLAYERS; i++) {
    score_answer(answers[i]);
  }
}
