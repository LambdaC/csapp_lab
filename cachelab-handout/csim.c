#include "cachelab.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <math.h>

struct Line {
   unsigned char bit;
   unsigned long tag;
   unsigned long time_stamp;
};

struct Set{
   int line_nums;
   struct Line *lines;
};

void exit_exe();

int main(int argc, char *argv[])
{
    int s, E, b;
    int p_flag = 0;
    char *file_name = NULL;
    int opt;
    unsigned long time_stamp = 0;
    while ((opt = getopt(argc, argv, "s:E:b:t:v")) != -1)
    {
        switch (opt)
        {
            case 's':
                s = atoi(optarg);
                break;
            case 'E':
                E = atoi(optarg);
                break;
            case 'b':
                b =  atoi(optarg);
                break;
            case 't':
                file_name = optarg;
                break;
            case 'v':
                p_flag = 1;
                break;
            default:
                exit_exe();
        }
    }
    
    //printf("s = %d, E = %d, b = %d, t = %s\n", s,E,b, file_name);

    if (s == 0 || E == 0 || b == 0 || file_name == NULL)
    {
        exit_exe();    
    }

    // open trace file
    FILE *p_file;
    if(!(p_file = fopen(file_name, "r")))
    {
        printf("%s: No such file\n", file_name);
        exit(0);
    }

    // init caches
    const int S = pow(2,s);
    struct Set *sets = malloc(sizeof(struct Set) * S);
    for(int i = 0; i < S; i++)
    {
       sets[i].line_nums = E;
       struct Line *lines = malloc(sizeof(struct Line) * E);
       for(int j = 0; j < E; j++)
       {
           lines[j].bit = 0;
           lines[j].time_stamp = 0;
       }
       sets[i].lines = lines;
    }

    //printf("%d\n", sets[0].line_nums); 

    char op[2];
    unsigned long address;
    char place_holder;
    int size;

    int hit_count = 0, miss_count = 0, evict_count = 0; 

    while(fscanf(p_file, "%s %lx %c %d", op, &address, &place_holder, &size) > 0)
    {
        char c = op[0];
        if (c != 'L' && c != 'S' && c != 'M')
            continue;
        if(p_flag)
            printf("%s %lx,%d ", op, address, size);

        int loop = c == 'M'?2:1;
        while(loop--){
        unsigned long flag = ~(0UL);
        unsigned s_index = ((address >> b) & (~(flag << s))) % S;
        unsigned long tag = address >> (s + b);
        struct Set *set = &(sets[s_index]);

        // check if can hit
        unsigned char miss_flag = 1;
        for(int i = 0; i < E; i++)
        {
           struct Line *line = &(set->lines[i]);
           if(line->bit == 1 && line->tag == tag)
           {
               hit_count++;
               line->time_stamp = ++time_stamp;
               if(p_flag)
                   printf("hit ");
               miss_flag = 0;
               break;
           }
        }

        if(!miss_flag)
        {
            continue;
        }
        if(p_flag)
            printf("miss ");
        miss_count++;
        
        // check if have empty line
        unsigned char inject_flag = 0;
        for(int i = 0; i < E; i++)
        {
            struct Line *line = &(set->lines[i]);
            if(line->bit == 0)
            {
                line->bit = 1;
                line->tag = tag;
                line->time_stamp = ++time_stamp;
                inject_flag = 1;
                break;
            }
        }

        if(!inject_flag)
        {
            int index = 0;
            unsigned long min = ~(0UL);
            for(int i = 0; i < E; i++)
            {
                unsigned long time_stamp = (set->lines[i]).time_stamp;
                if(time_stamp < min)
                {
                    index = i;
                    min = time_stamp;
                }
            }
            set->lines[index].tag = tag;
            set->lines[index].time_stamp = ++time_stamp;
            evict_count++;
            if(p_flag)
                printf("eviction ");
        }
        }
        if(p_flag)
            printf("\n");
    }

    fclose(p_file);
    
    printSummary(hit_count, miss_count, evict_count);

    for(int i = 0; i < S; i++)
    {
        free(sets[i].lines);
    }

    free(sets);

    return 0;
}

void exit_exe()
{
    printf("wrong argument\n");
    exit(0);
}
