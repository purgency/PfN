/*
Gruppe:
Philipp-Marvin Quach
Camilo Andres Daza Barrios

Tests funktionieren nicht wirklich, da:
"architecture of input file `intset.o' is incompatible with i386:x86-64 output"
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include "intset.h"
#include <inttypes.h>

unsigned int _d = 65536;;

struct IntSet {
    uint16_t *_elements;
    unsigned long _greatestq;
    unsigned long _maxvalue;
    unsigned long _nofelements; // more like capacity
    unsigned long _insertindex; // insertindex / the actual number of elements
    unsigned long *_sectionstart;
    unsigned long *_sectionlength;
    unsigned long _sectionindex;
};

IntSet *intset_new(unsigned long maxvalue, unsigned long nofelements)
{
    IntSet *intset = (IntSet*) malloc(sizeof(IntSet));
    assert(intset != NULL);

    assert(nofelements <= maxvalue);

    intset->_elements = malloc(nofelements * sizeof(uint16_t));
    assert(intset->_elements != NULL);

    intset->_sectionstart = malloc(((maxvalue/_d)+2) * sizeof(unsigned long));
    assert(intset->_sectionstart != NULL);

    intset->_sectionlength = calloc((maxvalue/_d)+2, sizeof(unsigned long));
    assert(intset->_sectionlength != NULL);

    intset->_greatestq = 0;
    intset->_maxvalue = maxvalue;
    intset->_insertindex = 0;
    intset->_sectionindex = 0;
    intset->_nofelements = nofelements;

    return intset;
}

size_t intset_size(unsigned long maxvalue, unsigned long nofelements)
{
    assert(nofelements <= maxvalue);

    return (sizeof(IntSet) + nofelements * sizeof(uint16_t)+
            sizeof(unsigned long) * 2 * (maxvalue / _d + 1));
}

void intset_delete(IntSet *intset)
{
    free(intset->_elements);
    free(intset->_sectionstart);
    free(intset->_sectionlength);
    free(intset);
}

void intset_add(IntSet *intset, unsigned long elem)
{
    unsigned long q = elem/_d;
    unsigned long now;

    assert(elem <= intset->_maxvalue);
    assert(intset->_insertindex < intset->_nofelements); // if !full
    assert(elem >= intset->_elements[intset->_insertindex]); //proof if the array is sorted

    intset->_elements[intset->_insertindex] = mod(elem/_d);
    intset->_insertindex++;

    intset->_sectionlength[q]++;
    intset->_greatestq = q;

    if (q > intset->_sectionindex)
    {

        for (now = intset->_sectionindex; now <= q; now++){

            intset->_sectionstart[now] = intset->_insertindex;
        }

        intset->_sectionindex = q;
    }
}

static bool binarysearch_is_member(const uint16_t *leftptr,
                                   const uint16_t *rightptr,
                                   unsigned long elem)
{
    const uint16_t *midptr;

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
    unsigned long q = elem/_d;

    if(elem <= intset->_maxvalue && intset->_insertindex > 0)
    {
        return binarysearch_is_member(intset->_elements + intset->_sectionstart[q],
                                      intset->_elements + intset->_sectionstart[q+1]-1,
                                      elem);
    }
    return false;
}

static uint16_t binarysearch_next_larger(const uint16_t *leftptr,
                                   const uint16_t *rightptr,
                                   uint16_t value)
{
    const uint16_t *midptr;
    const uint16_t *rightptrinit = rightptr;
    const uint16_t *leftptrinit = leftptr;

    while(leftptr <= rightptr)
    {
        midptr = leftptr + (((uint16_t) (rightptr-leftptr)) >> 1);

        if(value < *midptr)
        {
            rightptr = midptr-1;
        }
        else
        {
            if(value > *midptr)
            {
                leftptr = midptr + 1;
            }
            else
            {
                if(rightptr != rightptrinit)
                {
                    return *rightptr;
                }
            }
        }
    }

    if(leftptr == leftptrinit && value < *leftptr)
    {
        return *leftptr;
    }
    else
    {
        return 0;
    }
}

unsigned long intset_number_next_larger(const IntSet *intset,
                                        unsigned long value)
{
    unsigned long q = value/_d;
    unsigned long result;

    assert(value <= intset->_maxvalue);

    if(value > _d * intset->_greatestq + intset->_elements[intset->_insertindex-1])
    {
        return intset->_nofelements;
    }

    while(intset->_insertindex > 0)
    {
        assert(q <= intset->_greatestq);

        result = binarysearch_next_larger(intset->_elements + intset->_sectionstart[q],
                                      intset->_elements + intset->_sectionstart[q+1]-1,
                                      value/_d);

        if(result > 0)
        {
            return result + _d * q;
        }

        q++;
    }
}

void intset_pretty(const IntSet *intset)
{
    unsigned long i = 0;
    unsigned long k;
    unsigned long q = 0;
    unsigned long z = sizeof(intset->_sectionstart) / sizeof(intset->_sectionstart[0]);

    for(q = 0; q < z; q++)
    {
        if(i <= intset->_insertindex)
        {
            k = intset->_sectionlength[i];

            while(k > 0)
            {
                printf("element at position %lu: %lu\n", i, _d * q + intset->_elements[i]);
                i++;
                k--;
            }
        }
    }
}
