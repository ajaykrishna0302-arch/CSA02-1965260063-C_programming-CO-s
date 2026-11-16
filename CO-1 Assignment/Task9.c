#include <stdio.h>

#define SLAB1_UNITS 100
#define SLAB2_UNITS 200
#define RATE1_PAISE 0L
#define RATE2_PAISE 225L
#define RATE3_PAISE 450L
#define FIXED_CHARGE_PAISE 5000L

typedef unsigned short meter_t;

unsigned int consumption(meter_t previous, meter_t current)
{
    return (unsigned int)(meter_t)(current - previous);
}

long compute_bill(long units)
{
    long paise = FIXED_CHARGE_PAISE;
    if (units > SLAB2_UNITS) {
        paise += (units - SLAB2_UNITS) * RATE3_PAISE;
        units = SLAB2_UNITS;
    }
    if (units > SLAB1_UNITS) {
        paise += (units - SLAB1_UNITS) * RATE2_PAISE;
        units = SLAB1_UNITS;
    }
    paise += units * RATE1_PAISE;
    return paise;
}

int main(void)
{
    struct { meter_t prev, curr; const char *note; } tests[] = {
        {1200, 1530, "normal bill, reaches slab 3"},
        {0, 100,     "boundary: exactly 100 units"},
        {100, 300,   "boundary: exactly 200 units"},
        {500, 500,   "zero units"},
        {65400, 120, "meter rolled over 65535 -> 0"},
    };
    long total = 0;
    printf("%8s %8s %6s  %9s  %s\n", "prev", "current", "units", "bill", "case");
    for (int i = 0; i < 5; i++) {
        unsigned int u = consumption(tests[i].prev, tests[i].curr);
        long bill = compute_bill(u);
        total += bill;
        printf("%8u %8u %6u  Rs %4ld.%02ld  %s\n",
               tests[i].prev, tests[i].curr, u, bill / 100, bill % 100,
               tests[i].note);
    }
    printf("Hand-checked total of the 5 bills: Rs %ld.%02ld\n", total / 100, total % 100);
    return 0;
}