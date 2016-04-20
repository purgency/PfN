/*
Gruppe:
Philipp-Marvin Quach
Camilo Andres Daza Barrios
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "queue.h"

typedef int Queueelement;

struct Queue {
    Queueelement *queuespace;
    unsigned long  enqueueindex,

                   dequeueindex,
                   queuesize,
                   no_of_elements;
};

Queue *queue_new(unsigned long qsize)
{
    Queue *q;

    if(qsize <= 0)
    {
        fprintf(stderr, "Error: a queue must have a size of 1 or higher");
        exit(EXIT_FAILURE);
    }

    q = (Queue*) malloc(sizeof (Queue));

    q->queuespace = (Queueelement*) malloc(qsize * sizeof(Queueelement));
    q->enqueueindex = 0;
    q->dequeueindex = qsize - 1;
    q->queuesize = qsize;
    q->no_of_elements = q->dequeueindex - q->enqueueindex;

    return q;
}

bool queue_is_empty(const Queue *q)
{
    if(q->no_of_elements == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void queue_double_size(Queue *q)
{
    if(q->no_of_elements != q->queuesize)
    {
        fprintf(stderr, "Error: this can only be done if the queue is full");
        exit(EXIT_FAILURE);
    }

    q->queuespace = realloc(q->queuespace,
                            sizeof(Queueelement) * q->queuesize * 2);

    memcpy(q->queuespace + q->queuesize, q->queuespace,
           q->dequeueindex * sizeof(Queueelement));

    q->enqueueindex = q->queuesize + q->dequeueindex;
    q->queuesize *= 2;

}

void queue_enqueue(Queue *q, Queueelement elem)
{
    if(q->queuesize == q->no_of_elements) queue_double_size(q);

    q->queuespace[q->enqueueindex] = elem;

    q->no_of_elements++;

    // wollte ich erst mit einer neuen modulo funktion machen,
    // wegen unsigned longs aber wahrscheinlich schlecht?
    // q->enqueueindex = mod((q->enqueueindex - 1), q->queuesize);
    q->enqueueindex = q->enqueueindex > 0? q->enqueueindex-1 : q->queuesize-1;
}

Queueelement queue_dequeue(Queue *q)
{
    Queueelement out;

    if(q->no_of_elements <= 0)
    {
        fprintf(stderr, "Error: empty queues shall not return stuff");
        exit(EXIT_FAILURE);
    }

    out = q->queuespace[q->dequeueindex];

    q->dequeueindex = q->dequeueindex > 0? q->dequeueindex-1 : q->queuesize-1;

    q->no_of_elements--;

    return out;
}

void queue_print(const Queue *q)
{
    unsigned long i;
    unsigned long j = 1;
    unsigned long index;

    if(q->no_of_elements > 0)
    {
        for(i =  0; i < q->no_of_elements; i++)
        {
            if(q->dequeueindex-i >= 0)
            {
                index = q->dequeueindex-i;
            }
            else
            {
                index = q->queuesize-j;
                j++;
            }

            printf("%d\n",q->queuespace[index]);
        }
    }
    else
    {
        printf("empty\n");
    }
}

void queue_delete(Queue *q)
{
    free(q->queuespace);
    free(q);
}
