#include <stdio.h>

int main(void)
{
    char name[8];
    printf("enter donor name: ");
    scanf("%s", name);   /* no width limit: a long name overflows name[] */
    printf("stored: %s\n", name);
    return 0;
}