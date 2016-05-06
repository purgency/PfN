/*
Gruppe:
Philipp-Marvin Quach
Camilo Andres Daza Barrios
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
    unsigned long _nofelements;
    unsigned long _insertindex;
};

IntSet *intset_new(unsigned long maxvalue, unsigned long nofelements)
{
    IntSet *intset = (IntSet*) malloc(sizeof(IntSet));

    assert(nofelements <= maxvalue);

    intset->_elements = malloc(nofelements * sizeof(unsigned long));
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
    int i;

    assert(elem < intset->_maxvalue);
    assert(intset->_insertindex < intset->_nofelements); // if !full

    for(i = 0; i < intset->_insertindex ; i++)
    {
        assert(elem > intset->_elements[i]);
    }

    intset->_elements[intset->_insertindex] = elem;
    intset->_insertindex++;
}

bool intset_is_member(const IntSet *intset, unsigned long elem)
{
    unsigned long leftboundary = 0;
    unsigned long rightboundary = intset->_insertindex-1;

    if(elem > intset->_maxvalue) return false;

    while(leftboundary != rightboundary)
    {
        if(intset->_elements[(leftboundary + rightboundary) / 2] >= elem)
        {
            if(intset->_elements[(leftboundary + rightboundary) / 2] == elem) return true;

            rightboundary = (leftboundary + rightboundary) / 2;
        }
        else
        {
            leftboundary = (leftboundary + rightboundary) / 2;
        }
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

}
