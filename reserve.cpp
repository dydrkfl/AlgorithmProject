#include <cstdio>
#include <cstring>
#include <cstdlib>

#ifndef CLS
//#define CLS     system("clear")
#define CLS     printf("\n\n")
#endif

void make_reservation_print_menu(char* name, int date, char src, char dst)
{
    printf("******************************\n");
    printf("*      Make reservation      *\n");
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

void make_reservation(void)
{
    char name[10] = {0, };
    int date = 1;
    char src = ' ';
    char dst = ' ';

    make_reservation_print_menu(name, date, src, dst);
    printf("Enter your name (Up to 9 characters): ");
    fgets(name, 10, stdin);
    if (name[strlen(name) - 1] == '\n') name[strlen(name) - 1] = 0;
    CLS;

    make_reservation_print_menu(name, date, src, dst);
    printf("Enter departure date (1 ~ 31): ");
    scanf("%d", &date);
    CLS;

    make_reservation_print_menu(name, date, src, dst);
    printf("Enter source city (A ~ Z): ");
    scanf("\n%c", &src);
    CLS;

    make_reservation_print_menu(name, date, src, dst);
    printf("Enter destination city (A ~ Z): ");
    scanf("\n%c", &dst);
    getchar();
    CLS;

    make_reservation_print_menu(name, date, src, dst);
    printf("Your reservation id is %d\n", 123);

    Path newpath;
    // initialize newpath
    T.insert(name, newpath);

    return;
}

int main(void)
{
    make_reservation();
}
