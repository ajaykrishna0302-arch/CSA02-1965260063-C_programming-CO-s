#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { int id; char group[4]; } Donor;
typedef struct { Donor *data; int size, capacity; } DonorList;

/* Appends a donor, doubling the capacity when the list is full.
   Returns 1 on success, 0 if memory could not be allocated. */
int add_donor(DonorList *list, int id, const char *group)
{
    if (list->size == list->capacity) {
        int newcap = list->capacity == 0 ? 2 : list->capacity * 2;
        Donor *p = realloc(list->data, newcap * sizeof(Donor));
        if (p == NULL) return 0;   /* list->data is untouched - nothing lost */
        list->data = p;
        list->capacity = newcap;
    }
    list->data[list->size].id = id;
    strncpy(list->data[list->size].group, group, 3);
    list->data[list->size].group[3] = '\0';
    list->size++;
    return 1;
}

int main(void)
{
    DonorList list = {NULL, 0, 0};
    const char *groups[] = {"O+", "A+", "B-", "AB+", "O-"};
    for (int i = 0; i < 5; i++) {
        add_donor(&list, 7001 + i, groups[i]);
        printf("added %d (%s): size = %d, capacity = %d\n",
               list.data[i].id, list.data[i].group, list.size, list.capacity);
    }

    /* district scale: 100,000 donors in the same growable list */
    for (int i = 5; i < 100000; i++)
        add_donor(&list, 7001 + i, groups[i % 5]);
    printf("at 100000 donors: size = %d, capacity = %d, memory = %zu bytes (%.1f MB)\n",
           list.size, list.capacity,
           (size_t)list.capacity * sizeof(Donor),
           list.capacity * sizeof(Donor) / 1048576.0);
    free(list.data);
    return 0;
}