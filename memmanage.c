/*
Gruppe:
Philipp-Marvin Quach
Camilo Andres Daza Barrios
*/

#include <stdio.h>
#include <stdlib.h>
#include "memmanage.h"

struct MMspaceblock
{
    void *_block;
    unsigned long _size;
    unsigned long _number;
    unsigned long _line;
    char *_file;
};

struct MMspacetable
{
    MMspaceblock *_sb;
    unsigned long _capacity;
};

MMspacetable* mem_man_new(unsigned long numberofblocks)
{
    MMspacetable *st;
    int i;

    st = malloc(sizeof(MMspacetable));
    st->_capacity = numberofblocks;
    st->_sb = malloc(numberofblocks * sizeof(MMspaceblock));

    for(i = 0; i < numberofblocks; i++)
    {
        st->_sb[i]._block = NULL;
        st->_sb[i]._file = NULL;
        st->_sb[i]._line = 0;
        st->_sb[i]._number = 0;
        st->_sb[i]._size = 0;
    }

    return st;
}

void *mem_man_alloc(MMspacetable *st, char *file, unsigned long line,
                     void *ptr, unsigned long size, unsigned long number)
{
    unsigned long index;

    for(index = 0; index < st->_capacity && st->_sb[index]._block != ptr;
     index++);

    if(index == st->_capacity)
    {
        fprintf(stderr, "The spacetable is already full");
        exit(EXIT_FAILURE);
    }

    st->_sb[index]._block = realloc(ptr, size * number);
    st->_sb[index]._size = size;
    st->_sb[index]._number = number;
    st->_sb[index]._line = line;
    st->_sb[index]._file = file;

    return &(st->_sb[index]);
}

void mem_man_delete_ptr(MMspacetable *st, char *file, unsigned long line,
                         void *ptr)
{
    unsigned long index;

    if(1==2)
    {
        //keine Ahnung was man mit den Parameten machen soll
        //lässt sich jedenfalls nicht kompilieren ohne Verwendung
        printf("%s%lu", file, line);
    }

    for(index = 0; index < st->_capacity && st->_sb[index]._block != ptr;
     index++);

    if(ptr == NULL)
    {
        fprintf(stderr, "There's no pointer that could be deleted");
        exit(EXIT_FAILURE);
    }

    free(ptr);

    st->_sb[index]._block = NULL;
    st->_sb[index]._size = 0;
    st->_sb[index]._number = 0;
    st->_sb[index]._line = 0;
    free(st->_sb[index]._file);
    st->_sb[index]._file = NULL;
}

void mem_man_info(const MMspacetable *st)
{
    unsigned long index;

    printf("Print out internal memory table:\n");

    for(index = 0; index < st->_capacity; index++)
    {
        if(st->_sb[index]._block != NULL)
        {
            printf("# active block %lu: allocated in file \"%s\", line %lu\n",
                    index, st->_sb[index]._file, st->_sb[index]._line);
        }
    }
}

void mem_man_check(const MMspacetable *st)
{
    unsigned long index;

    if(st == NULL)
    {
        fprintf(stderr, "There's no spacetable that could be checked");
        exit(EXIT_FAILURE);
    }

    for(index = 0; index < st->_capacity; index++)
    {
        if(st->_sb[index]._block != NULL)
        {
            fprintf(stderr, "space leak: main memory for block %lu not freed %lu"
                     "cells of size %lu\nallocated: file \"%s\"" , index,
                     st->_sb[index]._number, st->_sb[index]._size,
                     st->_sb[index]._file);
            exit(EXIT_FAILURE);
        }
    }

}

void mem_man_delete(MMspacetable *st)
{
    unsigned long index;

    if(st == NULL)
    {
        fprintf(stderr, "There's no spacetable that could be deleted");
        exit(EXIT_FAILURE);
    }

    for(index = 0; index < st->_capacity; index++)
    {
        free(st->_sb->_block);
        free(st->_sb->_file);
    }
    free(st->_sb);
    free(st);
}
