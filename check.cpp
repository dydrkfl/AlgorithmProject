#include <cstdio>
#include <cstring>
#include "RBtree.h"
#include "Path.h"

extern Tree T;

void check_reservation_print_menu(char* name, int date, char src, char dst)
{
    printf("******************************\n");
    printf("*     Check reservation      *\n");
    printf("*                            *\n");
    printf("* Name: %s", name);
    for (int i = 0; i < 21 - strlen(name); i++)
        printf(" ");
    printf("*\n");
    printf("* Dep. date: %2d              *\n", date);
    printf("* From: %c                    *\n", src);
    printf("* To: %c                      *\n", dst);
    printf("******************************\n");
}

void check_reservation(void)
{
    int r_id;
    printf("Enter your reservation id: ");
    scanf("%d", &r_id);
    getchar();

    Node* customer = T.search(T.root, r_id, NULL);
    if (customer->reserve_id != r_id) {
        printf("Cannot find reservation for given reservation id (%d)\n", r_id);
        return;
    } else {
        check_reservation_print_menu(customer->name, customer->path->dep_time[0], \
                customer->path->source + 'A', customer->path->dest + 'A');

        printf("This is reservation info for given reservation id (%d)\n", r_id);
    }
}
