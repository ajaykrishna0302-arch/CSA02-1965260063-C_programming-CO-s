#include <stdio.h>

#define RUPEES_TO_PAISE(r) ((long)((r) * 100))
#define SQUARE(x) ((x) * (x))
#define SQUARE_BAD(x) x * x
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int main(void)
{
    printf("Rs 2.25 in paise: %ld\n", RUPEES_TO_PAISE(2.25));
    printf("SQUARE(5)    = %d\n", SQUARE(5));
    printf("SQUARE_BAD(3+1) = %d  (expands to 3+1*3+1 = 7, wrong)\n", SQUARE_BAD(3+1));
    printf("SQUARE(3+1)  = %d  (fully parenthesised, correct)\n", SQUARE(3+1));
    int i = 9, j = 5;
    printf("MAX(i++, j)  = %d, i is now %d  (i++ evaluated twice)\n", MAX(i++, j), i);
    return 0;
}