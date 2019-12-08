#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include "Path.h"
#include "RBtree.h"
#include "Path_finder.h"

#ifndef CLS
#define CLS     system("clear")
#endif

// implementation of each menu
void make_reservation(void);    // ./reserve.cpp
void print_timetable(void);     // ./timetable.cpp
void cancel_reservation(void);  // ./cancel.cpp
void check_reservation(void);   // ./check.cpp
void print_rbtinfo(void);     // ./rbtinfo.cpp

/* default data structure,  RBT T */
Tree T;

/* default data structure, Path_finder* P */
Path_finder* P;

int main(int argc, const char **argv)
{

    int timetable[31][26][26][2];   // [date][src][dst][0:hour 1:minute]
    int map[26][26];  // to check if the path is already generated


    (void)argc;
    (void)argv;

    srand(time(NULL));

    memset(map, 0, sizeof(map));

    int X_cor[26];
    int Y_cor[26];
	/* set cities' coordinate */
    for(int i =0; i<26;i++){
        X_cor[i] = rand()%6001-3000;
        Y_cor[i] = rand()%6001-3000;
    }

	/* randomly generate 100 distinct direct paths 
	*  map include the flight time information between two cities.
	*/
    for (int i = 0; i < 100; i++) {
        int src = rand() % 26;
        int dst = rand() % 26;

        if (src != dst && !map[src][dst] && !map[dst][src]) {
        	/* get distance between two cities */
            map[src][dst] = (int)sqrt((X_cor[dst]-X_cor[src])*(X_cor[dst]-X_cor[src])+(Y_cor[dst]-Y_cor[src])*(Y_cor[dst]-Y_cor[src]));
            map[dst][src] = (int)sqrt((X_cor[dst]-X_cor[src])*(X_cor[dst]-X_cor[src])+(Y_cor[dst]-Y_cor[src])*(Y_cor[dst]-Y_cor[src]));
            /* get the flight time - unit : minutes [ distance / (500km/hour = (25/3)km/minutes )*/
			map[src][dst] = (int)(map[src][dst]*3/25);
            map[dst][src] = (int)(map[dst][src]*3/25);
        } else {
            i--;
        }
    }
	
	/* randomly generate departure time table */
    for (int date = 0; date < 31; date++) {
        for (int src = 0; src < 26; src++) {
            for (int dst = 0; dst < 26; dst++) {
                if (map[src][dst] != 0) {
                    int hour = rand() % 24;
                    int minute = rand() % 60;
                    timetable[date][src][dst][0] = hour;
                    timetable[date][src][dst][1] = minute;
                }

            }
        }
    }
	
	/* path finder object p */
    P = new Path_finder(timetable, map);
    
    char rand_name[5];
    rand_name[4] = '\0';

    for (int i = 0; i < 500; i++) {
        int date = rand() % 31;
        int src = rand() % 26;
        int dst = rand() % 26;

        if (map[src][dst] == 0) {
            i--;
            continue;
        } else {
        	/* make random name [ length = 4 ] */
        	rand_name[0] = rand() % 26 + 65;
        	for(int j = 1; j<4; j++)
        		rand_name[j] = rand() % 26 + 97;
        	
            printf("%d %d %d\n", date, src, dst);
            printf("i: %d\n", i);
            Path *newpath = P->get_path(date, src, dst);
            /* flight_time == 0 -> there is no path between src and dst */
            if(newpath->flight_time!=0)
                T.insert(rand_name, newpath);
            else
            	delete(newpath);
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
        getchar();

        switch (select) {
            case 1:
                CLS;
                make_reservation();
                break;
            case 2:
                CLS;
                //print_timetable();
                break;
            case 3:
                CLS;
                cancel_reservation();
                break;
            case 4:
                CLS;
                //check_reservation();
                break;
            case 5:
                CLS;
                print_rbtinfo();
                break;
            case 6:
                return 0;
                break;
            default:
                printf("Invalid input\n");
        }
    }
    return 0;
}
