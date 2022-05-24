#pragma once
#include "lib/cstd.h"

#define CMD "grep Mem /proc/meminfo | awk \'BEGIN {FS=\" \"}; {print $2}\'"

void __get_memory_available(double *val,double *percent)
{
    double mem_total=0, mem_available=0;
    FILE *file;
    file = popen(CMD, "r");
    fscanf(file, "%lf", &mem_total);
    fscanf(file, "%lf", &mem_available);
    fscanf(file, "%lf", &mem_available);
    pclose(file);
    *val = mem_available;
    *percent = (mem_available/mem_total)*100.0;
}

void memory_monitor(double show_byte,int32_t second,int32_t count)
{
    double val=0,percent=0;
    if(second>0)
    {
        while(1)
        {
            for(int i=0;i<count;i++)
            {
                __get_memory_available(&val,&percent);
                if(show_byte>1000)
                {
                    printf("Available: %d B (%.2lf%%\n",(int32_t)val*(int32_t)show_byte,percent);
                }
                else if(show_byte>0.9)
                {
                    printf("Available: %d KB (%.2lf%%)\n",(int32_t)val*(int32_t)show_byte,percent);
                }
                else
                {
                    printf("Available: %.2lf MB (%.2lf%%)\n",val*show_byte,percent);
                }
            }
            usleep(second*1000000);
        }
    }
    else
    {
        for(int i=0;i<count;i++)
        {
            __get_memory_available(&val,&percent);
            if(show_byte>1000)
            {
                printf("Available: %d B (%.2lf%%)\n",(int32_t)val*(int32_t)show_byte,percent);
            }
            else if(show_byte>0.9)
            {
                printf("Available: %d KB (%.2lf%%)\n",(int32_t)val*(int32_t)show_byte,percent);
            }
            else
            {
                printf("Available: %.2lf MB (%.2lf%%)\n",val*show_byte,percent);
            }
        }
    }
}