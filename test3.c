#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <wait.h>

int main()
{
    int test = 50;

    int P = fork();
    for (int i = 0; i < 50; i++)
    {
        if (P > 0)
        {
            test = test + 1;
            printf("parent : %d\n", test);
        }
        else if (P == 0)
        {
            test = test - 1;
            printf("child : %d\n", test);
        }
        else
        {
            printf("error\n");
        }
    }
}