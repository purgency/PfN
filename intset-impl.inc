/*
Gruppe:
Philipp-Marvin Quach
Camilo Andres Daza Barrios
*/

#include <iostream>
#include <inttypes.h>
#include <assert.h>

#define BITS_FOR_SIZE(SIZE) ((SIZE) * CHAR_BIT)
#define ELEM2SECTION(LOGVAL,X) ((X) >> (LOGVAL))
#define SECTIONMINELEM(S) ((S) << this->logsectionsize)


template <typename Basetype>
IntSet<Basetype>::IntSet(unsigned long maxelem, unsigned long nofelem){

unsigned long idx;

elements = new Basetype[nofelem];

assert(elements != NULL);
nextfree = 0;
logsectionsize = BITS_FOR_SIZE(sizeof(Basetype));
numofsections = ELEM2SECTION(logsectionsize,maxelem) + 1;
sectionstart = new unsigned long[numofsections+1];

assert(sectionstart != NULL);
sectionstart[0] = 0;
for (idx = 1; idx <= numofsections; idx++)
{
sectionstart[idx] = nofelem;
}
maxelement = maxelem;
currentsectionnum = 0;
nofelements = nofelem;
previouselem = ULONG_MAX;

}

template <typename Basetype>
IntSet<Basetype>::~IntSet(){
    delete[] this->elements;
    delete[] this->sectionstart;
    delete this;
}

template <typename Basetype>
void IntSet<Basetype>::add(unsigned long elem){
	assert(this->nextfree < this->nofelements &&
         elem <= this->maxelement &&
         (this->previouselem == ULONG_MAX || this->previouselem < elem));
	while (elem >= SECTIONMINELEM(this->currentsectionnum+1))
	{
	assert(this->currentsectionnum < this->numofsections);
	this->sectionstart[this->currentsectionnum+1] = this->nextfree;
	this->currentsectionnum++;
	}
	assert(SECTIONMINELEM(this->currentsectionnum) <= elem &&
	     elem < SECTIONMINELEM(this->currentsectionnum+1) &&
	     ELEM2SECTION(this->logsectionsize,elem) ==
	       this->currentsectionnum);

	this->elements[this->nextfree++] = (Basetype) elem;
	this->previouselem = elem;
}

template <typename Basetype>
static bool binarysearch_is_member(const Basetype *leftptr,
                                   const Basetype *rightptr,
                                   Basetype elem)
{
  const Basetype *midptr;

  while (leftptr <= rightptr)
  {
    midptr = leftptr + (((unsigned long) (rightptr-leftptr)) >> 1);
    if (elem < *midptr)
    {
      rightptr = midptr-1;
    } else
    {
      if (elem > *midptr)
      {
        leftptr = midptr + 1;
      } else
      {
        return true;
      }
    }
  }
  return false;
}

template <typename Basetype>
bool IntSet<Basetype>::is_member(unsigned long elem) const{
	if (elem <= this->maxelement)
  {
    const unsigned long sectionnum = ELEM2SECTION(this->logsectionsize,elem);

    if (this->sectionstart[sectionnum] < this->sectionstart[sectionnum+1])
    {
      return binarysearch_is_member(this->elements +
                                    this->sectionstart[sectionnum],
                                    this->elements +
                                    this->sectionstart[sectionnum+1] - 1,
                                    (Basetype) elem);
    }
  }
  return false;
}

template <typename Basetype>
static unsigned long binarysearch_smallest_g(const Basetype *leftptr,
                                             const Basetype *rightptr,
                                           	Basetype pos)
{
  const Basetype *midptr, *found = NULL, *leftorig = leftptr;

  assert(leftptr <= rightptr);
  if (pos < *leftptr)
  {
    return 0;
  }
  if (pos > *rightptr)
  {
    return 1UL + (unsigned long) (rightptr - leftptr);
  }
  assert(pos > *leftptr && pos < *rightptr);
  while (leftptr <= rightptr)
  {
    midptr = leftptr + ((unsigned long) (rightptr - leftptr) >> 1);
    if (pos < *midptr)
    {
      rightptr = midptr - 1;
    } else
    {
      found = midptr;
      if (pos > *midptr)
      {
        leftptr = midptr + 1;
      }
      else
        break;
    }
  }
  /* not allowed by exercise! */
  assert(*found != pos);
  assert(found != NULL && found >= leftorig);
  return 1UL + (unsigned long) (found - leftorig);
}

template <typename Basetype>
unsigned long IntSet<Basetype>::number_next_larger(unsigned long pos) const{
  unsigned long sectionnum = ELEM2SECTION(this->logsectionsize,pos),
                result = this->sectionstart[sectionnum];

  assert(pos <= this->maxelement);

  if (pos > this->previouselem)
    return this->nofelements;

  if (this->sectionstart[sectionnum] < this->sectionstart[sectionnum+1])
  {
    result += binarysearch_smallest_g(
                     this->elements + this->sectionstart[sectionnum],
                     this->elements + this->sectionstart[sectionnum+1] - 1,
                     (Basetype) pos);
  }
  return result;
}

template <typename Basetype>
void IntSet<Basetype>::pretty_print(void) const{
	unsigned long idx, sectionnum = 0;

  assert(this->nextfree > 0);
  for (idx = 0; idx < this->nextfree; idx++)
  {
    while (idx >= this->sectionstart[sectionnum+1])
    {
      sectionnum++;
    }
    cout << SECTIONMINELEM(sectionnum) + this->elements[idx] <<
                   (idx < this->nextfree - 1 ? "&" : "\\\\\n");
  }
  for (idx = 0; idx < this->nextfree; idx++)
  {
    cout << this->elements[idx] <<
                   (idx < this->nextfree - 1 ? "&" : "\\\\\n");
  }
  sectionnum = 0;
  for (idx = 0; idx < this->nextfree; idx++)
  {
    while (idx >= this->sectionstart[sectionnum+1])
    {
      sectionnum++;
    }
    cout << sectionnum <<
                   (idx < this->nextfree - 1 ? "&" : "\\\\\n");
  }
  for (idx = 0; idx <= this->numofsections; idx++)
  {
    cout << this->sectionstart[idx] <<
                   (idx < this->numofsections ? "&" : "\\\\\n");
  }
}

template <typename Basetype>
size_t IntSet<Basetype>::
size(unsigned long maxelement,unsigned long nofelements){
	return sizeof(maxelement)*nofelements;
}
