#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "int_conv.h"

//1. get number m of letters in argv[1]
//2. get number x of possible mixtures (formel aus stochastik)
//3. for i = 0 to i = x do: write i transformed* into line i
//
//* A = 0, B = 1... = n-1. BA = (B*n)+0, BB = (B*n)+1... BAA =

int n;
int m;
char* str;

void printNumAsStr(int x)
{
    int i;

    for(i = n-1; i >= 0; i--)
    {
        int y = 0;
        while(x >= pow(m,i))
        {
            x -= pow(m,i);
            y++;
        }

        printf("%c",str[y]);
    }

    printf("\n");
}

int main(int argc,char **argv)
{
    str = argv[1];
    n = get_int(argv[2]);
    m = strlen(argv[1]);
    int posbl = pow(m,n);
    int i;

    for(i = 0; i < posbl; i++)
    {
        printNumAsStr(i);
    }

    int res = get_int("1234");

    return res;
}


