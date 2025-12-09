#include <stdio.h>
#include <cs50.h>

int get_change_req(){
    int user_input;
    do {
       user_input = get_int("Change owed: ");
    } while (user_input < 0);
    return user_input;
}

int calc_coins(int remaining_change, int sum, int* coins, int coins_length) {
    if (remaining_change == 0) {
        return sum;
    }
    
    // printf("%i\n", remaining_change);
    // printf("%i\n", sum);
    // printf("%i , %i , %i , %i\n",coins[0], coins[1], coins[2], coins[3]);


    for (int i = 0; i < coins_length; i++){
        if (remaining_change >= coins[i])
        { 
            remaining_change = remaining_change - coins[i];
            break;
        }
    }

    return calc_coins(remaining_change, sum + 1, coins, coins_length);

}

int main(void)
{
    int coins[4] = {25, 10, 5, 1};
    int coins_length = sizeof(coins) / sizeof(coins[0]);
    int req_change = get_change_req();
    // printf("%i, %i, %i, %i",coins[0], coins[1], coins[2], coins[3]);
    // printf("%i", req_change);
    printf("%i", calc_coins(req_change, 0, coins, coins_length));

}

