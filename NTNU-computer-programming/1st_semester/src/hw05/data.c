#include <stdint.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>

double get_mean( const int32_t input[], size_t size )
{
    int64_t sum = 0;
    for( size_t i = 0; i < size;i++)
    {
        sum += input[i];
    }
    return (sum/(double)size);
}

double get_median( const int32_t input[], size_t size )
{
    //create sorted_input array 
    int32_t sorted_input[size];
    for(size_t i = 0; i < size;i++)
    {
        sorted_input[i]=input[i];
    }
    for(size_t i = 0; i < size-1;i++)
    {
        for(size_t j = i+1; j < size;j++)
        {
            if(sorted_input[i]>sorted_input[j])
            {
                int temp=sorted_input[j];
                sorted_input[j]=sorted_input[i];
                sorted_input[i]=temp;
            }
        }
    }

    //main
    if(size%2==0)
    {
        return (double)(sorted_input[size/2]+sorted_input[(size/2)-1])/2;
    }
    else
    {
        return sorted_input[size/2];
    }
}

int32_t get_mode( const int32_t input[], size_t size )
{
    //create sorted_input array 
    int32_t sorted_input[size];
    for(size_t i = 0; i < size;i++)
    {
        sorted_input[i]=input[i];
    }
    for(size_t i = 0; i < size-1;i++)
    {
        for(size_t j = i+1; j < size;j++)
        {
            if(sorted_input[i]>sorted_input[j])
            {
                int temp=sorted_input[j];
                sorted_input[j]=sorted_input[i];
                sorted_input[i]=temp;
            }
        }
    }

    //main
    int32_t compare=sorted_input[0],mode_counter=0,mode=0,big=0;
    for(size_t i = 0; i < size;i++)
    {
        if(sorted_input[i]!=compare||i==0)
        {   
            if(mode_counter>=big)
            {
                big=mode_counter;
                mode=compare;
                
            }
            compare=sorted_input[i];
            mode_counter=1;
        }
        else
        {
            mode_counter++;
        }
        if(i==size-1)
        {   
            if(mode_counter>=big)
            {
                big=mode_counter;
                mode=compare;
                
            }
            compare=sorted_input[i];
        }
    }
    return mode;
}

double get_stddev( const int32_t input[], size_t size )
{
    int64_t sum = 0;
    for( size_t i = 0; i < size;i++)
    {
        sum += input[i];
    }
    double mean = sum / (double)size;
    double sigma=0;
    for( size_t i = 0; i < size;i++)
    {
        sigma+=pow((input[i]-mean),2);
    }
    return sqrt(sigma/size);
}