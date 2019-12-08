#include <cstdio>
#include "RBtree.h"

extern Tree T;

void print_rbtinfo(void)
{
    printf("# of nodes: %d\n", T.num_node);
    printf("Height: %d\n", T.height);
}
