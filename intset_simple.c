/*
Gruppe:
Philipp-Marvin Quach
Camilo Andres Daza Barrios

Bemerkung:
Beim Testen stoppt das Program bei uns in der Methode checkall der Datei
intset_main.c und zwar in Zeile 237/238 bei
"printf("sizeof(Intset)=%zu (%.2f bits/number)\n",
         size,(double) size/arr->nofelements * CHAR_BIT);"
hier sehen wir allerdings nicht inwiefern der Fehler mit unserem Code
zusammenhängt. Eine Warnung gibt an, dass %.2f ein double erwartet,
obwohl dort bereits auf double gecastet wird.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include "intset.h"


struct IntSet {
    unsigned long *_elements;
    unsigned long _maxvalue;
    unsigned long _nofelements; // more like capacity
    unsigned long _insertindex; // insertindex / the actual number of elements
};

IntSet *intset_new(unsigned long maxvalue, unsigned long nofelements)
{
    IntSet *intset = (IntSet*) malloc(sizeof(IntSet));

    assert(nofelements <= maxvalue);
    assert(intset != NULL);

    intset->_elements = malloc(nofelements * sizeof(unsigned long));
    assert(intset->_elements != NULL);

    intset->_maxvalue = maxvalue;
    intset->_insertindex = 0;
    intset->_nofelements = nofelements;

    return intset;
}

size_t intset_size(unsigned long maxvalue, unsigned long nofelements)
{
    assert(nofelements <= maxvalue);

    return (sizeof(IntSet) + nofelements * sizeof(unsigned long));
}

void intset_delete(IntSet *intset)
{
    free(intset->_elements);
    free(intset);
}

void intset_add(IntSet *intset, unsigned long elem)
{
    assert(elem <= intset->_maxvalue);
    assert(intset->_insertindex < intset->_nofelements); // if !full

    intset->_elements[intset->_insertindex] = elem;
    intset->_insertindex++;
}

static bool binarysearch_is_member(const unsigned long *leftptr,
                                   const unsigned long *rightptr,
                                   unsigned long elem)
{
    const unsigned long *midptr;

    while(leftptr <= rightptr)
    {
        midptr = leftptr + (((unsigned long) (rightptr-leftptr)) >> 1);

        if(elem < *midptr)
        {
            rightptr = midptr-1;
        }
        else
        {
            if(elem > *midptr)
            {
                leftptr = midptr + 1;
            }
            else
            {
                return true;
            }
        }
    }

    return false;
}

bool intset_is_member(const IntSet *intset, unsigned long elem)
{
    if(elem <= intset->_maxvalue && intset->_insertindex > 0)
    {
        return binarysearch_is_member(intset->_elements,
                                      intset->_elements+intset->_insertindex-1,
                                      elem);
    }
    return false;
}

unsigned long intset_number_next_larger(const IntSet *intset,
                                        unsigned long pos)
{
    return 0;
}

void intset_pretty(const IntSet *intset)
{
    unsigned long i;

    for(i = 0; i < intset->_insertindex; i++)
    {
        printf("element at position %lu: %lu\n", i, intset->_elements[i]);
    }
}
