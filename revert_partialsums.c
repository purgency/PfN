#include <stdio.h>
#include <stdlib.h>

long* revert_partialsums(long *ps, unsigned long n)
{
    int i;

    for(i = 0; i < n; i++)
    {
        ps[n-i] = ps[n-i] - ps[n-i-1];
    }

    return ps;
}

int main(int argc, char **argv)
{
    int i;
    int arg;
    int arg1;
    int arg2;
    long* ps = malloc((argc-1)*sizeof(int));

    if(argc < 3)
    {
        fprintf(stderr, "Error: Please enter a series of whole,"
                            " non-negative, ascending numbers after executable"
                            " (revert_partialsums.x 1 2 3)");
            exit(EXIT_FAILURE);
    }

    for(i = 1; i < argc-1; i++)
    {
        sscanf(argv[i],"%d", &arg1);
        sscanf(argv[i+1],"%d", &arg2);

        if(arg1 > arg2 || arg1 < 0 || arg2 < 0)
        {
            fprintf(stderr, "Error: Please enter a series of whole,"
                            " non-negative, ascending numbers after executable"
                            " (revert_partialsums.x 1 2 3)");
            exit(EXIT_FAILURE);
        }
    }

    for(i = 0; i < argc-1; i++)
    {
        sscanf(argv[i+1],"%d", &arg);
        ps[i] = arg;
    }

    ps = revert_partialsums(ps, argc-1);

    for(i = 0; i < argc-1; i++)
    {
        printf("%ld", ps[i]);
    }

    free(ps);

    return 0;
}
