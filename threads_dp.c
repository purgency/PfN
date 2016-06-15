/*
Gruppe:
Philipp-Marvin Quach
Camilo Andres Daza Barrios
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include "multiseq.h"
#include "bestkvals_generic.h"
#include "unit_edist.h"

typedef struct distStruct
{
    unsigned long dist;
    int p;
    int q;
} distStruct;

typedef struct arg_struct {
    int arg1;
    int arg2;
    int arg3;
    Evalfunction arg4;
    seqStruct *arg5;
    BestKVals *arg6;
} arg_struct;


int bkv_cmp(const void *a, const void *b)
{
    const distStruct *dSa = a;
    const distStruct *dSb = b;

    if(dSa->dist < dSb->dist)
    {
        return -1;
    }
    else if(dSa->dist > dSb->dist)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int eval_seqrange(int i, int j, int n, Evalfunction evalf,
 seqStruct *seq, BestKVals *bkv)
{
    assert(i >= 0 && j >= i && n-1 >= j);

    int p;
    for(p = i; p <= j; p++)
    {
        int q;
        for(q = p + 1; q <= n - 1; q++)
        {

			distStruct *dS;
			dS = malloc(sizeof(*dS));
			dS->dist = evalf(seq->seqbeg[p],seq->seqlength[p],
			seq->seqbeg[q],seq->seqlength[q]);
			dS->p = p;
			dS->q = q;
			best_k_vals_insert(bkv, dS);

        }
    }
    return 1;
}


int main(int argc, char **argv)
{
    int k;
    int t;
    int length; // = 175 for sw175.fna
    FILE *file;
    seqStruct *seq;
    BestKVals *bkv;
    pthread_t *threads;
	
	if(argc != 4)
    {
        fprintf(stderr, "Executionformat: threads_dp.x <k> <t> <Dateiname>");
        exit(EXIT_FAILURE);
    }

    sscanf(argv[1],"%d",&k);
    sscanf(argv[2],"%d",&t);

    if(k < 1 || t < 1)
    {
        fprintf(stderr, 
		"Error: number of pairs, k, and number of threads, t, must be 1 or greater");
        exit(EXIT_FAILURE);
    }

    file = fopen(argv[3],"r");

    seq = init(file, &length);

    bkv = best_k_vals_new(k, bkv_cmp, sizeof(char));

    threads = malloc(k * sizeof(pthread_t));
	assert(threads != NULL);

    unsigned long teeth = length/t;
    int r = 0;

    int i;
    for(i = 0; i < t; i++)
    {
        if (i == t-1) r = length % t;

        pthread_t thr;
        threads[i] = thr;

        struct arg_struct args;
        args.arg1 = teeth * (i-1);
        args.arg2 = teeth * (i-1) + teeth-1+r;
        args.arg3 = length;
        args.arg4 = eval_unit_edist;
        args.arg5 = seq;
        args.arg6 = bkv;

        pthread_create(&thr, NULL, eval_seqrange, (void *) &args);

    }

    for(i = 0; i < t; i++)
    {
        pthread_join(threads[i], NULL);
    }

    for(i = 0; i < k; i++)
    {
        const distStruct *dS = best_k_vals_next(bkv);
        printf("%*d %*d %lu\n", 3, dS->p, 3, dS->q, dS->dist);
    }

    free(threads);
    free(seq->seqbeg);
    free(seq->seqlength);
    free(seq);
    best_k_vals_delete(bkv);

    return 0;
}




