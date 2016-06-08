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

#define MAXARRAYELEMENTS 1000000
#define MAXSORTVALUE 1000U

int main(int argc, char **argv)
{
    unsigned long nofelements;

    sscanf(argv[1],"%lu", &nofelements);

    unsigned int *values = malloc(sizeof(unsigned int) * nofelements);
    assert(values != NULL);

    unsigned int *valuesb = malloc(sizeof(unsigned int) * nofelements);
    assert(valuesb != NULL);

    unsigned long i;

    if(argc != 2)
    {
        fprintf(stderr, "Executionformat: sorting_main.x <num>");
        exit(EXIT_FAILURE);
    }

    if(nofelements <= 0 || nofelements > MAXARRAYELEMENTS)
    {
        fprintf(stderr, "number must be > 0 and <= 1000000");
        exit(EXIT_FAILURE);
    }

    srand48(42349421);

    printf("# Zweifache Erzeugung der Zufallszahlen...\n");
    for (i = 0; i < nofelements; i++)
    {
        values[i] = valuesb[i] = (unsigned int) (drand48() * (MAXSORTVALUE+1));
    }

    printf("# Sortieren der Zufallszahlen mit Insertion Sort...\n");
    insertionsort(values, nofelements);

    printf("# Sortieren der Zufallszahlen mit Counting Sort...\n");
    countingsort(valuesb, nofelements);

    printf("# Vergleich der Arrays...\n");
    for(i = 0; i < nofelements; i++)
    {
        if(values[i] != valuesb[i])
        {
            fprintf(stderr, "# Arrays NICHT identisch!");
            exit(EXIT_FAILURE);
        }
    }

    printf("# Arrays identisch!\n");

    printf("Kleinste erzeugte Zufallszahl: %d\n", values[0]);
    printf("Groesste erzeugte Zufallszahl: %d\n", values[nofelements-1]);

    int fieldwith = log10(MAXSORTVALUE);

    printf("Dezentilverteilung:\n");
    printf("%*s|#Werte\n",fieldwith*2+2, "Dezentil");

    unsigned long tenth = (values[nofelements-1]-values[0]+1)/10;
    int r = 0;

    unsigned long idx = 0;

    for(i = 1; i <= 10; i++)
    {
        if (i == 10) r = (values[nofelements-1]-values[0]+1)%10;
        unsigned long start = values[0]+tenth * (i-1);
        unsigned long end = values[0]+tenth * (i-1) + tenth-1+r;
        printf("%*lu-%*lu|", fieldwith, start, fieldwith+1, end);

        unsigned int counter = 0;
        while(values[idx] <= end)
        {
            counter++;
            idx++;
        }
        printf("%u\n", counter);
    }

    free(values);
    free(valuesb);

    return 0;
}
