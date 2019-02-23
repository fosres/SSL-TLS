#include <stdio.h>
#include <time.h>

void delay(unsigned int mseconds)
{
    clock_t goal = mseconds+clock();

    while (goal > clock());

}

int main(void)
{

    int i = 0;

    while ( i < 100 )
    {
        printf("\r");
        
        printf("%d seconds have passed",i);
        
        i++;

        delay(1000);

    }
    return 0;

}

