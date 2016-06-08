/*
Gruppe:
Philipp-Marvin Quach
Camilo Andres Daza Barrios
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "sorting.h"

void insertionsort(unsigned int *values, unsigned long nofelements)
{
    unsigned long j;
    for(j = 1; j <= nofelements - 1; j++)
    {
        unsigned int key = values[j];
        int i = j - 1;
        while(i >= 0 && values[i] > key)
        {
            values[i+1] = values[i];
            i = i - 1;
        }
        values[i+1] = key;
    }
}

void countingsort(unsigned int *values, unsigned long nofelements)
{
    unsigned int k = 0;
    unsigned long i;
    for(i = 0; i < nofelements; i++)
    {
        if(values[i] > k)
        {
            k = values[i];
        }
    }

    unsigned int *B = malloc(sizeof(unsigned int) * nofelements);
    assert(B != NULL);

    unsigned int *C = malloc(sizeof(unsigned int) * (k+1));
    assert(C != NULL);

    for(i = 0; i <= k; i++)
    {
        C[i] = 0;
    }

    for(i = 0; i < nofelements; i++)
    {
        C[values[i]] += 1;
    }

    for(i = 1; i <= k; i++)
    {
        C[i] = C[i] + C[i-1];
    }

    for(i = nofelements-1; i >= 0; i--)
    {
        B[C[values[i]]-1] = values[i];
        C[values[i]] = C[values[i]]-1;
        if(i == 0) break;
    }

    for(i = 0; i < nofelements; i++)
    {
        values[i] = B[i];
    }

    free(C);
    free(B);
}
