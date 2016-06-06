#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

unsigned long file_size(const char *inputfile)
{
  long filesize;
  FILE *fp = fopen(inputfile,"rb");
assert(fp != NULL);
fseek (fp, 0, SEEK_END); /* jump to end of file */ filesize = ftell(fp); /* read current position */ fclose(fp);
assert(filesize >= 0);
return (unsigned long) filesize;

}

char compl(char x)
{
    if(x == 'A')
    {
        return 'T';
    }
    else if(x == 'T')
    {
        return 'A';
    }
    else if(x == 'C')
    {
        return 'G';
    }
    else if(x == 'G')
    {
        return 'C';
    }
}

int main(int argc, char **argv){

	//printf("%lu",file_size("ecoli.seq"));
	unsigned long lon = file_size("ecoli.seq");

	char *buff = malloc(lon*sizeof(char));


	FILE *fp = fopen("ecoli.seq", "r+");

	FILE *fo = fopen("ecoli.seq.rc", "w+");

	fread(buff, sizeof(char),lon,fp);

	int  i;

	int rowlength = strcspn(buff,"\n");

	int j = 0;


    //printf("%lu", lon);

    printf("%d", rowlength);

	for(i = lon; i >= 0; i--)
    {
        if(j != rowlength)
        {

            char comp = compl(buff[i]);
            fputc(comp,fo);
        }
        else{

        }
    }

	return 0;
}



