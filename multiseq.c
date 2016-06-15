/*
Gruppe:
Philipp-Marvin Quach
Camilo Andres Daza Barrios
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "multiseq.h"

unsigned long file_size(FILE *fp)
{
    long filesize;
    assert(fp != NULL);
    fseek (fp, 0, SEEK_END); /* jump to end of file */
    filesize = ftell(fp); /* read current position */
    fseek (fp, 0, SEEK_SET); /* jump back to beginning of file */
    assert(filesize >= 0);
    return (unsigned long) filesize;

}

seqStruct *init(FILE *file, int* length)
{
    seqStruct *seq;
    seq = (seqStruct*) malloc(sizeof(*seq));
    assert(seq != NULL);

    unsigned long lon = file_size(file);

    seq->seqlength = malloc(sizeof(int*)*lon);
    assert(seq->seqlength != NULL);
	
    seq->seqbeg = malloc(sizeof(char*)*lon);
    assert(seq->seqbeg != NULL);

    char *buff = malloc(lon*sizeof(char));

    fread(buff, sizeof(char),lon,file);

    int i;
    int initial = 0;
    int len = 0;
    int j = 0;

    for(i=0;i<lon;i++){

        if(buff[i]=='>'){
            initial = i+strcspn(buff+i,"\n")+1;
            len = strcspn(buff+initial,"\n");

            seq->seqbeg[j]=&buff[initial];
            seq->seqlength[j]=len;

            j++;
        }
    }

    *length = j;

    return seq;

}

