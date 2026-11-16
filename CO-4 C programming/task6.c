
#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 10

struct date {
    int day, month, year;
};

enum item_kind { PACKAGED, COOKED, COMBO };

struct item {
    int id;
    char name[24];
    int price_paise;
    int stock;
    enum item_kind kind;
    union {
        struct date expiry;  /* PACKAGED: expiry date */
        int prepared_hour;   /* COOKED: hour prepared (0-23) */
        int parts[3];        /* COMBO: ids of up to 3 items */
    } detail;
};

int days_between(struct date a, struct date b)
{
    /* rough day count, 30-day months - enough for a two-day expiry check */
    return (b.year - a.year) * 360
         + (b.month - a.month) * 30
         + (b.day - a.day);
}

int sell(struct item *it, int qty)
{
    if (qty > it->stock) return 0;  /* sale exceeds stock: refused */

    it->stock -= qty;
    return 1;
}

int main(void)
{
    struct item items[3] = {
        {1, "Biscuit pack", 3000, 10, PACKAGED,
            .detail.expiry = {16, 11, 2026}},

        {2, "Veg puff", 2500, 2, COOKED,
            .detail.prepared_hour = 9},

        {3, "Lunch combo", 9000, 5, COMBO,
            .detail.parts = {2, 1, 0}}
    };

    struct date today = {14, 11, 2026};

    printf("-- sales --\n");

    printf("sell 3 x Biscuit pack: %s\n",
           sell(&items[0], 3) ? "ok" : "not enough stock");

    printf("sell 5 x Veg puff:    %s\n",
           sell(&items[1], 5) ? "ok" : "not enough stock");

    printf("sell 2 x Lunch combo: %s\n",
           sell(&items[2], 2) ? "ok" : "not enough stock");

    printf("-- expiry warning (within 2 days) --\n");

    for (int i = 0; i < 3; i++)
        if (items[i].kind == PACKAGED &&
            days_between(today, items[i].detail.expiry) <= 2)
            printf("  %s expires %02d/%02d/%d\n",
                   items[i].name,
                   items[i].detail.expiry.day,
                   items[i].detail.expiry.month,
                   items[i].detail.expiry.year);

    /* day summary: revenue per item = (opening stock - stock) x price */
    int revenue[3];
    int opening[3] = {10, 2, 5};
    int idx[3] = {0, 1, 2};

    for (int i = 0; i < 3; i++)
        revenue[i] = (opening[i] - items[i].stock)
                     * items[i].price_paise;

    for (int i = 0; i < 2; i++)
        for (int j = i + 1; j < 3; j++)
            if (revenue[idx[j]] > revenue[idx[i]]) {
                int t = idx[i];
                idx[i] = idx[j];
                idx[j] = t;
            }

    printf("-- day summary by revenue --\n");

    for (int i = 0; i < 3; i++)
        printf("  %-12s Rs %d.%02d\n",
               items[idx[i]].name,
               revenue[idx[i]] / 100,
               revenue[idx[i]] % 100);

    return 0;
}
