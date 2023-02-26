#include <stdlib.h>
#include <time.h>

int random(int x,int y)
{
    srand(time(0));
    return rand()%(y-x+1)+x;
}