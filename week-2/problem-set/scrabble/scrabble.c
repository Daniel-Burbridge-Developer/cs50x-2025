#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

string get_input_from_player(int player) {
  return get_string("Player %d: ", player + 1);
}

int score_answer(string answer) {
  char string_buffer[50];
  int answer_length = sprintf(string_buffer, "%s", answer);

  printf("String %s is %d characters long!\n", answer, answer_length);

  int sum = 0;
  for (int i = 0; i < answer_length; i++) {
    answer[i] = tolower(answer[i]);
    int points = answer[i] - 'a' + 1;
    printf("%c is worth %d points, adding to %d equals, %d\n", answer[i],
           points, sum, points + sum);
    sum += points;
  }

  printf("SCORE: %d\n", sum);
  return sum;
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
