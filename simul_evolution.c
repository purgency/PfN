#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>



int main(int argc, char **argv){

	if(argc < 6 || argc >=8)
    {
        fprintf(stderr, "Error: Please give the correct number of parameters");
        exit(EXIT_FAILURE);
    }



	int na;
	double pa;
	int nb;
	double pb;
	int maxsteps;
	int timer;
	double rand1;
	double rand2;

	FILE *file;

	sscanf(argv[1],"%d",&na);
	sscanf(argv[2],"%lf",&pa);
	sscanf(argv[3],"%d",&nb);
	sscanf(argv[4],"%lf",&pb);
	sscanf(argv[5],"%d",&maxsteps);

	timer = 0;


	int naVar = na;
	int nbVar = nb;
	int i;

	srand(time(NULL));

	if(argc == 7){
    	file = fopen(argv[6],"w+");
    	fprintf(file,"%d\t%d\t%d\n",timer,na,nb);
    }

	while(timer != maxsteps && na>0 && nb>0){
		for(i = 0;i<=na && nbVar>0;i++){
			rand1 = (double)rand() / (double)RAND_MAX;
			rand2 = (double)rand() / (double)RAND_MAX;
			if(rand1<=pa){
				naVar++;
				if(rand2>0.5 && naVar>0){
					naVar--;
				}
				else if(rand2<=0.5 && nbVar>0){
					nbVar--;
				}
			}
		}

		for(i = 0;i<=nb && naVar>0;i++){
			rand1 = (double)rand() / (double)RAND_MAX;
			rand2 = (double)rand() / (double)RAND_MAX;
			if(rand1<=pb){
				nbVar++;
				if(rand2>0.5 && naVar>0){
					naVar--;
				}
				else if(rand2<=0.5 && nbVar>0){
					nbVar--;
				}
			}

		}

		na = naVar;
		nb = nbVar;
		timer++;
		if(argc == 7){
			fprintf(file,"%d\t%d\t%d\n",timer,na,nb);
		}
	}

	if(timer == maxsteps)
    {
        printf("simulation stopped after %d steps (A:%d,B:%d)", timer, na, nb);
    }
    else if(na <= 0)
    {
        printf("fixed:A\tsteps:%d", timer);
    }
    else // nb <= 0
    {
        printf("fixed:B\tsteps:%d", timer);
    }

    if(argc == 7){
    	fclose(file);
    }

	return 0;
}
