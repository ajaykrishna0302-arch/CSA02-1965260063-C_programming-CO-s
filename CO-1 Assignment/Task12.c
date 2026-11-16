#include <stdio.h>

typedef struct {
    long rate1, rate2, rate3;   /* paise per unit, read at run time */
    long fixed_paise;
    long peak_surcharge_pct;    /* 20 means +20% between 6 PM and 10 PM */
} Tariff;

long compute_bill(const Tariff *t, long units, long peak_units)
{
    long paise = t->fixed_paise;
    long u = units;
    if (u > 200) { paise += (u - 200) * t->rate3; u = 200; }
    if (u > 100) { paise += (u - 100) * t->rate2; u = 100; }
    paise += u * t->rate1;
    paise += peak_units * t->rate3 * t->peak_surcharge_pct / 100;
    return paise;
}

int main(void)
{
    Tariff t = {0, 225, 450, 5000, 20};   /* from a config file, not #define */
    long bill = compute_bill(&t, 350, 40);
    printf("350 units, 40 in peak hours -> Rs %ld.%02ld\n", bill / 100, bill % 100);
    t.rate2 = 230;                        /* tariff revision without recompiling */
    bill = compute_bill(&t, 350, 40);
    printf("after rate revision         -> Rs %ld.%02ld\n", bill / 100, bill % 100);
    return 0;
}