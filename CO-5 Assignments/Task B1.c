#include <stdio.h>
#include <stdlib.h>

long long power_linear(long long base, int exp)
{
    if (exp == 0) return 1;
    return base * power_linear(base, exp - 1);
}

long long power_iter(long long base, int exp)
{
    long long r = 1;
    while (exp > 0) { r *= base; exp--; }
    return r;
}

int main(int argc, char *argv[])
{
    int depth = argc > 1 ? atoi(argv[1]) : 100000;
    if (argc > 2) {
        printf("iterative at depth %d: finished fine\n", depth);
        (void)power_iter(2, depth);
    } else {
        printf("recursion at depth %d: ", depth);
        fflush(stdout);
        (void)power_linear(2, depth);
        printf("finished fine\n");
    }
    return 0;
}