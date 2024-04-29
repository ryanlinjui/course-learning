#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

#define MAX_LEN 4000
#define DATA_START_ROW 5

typedef struct _pg
{
    char *country;
    int64_t pg_value;
    double pg_rate;
    double pg_dev;
    double pg_prediction;
}PG;

double *year;

int8_t match(char *source, char* target)
{
    int32_t len_target = strlen(target);
    for(int i=0;source[i];i++)
    {
        for(int j=0;target[j];j++)
        {
            if((target[j]>=65&&target[j]<=90)||(target[j]>=97&&target[j]<122))
            {
                if(abs(source[i+j]-target[j])&&(abs(source[i+j]-target[j])-32))
                {
                    return 0;
                }
            }
            else
            {
                if(source[i+j]-target[j])
                {
                    return 0;
                }
            }    
            if(j>=len_target-1)
            {
                return 1;
            }
        }
    }
    return 0;
}

double get_stddev(double num[],int32_t size)
{
    double sum=0,avg=0;
    for(int i=0;i<size;i++)
    {
        sum += num[i];
    }
    avg = sum/size; 
    double square_sum=0;
    for(int i=0;i<size;i++)
    {
        square_sum += pow(num[i]-avg,2);
    }
    return sqrt(square_sum/((double)size));
}

double predict_population(double population[],int32_t size)
{
    #define PRDDICT_YEAR 2021
    double sigma_x=0,sigma_x2=0,sigma_y=0,sigma_xy=0,b,a;
    for(int i=0;i<size;i++)
    {
        sigma_x = sigma_x+population[i];
        sigma_x2= sigma_x2+(population[i]*population[i]);
        sigma_y = sigma_y+year[i];
        sigma_xy = sigma_xy+(year[i]*population[i]);
    }
    b = (sigma_x2*sigma_y-sigma_xy*sigma_x)/(size*sigma_x2-sigma_x*sigma_x);
    a = (size*sigma_xy-sigma_x*sigma_y)/(size*sigma_x2-sigma_x*sigma_x);
    return a * PRDDICT_YEAR + b;
}

int32_t menu()
{
    printf("--- Menu ---\n"
    "1) Which country has the largest population growth?\n"
    "2) Which country has the largest population growth rate?\n"
    "3) Which country has the smallest population growth, including negative growth?\n"
    "4) Which country has the smallest population growth rate, including negative growth?\n"
    "5) Which country has the largest population standard deviation?\n"
    "6) Which country has the smallest population standard deviation?\n"
    "7) Given a country name (case-insensitive), please use linear least squares method to predict the country's population in 2021.\n" 
    "8) Exit\n"
    "Your choice: ");
    int32_t choice = 0;
    scanf("%d", &choice);
    if((choice < 1) || (choice > 8))
    {
        printf("Invalid input!!\n");
        exit(0);
    }
    return choice;
}

void get_year_array(char *source)
{
    char *match = ",\"";   
    char *token = strtok(source,match);
    for(int i = 0;; i++,token = strtok(NULL,match))
    {
        if(token==NULL) break;
        if(token[0]>=48&&token[0]<=57)
        {
            // printf("%d: %s\n",i,token); //show source elements index of numbers
            if(i>=4)
            {
                year[i-4] = (double)atoi(token);
            }
        }
    }
}

void analysis(char *source, PG *data,int32_t start_time,int32_t end_time)
{
    char *match = ",\"";   
    char *token = strtok(source,match);
    
    double num[end_time-start_time+1];
    num[end_time-start_time] = -1;

    double sum = 0;
    for(int i = 0;; i++,token = strtok(NULL,match))
    {
        if(token==NULL) break;
        
        if(token[0]>=48&&token[0]<=57)
        {
            // printf("%d: %s\n",i,token); //show source elements index of numbers
            if(i==0)
            {
                data->country = malloc(strlen(token)+1);
                strncpy(data->country,token,strlen(token));
            }
            else if(i>=5)
            {

                num[i-5] = (double)atoi(token);
                sum += num[i-5];
            }
        }
    }
    
    
    if(num[end_time-start_time] == -1)
    {
        data->pg_value = 0;
        data->pg_rate = 0;
        data->pg_dev = 0;
        data->pg_prediction = 0;
        return;
    }

    data->pg_value = num[end_time-start_time] - num[0];
    data->pg_rate = ((num[end_time-start_time] - num[0])/(sum/(end_time-start_time)))*1000;
    data->pg_dev = get_stddev(num,end_time-start_time+1);
    data->pg_prediction = predict_population(num,end_time-start_time+1);
}

