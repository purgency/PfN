#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

	if(argc != 2)
    {
        fprintf(stderr, "Executionformat: revcomp.x <filename>");
        exit(EXIT_FAILURE);
    }

	
	
	unsigned long lon = file_size(argv[1]);

	char *buff = malloc(lon*sizeof(char));

	assert(buff != NULL);

    FILE *fp = fopen(argv[1], "r+");

	FILE *fo = fopen(strcat(argv[1],".rc"), "w+");

	fread(buff, sizeof(char),lon,fp);

	int  i;

	int j = 0;
	int h;

    for(i = lon-1, h = 0; i >= 0; i--, h++)
    {
        if(buff[h] == '\n')
        {
            fputc('\n',fo);
            i++;
        }
        else
        {
            if(buff[i] == '\n')
            {
                i--;
            }

            char comp = compl(buff[i]);
            fputc(comp,fo);
        }
    }

    fclose(fo);
    fclose(fp);
    free(buff);

	return 0;
}
