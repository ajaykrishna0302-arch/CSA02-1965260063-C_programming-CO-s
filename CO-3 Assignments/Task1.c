
#include <stdio.h>

int steps; /* comparisons made by the last search */

/* a[] is sorted in ascending order. Returns the index of key, or -1. */
int binary_search(const int a[], int n, int key)
{
    steps = 0;
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;  /* overflow-safe midpoint */
        steps++;

        if (a[mid] == key) return mid;
        if (a[mid] < key) low = mid + 1;
        else high = mid - 1;
    }

    return -1;
}

int linear_search(const int a[], int n, int key)
{
    steps = 0;

    for (int i = 0; i < n; i++) {
        steps++;
        if (a[i] == key) return i;
    }

    return -1;
}

int main(void)
{
    int accession[] = {
        1021, 1048, 1103, 1190, 1222,
        1305, 1377, 1402, 1460, 1533
    };

    int n = sizeof accession / sizeof accession[0];

    int keys[] = {1021, 1305, 1533, 1400};

    for (int k = 0; k < 4; k++) {
        int pos = binary_search(accession, n, keys[k]);
        int bs = steps;

        linear_search(accession, n, keys[k]);

        printf("Book %d -> index %2d, binary = %d, linear = %d comparisons\n",
               keys[k], pos, bs, steps);
    }

    return 0;
}
