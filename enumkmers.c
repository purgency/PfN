#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//1. get number m of letters in argv[1]
//2. get number nposbl of possible mixtures (formel aus stochastik)
//3. for i = 0 to i = nposbl do: write i transformed* into line i
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
        while(x >= (int) (pow(m,i)+0.5))
        {
            x -= (int) (pow(m,i)+0.5);
            y++;
        }

        printf("%c",str[y]);
    }

    printf("\n");
}

int main(int argc,char **argv)
{
    if(argc != 3)
    {
        fprintf(stderr, "Executionformat: enumkmers.x <letters> <num>");
        exit(EXIT_FAILURE);
    }

    str = argv[1];
    sscanf(argv[2],"%d", &n);
    m = strlen(argv[1]);
    int posbl = (int) (pow(m,n) +0.5); //+0.5 for correct rounding
    int i;

    for(i = 0; i < posbl; i++)
    {
        printNumAsStr(i);
    }

    return 0;
}


