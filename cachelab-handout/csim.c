#include "cachelab.h"
#include <unistd.h>

int main(int argc, char *argv[])
{
    int s, e, b;
    int opt;
    while ((opt = getopt(argc, argv, "s:e:b:")) != -1)
    {
        switch (opt)
        {
            case 's':
                s = atoi(optarg);
                break;
            case 'e':
                e = atoi(optarg);
                break;
            case 'b':
                b =  atoi(optarg);
                break;
            default:
                printf("wrong argument\n");
                exit(0);
        }
    }
    
    printf("s = %d, e = %d, b = %d\n", s,e,b);
    
    printSummary(0, 0, 0);
    return 0;
}