int main()
{
    char *data_name = malloc(200);
    int32_t start_time = 0;
    int32_t end_time = 0;
    printf("Please enter the data name: ");
    scanf("%s",data_name);
    FILE *file = fopen(data_name,"r");
    PG *data = NULL;
    char *input = malloc(MAX_LEN);
    if(file==NULL)
    {
        printf("File doesn't exist!!\n");
        return 0;
    }
    printf("Please enter the analysis start time: ");
    scanf("%d",&start_time);
    printf("Please enter the analysis end time: ");
    scanf("%d",&end_time);

    int32_t count;
    year = malloc(MAX_LEN*sizeof(double));
    for(count=0;!feof(file);count++)
    {   
        if(fgets(input,MAX_LEN,file)==NULL) break;
        if(count==DATA_START_ROW-1)
        {
            get_year_array(input);
        }
        else if(count>=DATA_START_ROW)
        {   
            data = realloc(data,(count-DATA_START_ROW+1)*sizeof(PG));
            analysis(input,&data[count-DATA_START_ROW],start_time,end_time);
            
        }
    }
    
    count -= DATA_START_ROW;
    PG *temp;
    for(int32_t choice=menu(); choice != 8;choice=menu())
    {
        if(choice == 1) //largest population growth
        {
            int64_t big = data[0].pg_value;
            
            for(int i=1;i<count;i++)
            {
                if(big<data[i].pg_value)
                {
                    big = data[i].pg_value;
                    temp = &data[i];
                }
            }
            printf("%s\n",temp->country);
        }
        else if(choice == 2) //largest population growth rate
        {
            double big = data[0].pg_rate;
            for(int i=1;i<count;i++)
            {
                if(big<data[i].pg_rate)
                {
                    big = data[i].pg_rate;
                    temp = &data[i];
                }
            }
            printf("%s\n",temp->country);
        }
        else if(choice == 3) //smallest population growth
        {
            int64_t small = data[0].pg_value;
            for(int i=1;i<count;i++)
            {
                if(small>data[i].pg_value)
                {
                    small = data[i].pg_value;
                    temp = &data[i];
                }
            }
            printf("%s\n",temp->country);
        }
        else if(choice == 4) //smallest population growth rate
        {
            double small = data[0].pg_rate;
            for(int i=1;i<count;i++)
            {
                if(small>data[i].pg_rate)
                {
                    small = data[i].pg_rate;
                    temp = &data[i];
                }
            }
            printf("%s\n",temp->country);
        }
        else if(choice == 5)
        {   
            double big = data[0].pg_dev;
            for(int i=1;i<count;i++)
            {
                if(big<data[i].pg_dev)
                {
                    big = data[i].pg_dev;
                    temp = &data[i];
                }
            }
            printf("%s\n",temp->country);
        }
        else if(choice == 6)
        {
            double small = data[0].pg_dev;
            for(int i=1;i<count;i++)
            {
                if(small>data[i].pg_dev)
                {
                    small = data[i].pg_dev;
                    temp = &data[i];
                }
            }
            printf("%s\n",temp->country);
        }
        else if(choice == 7)
        {
            char *input_country = malloc(101);
            printf("Please enter the country: ");
            fgets(input_country,100,stdin);
            input_country[strlen(input_country)-1] = (input_country[strlen(input_country)-1]=='\n') ? 0 : input_country[strlen(input_country)-1];
            for(int i=0;i<count;i++)
            {
                if(match(data[i].country,input_country))
                {
                    printf("linear least squares method to predict value: %f\n",data[i].pg_prediction);
                }
            }
        }
    }
    fclose(file);
    return 0;
}