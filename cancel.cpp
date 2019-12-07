#include <cstdio>
#include "RBtree.h"

extern Tree T;

void cancel_reservation_print_menu(char* name, int date, char src, char dst)
{
    printf("******************************\n");
    printf("*     Cancel reservation     *\n");
    printf("*                            *\n");
    printf("* Name: %s", name);
    for (int i = 0; i < 21 - strlen(name); i++)
        printf(" ");
    printf("\n");
    printf("* Dep. date: %2d              *\n", date);
    printf("* From: %c                    *\n", src);
    printf("* To: %c                      *\n", dst);
    printf("******************************\n");
}

void cancel_reservation()
{
    int r_id;

    printf("Enter your reservation id: ");
    scanf("%d", &r_id);
    getchar();
    printf("\n");

    Node* customer = T.search(T, r_id, NULL, 0);
    if (customer->reserve_id != r_id) {
        printf("Cannot find reservation for given reservation id (%d)\n", r_id);
        return;
    } else {
        cancel_reservation_print_menu(customer->name, customer->path.dep_time[0], \
                customer->path.source + 'A', customer->path.dest + 'A');
        printf("Check your reservation info.\n");
        printf("Cancel this reservation? (y/n)");
        scanf("%c", &sel);
        getchar();

        if (sel == 'y') {
            T.remove(r_id);
            printf("Successfully cancelled reservation (Reservation ID: %d)\n", r_id);
        }
    }
}

int main(void)
{
    cancel_reservation();
}
