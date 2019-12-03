#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include "Path.h"
#include "RBtree.h"

#ifndef CLS
#define CLS     system("clear")
#endif

// implementation of each menu
void make_reservation(void);    // ./reserve.cpp
void print_timetable(void);     // ./timetable.cpp
void cancel_reservation(void);  // ./cancel.cpp
void check_reservation(void);   // ./check.cpp
void print_rbtinfo(Tree T);     // ./rbtinfo.cpp

int main(int argc, const char **argv)
{
    (void)argc;
    (void)argv;

    srand(time(NULL));

    int map[26][26];  // to check if the path is already generated
    memset(map, 0, sizeof(map));

    for (int i = 0; i < 100; i++) {
        int src = rand() % 26;
        int dst = rand() % 26;

        if (src != dst && !map[src][dst] && !map[dst][src]) {
            map[src][dst] = 1;
            map[dst][src] = 1;
        } else {
            i--;
        }
    }

    // path_init(map);

    int timetable[31][26][26][2];   // [date][src][dst][0:hour 1:minute]
    for (int date = 0; date < 31; date++) {
        for (int src = 0; src < 26; src++) {
            for (int dst = 0; dst < 26; dst++) {
                if (map[src][dst] == 1) {
                    int hour = rand() % 24;
                    int minute = rand() % 60;
                    int dep_time[3] = {date, hour, minute};
                    // path_make(src, dst, dep_time);
                }
            }
        }
    }

    Tree T;
    for (int i = 0; i < 500; i++) {
        int date = rand() % 31;
        int src = rand() % 26;
        int dst = rand() % 26;

        if (map[src][dst] == 0) {
            i--;
            continue;
        } else {
            Path newpath = get_path(date, src, dst);
            T.insert("name", newpath);
        }
    }

    int select;
    while (1) {
        printf("******************************\n");
        printf("* Flight Reservation System  *\n");
        printf("*                            *\n");
        printf("* 1. Make reservation        *\n");
        printf("* 2. Print time table        *\n");
        printf("* 3. Cancel reservation      *\n");
        printf("* 4. Check reservation info  *\n");
        printf("* 5. Print RBT info          *\n");
        printf("* 6. Exit                    *\n");
        printf("******************************\n");
        printf("> ");
        scanf("%d", &select);

        switch (select) {
            case 1:
                CLS;
                make_reservation();
                break;
            case 2:
                CLS;
                print_timetable();
                break;
            case 3:
                CLS;
                cancel_reservation();
                break;
            case 4:
                CLS;
                check_reservation();
                break;
            case 5:
                CLS;
                print_rbtinfo(T);
                break;
            case 6:
                return 0;
                break;
            default:
                printf("Invalid input\n");
        }

        CLS;
    }
    return 0;
}
