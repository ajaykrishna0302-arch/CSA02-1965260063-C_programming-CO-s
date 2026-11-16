
#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100

struct date {
    int day, month, year;
};

struct pressure {
    int systolic, diastolic;
};

struct patient {
    char name[32];
    int age;
    char phone[11];          /* 10 digits + '\0' */
    struct pressure bp;      /* blood pressure, e.g. 120/80 */
    struct date visit;
};

int addPatient(struct patient list[], int count,
               const char *name, int age, const char *phone,
               int sys, int dia, struct date d)
{
    if (count >= MAX_PATIENTS) return -1;  /* limit check */

    strncpy(list[count].name, name, 31);
    list[count].name[31] = '\0';

    list[count].age = age;

    strncpy(list[count].phone, phone, 10);
    list[count].phone[10] = '\0';

    list[count].bp.systolic = sys;
    list[count].bp.diastolic = dia;

    list[count].visit = d;

    return count + 1;
}

int main(void)
{
    struct patient register_[MAX_PATIENTS];
    int count = 0;

    count = addPatient(register_, count, "Amutha", 67, "9840012345", 120, 80,
                       (struct date){14, 11, 2026});

    count = addPatient(register_, count, "Selvam", 45, "9884012345", 140, 95,
                       (struct date){14, 11, 2026});

    for (int i = 0; i < count; i++)
    {
        printf("%s, age %d, ph %s, BP %d/%d, visited %02d/%02d/%d\n",
               register_[i].name, register_[i].age, register_[i].phone,
               register_[i].bp.systolic, register_[i].bp.diastolic,
               register_[i].visit.day, register_[i].visit.month,
               register_[i].visit.year);
    }

    printf("sizeof(struct patient) = %zu bytes\n", sizeof(struct patient));

    return 0;
}
