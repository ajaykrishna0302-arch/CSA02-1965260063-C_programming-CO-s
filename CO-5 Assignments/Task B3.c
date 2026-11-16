#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct { int id; char group[4]; int age; } Donor;

static double ms_since(clock_t t0) { return 1000.0 * (clock() - t0) / CLOCKS_PER_SEC; }

int main(void)
{
    /* B3.1 - correctness on 10 records, both formats */
    Donor sample[10];
    for (int i = 0; i < 10; i++) {
        sample[i].id = 7001 + i;
        strcpy(sample[i].group, i % 2 ? "A+" : "O-");
        sample[i].age = 20 + i;
    }
    FILE *ft = tmpfile(), *fb = tmpfile();
    for (int i = 0; i < 10; i++)
        fprintf(ft, "%d %s %d\n", sample[i].id, sample[i].group, sample[i].age);
    fwrite(sample, sizeof(Donor), 10, fb);
    rewind(ft); rewind(fb);
    Donor rt, rb; int identical = 1;
    for (int i = 0; i < 10; i++) {
        fscanf(ft, "%d %3s %d", &rt.id, rt.group, &rt.age);
        fread(&rb, sizeof(Donor), 1, fb);
        if (rt.id != rb.id || rt.age != rb.age || strcmp(rt.group, rb.group) != 0)
            identical = 0;
    }
    printf("10-record round trip: text and binary both %s\n",
           identical ? "identical" : "MISMATCH");

    /* B3.2 - size and time at three scales */
    long sizes[] = {1000, 10000, 100000};
    for (int s = 0; s < 3; s++) {
        long n = sizes[s];
        FILE *t = tmpfile(), *b = tmpfile();
        clock_t t0 = clock();
        for (long i = 0; i < n; i++) fprintf(t, "%ld %s %d\n", 7001 + i, "O+", 25);
        double tw = ms_since(t0);
        t0 = clock();
        Donor d = {7001, "O+", 25};
        for (long i = 0; i < n; i++) fwrite(&d, sizeof d, 1, b);
        double bw = ms_since(t0);
        printf("n = %6ld: text %8ld bytes in %6.1f ms | binary %8ld bytes in %5.1f ms\n",
               n, ftell(t), tw, ftell(b), bw);
        fclose(t); fclose(b);
    }

    /* B3.3 - update one record: fseek in binary vs rewriting the text file */
    FILE *b = tmpfile();
    Donor d = {7001, "O+", 25};
    for (long i = 0; i < 100000; i++) fwrite(&d, sizeof d, 1, b);
    clock_t t0 = clock();
    Donor upd = {7001, "AB-", 31};
    fseek(b, 50000 * sizeof(Donor), SEEK_SET);
    fwrite(&upd, sizeof upd, 1, b);
    printf("binary in-place update of record 50000: %.3f ms\n", ms_since(t0));
    fclose(b);
    return 0;
}