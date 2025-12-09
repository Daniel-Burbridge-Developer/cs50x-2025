#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int number;
    do {
        number = get_int("Height: ");
    } while (number <  1);

    for (int i = number; i > 0; i--) {
        for (int j = 0; j < number; j++) {
            if (j < i-1) {
                printf(" ");
            } else {
                printf("#");
            }
        }
        printf ("  ");
        for (int k = 0; k < number; k++) {
            if (k < i-1) {

            } else {
                printf("#");
            }
        }
        printf("\n");
    }
}