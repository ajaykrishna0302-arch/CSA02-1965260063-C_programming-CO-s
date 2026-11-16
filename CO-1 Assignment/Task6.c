#include <stdio.h>

int main(void)
{
    int house;
    long prev, curr;
    for (int rec = 1; rec <= 2; rec++) {
        printf("Record %d - enter house no, previous, current: ", rec);
        int got = scanf("%d %ld %ld", &house, &prev, &curr);
        if (got != 3) {
            printf("scanf returned %d: invalid input rejected "
                   "(letters are not readings).\n", got);
            return 1;
        }
        long units = curr - prev;
        long paise = 5000L + (units > 100 ? (units - 100) * 225L : 0L);
        printf("House %d: units = %ld, bill = Rs %ld.%02ld\n",
               house, units,