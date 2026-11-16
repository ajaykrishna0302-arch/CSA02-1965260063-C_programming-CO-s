#include <stdio.h>
#include "billing.h"

/* Compile with gcc -DDEBUG to see the intermediate values. */

long compute_bill(long units)
{
    long paise = FIXED_CHARGE_PAISE;
#ifdef DEBUG
    printf("[debug] start: fixed charge = %ld paise\n", paise);
#endif
    if (units > SLAB2_UNITS) {
        paise += (units - SLAB2_UNITS) * RATE3_PAISE;
        units = SLAB2_UNITS;
    }
    if (units > SLAB1_UNITS) {
        paise += (units - SLAB1_UNITS) * RATE2_PAISE;
        units = SLAB1_UNITS;
    }
#ifdef DEBUG
    printf("[debug] after energy charge: %ld paise\n", paise);
#endif
    return paise;
}

unsigned int consumption(meter_t previous, meter_t current)
{
    return (unsigned int)(meter_t)(current - previous);
}

int main(void)
{
    long bill = compute_bill(350);
    printf("Bill for 350 units: Rs %ld.%02ld\n", bill / 100, bill % 100);
    return 0;
}