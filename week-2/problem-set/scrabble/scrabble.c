#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

string get_input_from_player(int player) {
  return get_string("Player %d: ", player + 1);
}

int silly_letter_to_point_conversation(char c) {
  if (c == 'a' || c == 'e' || c == 'i' || c == 'l' || c == 'n' || c == 'o' ||
      c == 'r' || c == 's' || c == 't' || c == 'u') {
    return 1;
  } else if (c == 'd' || c == 'g') {
    return 2;
  } else if (c == 'b' || c == 'c' || c == 'm' || c == 'p') {
    return 3;
  } else if (c == 'f' || c == 'h' || c == 'v' || c == 'w' || c == 'y') {
    return 4;
  } else if (c == 'k') {
    return 5;
  } else if (c == 'j' || c == 'x') {
    return 8;
  } else if (c == 'q' || c == 'z') {
    return 10;
  }
  return 0;  // Should not happen for valid letters
}

int score_answer(string answer) {
  char string_buffer[50];
  int answer_length = sprintf(string_buffer, "%s", answer);

  printf("String %s is %d characters long!\n", answer, answer_length);

  int sum = 0;
  for (int i = 0; i < answer_length; i++) {
    answer[i] = tolower(answer[i]);
    int points = silly_letter_to_point_conversation(answer[i]);
    printf("%c is worth %d points, adding to %d equals, %d\n", answer[i],
           points, sum, points + sum);
    sum += points;
  }

  printf("SCORE: %d\n", sum);
  return sum;
}

// I'm not sure on Dict / Hashmap syntax for C. Does it even exist?
// I don't even know switch statement. Forgive me for this code...

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
