#ifndef PATH_H_INCLUDED
#define PATH_H_INCLUDED

typedef struct Path_info{
    int flight_time;
    int flight_path[100];
    int dep_time[3];
    int arr_time[3];
    int source;
    int dest;
}Path;

#endif // PATH_H_INCLUDED
