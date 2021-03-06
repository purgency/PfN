/*
Gruppe:
Philipp-Marvin Quach
Camilo Andres Daza Barrios

Anmerkung: hier habe ich Probleme make test aufzurufen,
da ich grade erst Cygwin auf meinem Windows installiert habe,
um die make Befehle auszuführen aber valgrind noch nicht eingreichtet ist
(valgrind: Kommand nicht gefunden). Ich hoffe das klappt alles so.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int *t1;
int *t2;
int *t3;
int *t1top;
int *t2top;
int *t3top;
int lastto;

int* tnumToTwrtop(int n);
void moveDisk(int from, int to);
int playLegalMoves(int i, int j, int missingMoves, int numMovesPlayed);
void hanoimoves(int n);

int main(int argc, char **argv)
{
    int numDisks;

    if(argc != 2)
    {
        fprintf(stderr, "Error: Please give a parameter for disknumber: hanoi.x [number]");
        exit(EXIT_FAILURE);
    }
    sscanf(argv[1],"%d", &numDisks);

    if(numDisks < 1)
    {
        fprintf(stderr, "Error: number of disks must be 1 or bigger");
        exit(EXIT_FAILURE);
    }

    hanoimoves(numDisks);

    return 0;
}

void hanoimoves(int n)
{
    t1 = (int*)calloc(n+1, sizeof(int));
    t2 = (int*)calloc(n+1, sizeof(int));
    t3 = (int*)calloc(n+1, sizeof(int));

    t1top = &t1[n];
    t2top = &t2[0];
    t3top = &t3[0];

    int numMovesPlayed = 1;
    int total = pow(2,n)-1;

    int i;

    printf("\ninitial configuration:\ntower1\ttower2\ttower3\n");

    for(i = 0; i < n; i++)
    {
        t1[n-i] = i+1;
        printf("%d\t%d\t%d\n", t1[n-i], t2[n-i], t3[n-i]);
    }

    printf("\nmoves to beat the puzzle:\n");

    if(n % 2 == 0)
    {
        printf("(1,3)");
        moveDisk(1, 3);
        lastto = 3;
    }
    else
    {
        printf("(1,2)");
        moveDisk(1, 2);
        lastto = 2;
    }

    if(n % 2 == 0)
    {
        while(numMovesPlayed < total)
        {
            numMovesPlayed = playLegalMoves(1, 3, total, numMovesPlayed);

            numMovesPlayed = playLegalMoves(1, 2, total, numMovesPlayed);

            numMovesPlayed = playLegalMoves(2, 3, total, numMovesPlayed);
        }
    }
    else
    {
        while(numMovesPlayed < total)
        {
            numMovesPlayed = playLegalMoves(1, 2, total, numMovesPlayed);

            numMovesPlayed = playLegalMoves(1, 3, total, numMovesPlayed);

            numMovesPlayed = playLegalMoves(2, 3, total, numMovesPlayed);
        }
    }

    printf("\n\nfinal configuration:\ntower1\ttower2\ttower3\n");

    for(i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\n", t1[n-i], t2[n-i], t3[n-i]);
    }
}

int* tnumToTwrtop(int n)
{
    if(n == 1)
    {
        return t1top;
    }
    else if(n == 2)
    {
        return t2top;
    }
    else
    {
        return t3top;
    }
}

void moveDisk(int from, int to)
{
    *(tnumToTwrtop(to)+1) = *tnumToTwrtop(from);
    *tnumToTwrtop(from) = 0;

    from == 1 ? t1top-- : from == 2 ? t2top-- : t3top--;
    to == 1 ? t1top++ : to == 2 ? t2top++ : t3top++;
}

int playLegalMoves(int i, int j, int missingMoves, int numMovesPlayed)
{
    char oneDirLegal = 1;

    while(numMovesPlayed < missingMoves && oneDirLegal == 1)
    {
        oneDirLegal = 0;

        if(lastto != i && (*tnumToTwrtop(i) < *tnumToTwrtop(j)
           || *tnumToTwrtop(j) == 0) && *tnumToTwrtop(i) != 0)
        {
            moveDisk(i, j);
            printf("(%d,%d)", i, j);
            lastto = j;
            oneDirLegal = 1;
            numMovesPlayed++;
        }
        else if(lastto != j && (*tnumToTwrtop(j) < *tnumToTwrtop(i)
                || *tnumToTwrtop(i) == 0) && *tnumToTwrtop(j) != 0)
        {
            moveDisk(j, i);
            printf("(%d,%d)", j, i);
            lastto = i;
            oneDirLegal = 1;
            numMovesPlayed++;
        }
    }

    return numMovesPlayed;
}
