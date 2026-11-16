
#include <stdio.h>

long comps, moves;

void bubble(int a[], int n)
{
    comps = moves = 0;

    for (int i = 0; i < n - 1; i++) {
        int exchanged = 0;             /* early-exit flag */

        for (int j = 0; j < n - 1 - i; j++) {
            comps++;

            if (a[j] > a[j + 1]) {
                int t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;

                moves++;
                exchanged = 1;
            }
        }

        if (!exchanged) break;         /* already in order */
    }
}

void selection(int a[], int n)
{
    comps = moves = 0;

    for (int i = 0; i < n - 1; i++) {
        int m = i;

        for (int j = i + 1; j < n; j++) {
            comps++;
            if (a[j] < a[m]) m = j;
        }

        if (m != i) {
            int t = a[i];
            a[i] = a[m];
            a[m] = t;
            moves++;
        }
    }
}

void insertion(int a[], int n)
{
    comps = moves = 0;

    for (int i = 1; i < n; i++) {
        int key = a[i], j = i - 1;

        while (j >= 0) {
            comps++;

            if (a[j] <= key) break;

            a[j + 1] = a[j];
            moves++;
            j--;
        }

        a[j + 1] = key;
    }
}

void run(const char *order, const int src[], int n)
{
    int a[16];

    const char *names[] = {
        "bubble", "selection", "insertion"
    };

    void (*fns[])(int *, int) = {
        bubble, selection, insertion
    };

    for (int f = 0; f < 3; f++) {
        for (int i = 0; i < n; i++)
            a[i] = src[i];

        fns[f](a, n);

        printf("%-13s %-10s comparisons = %2ld, swaps/shifts = %2ld\n",
               order, names[f], comps, moves);
    }
}

int main(void)
{
    int sorted[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int nearly[] = {1, 2, 3, 5, 4, 6, 8, 7};
    int rev[] = {8, 7, 6, 5, 4, 3, 2, 1};
    int rnd[] = {4, 8, 1, 6, 3, 7, 2, 5};

    run("sorted", sorted, 8);
    run("nearly sorted", nearly, 8);
    run("reverse", rev, 8);
    run("random", rnd, 8);

    return 0;
}
