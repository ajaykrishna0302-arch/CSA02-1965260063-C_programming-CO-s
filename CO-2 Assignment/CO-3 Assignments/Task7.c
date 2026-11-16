
#include <stdio.h>
#include <time.h>

int main(void)
{
    int votes[] = {3, 1, 2, 3, 0, 2, 3, 2, 7, 1, 3, -4, 2, 3, 1};
    int nvotes = 15, cand = 3;
    int count[13] = {0};        /* one slot per candidate number */
    int valid = 0, invalid = 0;

    for (int i = 0; i < nvotes; i++) {
        int v = votes[i];

        if (v >= 1 && v <= cand) {
            count[v]++;
            valid++;
        }
        else
            invalid++;
    }

    printf("valid votes = %d, invalid votes = %d\n", valid, invalid);

    /* result order: candidates in descending order of votes (selection sort) */
    int order[13];

    for (int c = 1; c <= cand; c++)
        order[c - 1] = c;

    for (int i = 0; i < cand - 1; i++)
        for (int j = i + 1; j < cand; j++)
            if (count[order[j]] > count[order[i]]) {
                int t = order[i];
                order[i] = order[j];
                order[j] = t;
            }

    printf("results: ");

    for (int i = 0; i < cand; i++)
        printf("candidate %d = %d  ", order[i], count[order[i]]);

    printf("\n");

    int winner = order[0];

    if (cand > 1 && count[order[1]] == count[winner])
        printf("Result: tie at %d votes\n", count[winner]);
    else
        printf("Winner: candidate %d with %d votes\n",
               winner, count[winner]);

    /* timing: count 5,000 and 500,000 generated votes */
    for (long n = 5000; n <= 500000; n *= 100) {
        int c12[13] = {0};
        unsigned x = 12345;
        clock_t t0 = clock();

        for (long i = 0; i < n; i++) {
            x = x * 1103515245u + 12345u;  /* simple generator */

            int v = (x >> 16) % 14 - 1;   /* includes some invalid votes */

            if (v >= 1 && v <= 12)
                c12[v]++;
        }

        double ms = 1000.0 * (clock() - t0) / CLOCKS_PER_SEC;

        printf("counting %ld votes took %.3f ms\n", n, ms);
    }

    return 0;
}
