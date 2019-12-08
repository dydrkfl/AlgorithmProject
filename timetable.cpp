#include <cstdio>
#include <cstring>
#include "Path.h"
#include "Path_finder.h"

#ifndef CLS
#define CLS     printf("\n\n")
#endif

extern Path_finder* P;
extern int map[26][26];
extern int timetable[31][26][26][2];

void print_timetable(void)
{
    int date;

    printf("Enter date to check the time table (1 ~ 31): ");
    scanf("%d", &date);

    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            if (map[i][j]) {
                printf("From %c to %c | Dep.time: %02d:%02d\n", i + 'A', j + 'A', \
                        timetable[date][i][j][0], timetable[date][i][j][1]);
            }
        }
    }
}
