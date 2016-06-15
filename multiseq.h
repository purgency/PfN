/*
Gruppe:
Philipp-Marvin Quach
Camilo Andres Daza Barrios
*/

#include <stdio.h>

typedef struct seqStruct
{
    const unsigned char **seqbeg;
    unsigned long *seqlength;
} seqStruct;

struct seqStruct *init(FILE *file, int* length);
