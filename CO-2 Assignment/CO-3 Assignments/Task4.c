
#include <stdio.h>

/* a[] and b[] are merit lists sorted in DESCENDING order of score.
   Copies both into out[] in descending order and returns the total count. */

int merge(const int a[], int na, const int b[], int nb, int out[])
{
    int i = 0, j = 0, k = 0;

    while (i < na && j < nb) {
        if (a[i] >= b[j])
            out[k++] = a[i++];  /* equal scores: campus A first */
        else
            out[k++] = b[j++];
    }

    while (i < na)
        out[k++] = a[i++];      /* copy whatever remains */

    while (j < nb)
        out[k++] = b[j++];

    return k;
}

void show(const char *label, const int a[], int na,
          const int b[], int nb)
{
    int merged[16];
    int n = merge(a, na, b, nb, merged);

    printf("%s: ", label);

    for (int i = 0; i < n; i++)
        printf("%d ", merged[i]);

    printf("\n");
}

int main(void)
{
    int campusA[] = {98, 91, 85, 72};
    int campusB[] = {95, 91, 80};
    int empty[] = {0};

    show("A + B", campusA, 4, campusB, 3);
    show("A + empty list", campusA, 4, empty, 0);

    return 0;
}
