#include <stdio.h>

int main(void)
{
    int units = 250;
    printf("Surprise 1: units / 100   = %d   (integer division drops the fraction)\n",
           units / 100);
    printf("            units / 100.0 = %.2f (converting first keeps it)\n",
           units / 100.0);

    float f = 0.1f + 0.2f;
    printf("Surprise 2: 0.1f + 0.2f = %.10f (float cannot hold 0.3 exactly)\n", f);

    long big = 3000000000L;      /* about Rs 3 crore in paise at district scale */
    int small = (int)big;
    printf("Surprise 3: (int)3000000000L = %d (the value no longer fits in int)\n",
           small);
    return 0;
}