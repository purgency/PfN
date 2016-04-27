/*
Gruppe:
Philipp-Marvin Quach
Camilo Andres Daza Barrios
*/

#include<stdlib.h>
#include"memmanage.h"


#define MEM_MAN_ALLOC(ST, P, T, N) mem_man_alloc(ST,__FILE__,__LINE__,P,sizeof(T),N)
#define MEM_MAN_DELETE_PTR(ST,P) mem_man_delete_ptr(ST,__FILE__,__LINE__,P)
