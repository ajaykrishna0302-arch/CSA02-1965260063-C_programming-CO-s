
#include <stdio.h>
#include <string.h>

#define N 8
#define LEN 30

int main(void)
{
    char names[N][LEN] = {
        "Kavya", "Arun", "Meena", "Arun",
        "Bala", "Divya", "Arun", "Charan"
    };

    long cmp_calls = 0, copies = 0;

    /* bubble-style sort by name, counting strcmp calls and character copies */
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - 1 - i; j++) {
            cmp_calls++;

            if (strcmp(names[j], names[j + 1]) > 0) {
                char t[LEN];

                strcpy(t, names[j]);
                strcpy(names[j], names[j + 1]);
                strcpy(names[j + 1], t);

                copies += 3 * LEN;  /* three full-width copies per swap */
            }
        }
    }

    printf("sorted directory:\n");

    for (int i = 0; i < N; i++)
        printf("  %s\n", names[i]);

    printf("strcmp calls = %ld, characters copied = %ld\n",
           cmp_calls, copies);

    /* binary search on the sorted names */
    const char *queries[] = {"Divya", "Farid"};

    for (int q = 0; q < 2; q++) {
        int low = 0, high = N - 1, found = -1, steps = 0;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            steps++;

            int c = strcmp(names[mid], queries[q]);

            if (c == 0) {
                found = mid;
                break;
            }

            if (c < 0)
                low = mid + 1;
            else
                high = mid - 1;
        }

        printf("search %-6s -> %s in %d comparisons\n",
               queries[q],
               found >= 0 ? "found" : "absent",
               steps);
    }

    /* duplicates sit next to each other after sorting */
    printf("duplicates:");

    for (int i = 0; i < N - 1; i++)
        if (strcmp(names[i], names[i + 1]) == 0)
            printf(" %s", names[i]);

    printf("\n");

    return 0;
}
