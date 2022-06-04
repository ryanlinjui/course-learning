#pragma once
#include "lib/cstd.h"
#include "lib/string.h"

// ./fin02 -c Taiwan -s 01-23-2020 -e 12-31-2021 -o output.csv

void create_plot(char *country,char *start,char *end,char *output)
{
    int32_t result = 0;
    FILE *file = fopen(output, "w");
    int32_t total = 0 ,sum = 0;
    int32_t l_r=0,c_r=0;
    FILE *p_file;
    char *data_name = calloc(100,sizeof(char));
    char *s_m = calloc(100,sizeof(char));
    char *s_d = calloc(100,sizeof(char));
    char *cmd = calloc(1000,sizeof(char));
    fprintf(file,"Date, New infected\n");
    char *l_data_name = calloc(100,sizeof(char));
    int32_t yy=atoi(start+6),mm=atoi(start),dd=atoi(start+3);
    dd--;
    if(dd==0)
    {
        mm--;
        if(mm==0)
        {
            yy--;
            mm=12;
        }
        if(mm==1)
        {
            dd=31;
        }
        else if(mm==2)
        {
            if(yy%4==0)
            {
                dd=29;
            }
            else
            {
                dd=28;
            }
        }
        else if(mm==3)
        {
            dd=31;
        }
        else if(mm==4)
        {
            dd=30;
        }
        else if(mm==5)
        {
            dd=31;
        }
        else if(mm==6)
        {
            dd=30;
        }
        else if(mm==7)
        {
            dd=31;
        }
        else if(mm==8)
        {
            dd=31;
        }
        else if(mm==9)
        {
            dd=30;
        }
        else if(mm==10)
        {
            dd=31;
        }
        else if(mm==11)
        {
            dd=30;
        }
        else if(mm==12)
        {
            dd=31;
        }
    }

    if(mm<10) 
    {
        sprintf(s_m, "0%d-", mm);  
    }
    else
    {
        sprintf(s_m, "%d-", mm);  
    }

    if(dd<10) 
    {
        sprintf(s_d,"0%d-",dd);
    }
    else
    {
        sprintf(s_d,"%d-",dd);
    }
    sprintf(l_data_name,"%s%s%d",s_m,s_d,yy);
    
    for(int32_t year=atoi(start+6),month=atoi(start),day=atoi(start+3),e_year=atoi(end+6),e_month=atoi(end),e_day=atoi(end+3);;day++)
    {
        if(month<10) 
        {
            fprintf(file,"0%d-",month);
            sprintf(s_m, "0%d-", month);  
        }
        else
        {
            fprintf(file,"%d-",month);
            sprintf(s_m, "%d-", month);  
        }

        if(day<10) 
        {
            fprintf(file,"0%d-",day);
            sprintf(s_d,"0%d-",day);
        }
        else
        {
            fprintf(file,"%d-",day);
            sprintf(s_d,"%d-",day);
        }
        sprintf(data_name,"%s%s%d",s_m,s_d,year);
        sprintf(cmd,"curl -o test.csv -s https://raw.githubusercontent.com/CSSEGISandData/COVID-19/master/csse_covid_19_data/csse_covid_19_daily_reports/%s.csv; grep %s test.csv | awk \'BEGIN {FS=\",\"}; {print $4}\'",l_data_name,country);
        p_file = popen(cmd, "r");
        fscanf(p_file, "%d", &l_r);
        pclose(p_file);
        sprintf(cmd,"curl -o test.csv -s https://raw.githubusercontent.com/CSSEGISandData/COVID-19/master/csse_covid_19_data/csse_covid_19_daily_reports/%s.csv; grep %s test.csv | awk \'BEGIN {FS=\",\"}; {print $4}\'",data_name,country); 
        p_file = popen(cmd, "r");
        fscanf(p_file, "%d", &c_r);
        pclose(p_file);
        result = c_r - l_r;
        fprintf(file,"%d,%d\n",year,result);
        
        total++;
        sum+= result;
        if(year*10000+month*100+day >= e_year*10000+e_month*100+e_day)
        {
            break;
        }

        if(year%4==0)
        {
            if((month==1&&day==31)||(month==2&&day==29)||(month==3&&day==31)||(month==4&&day==30)||(month==5&&day==31)||(month==6&&day==30)||(month==7&&day==31)||(month==8&&day==31)||(month==9&&day==30)||(month==10&&day==31)||(month==11&&day==30)||(month==12&&day==31))
            {
                day = 0;
                month++;
            }
        }
        else
        {
            if((month==1&&day==31)||(month==2&&day==28)||(month==3&&day==31)||(month==4&&day==30)||(month==5&&day==31)||(month==6&&day==30)||(month==7&&day==31)||(month==8&&day==31)||(month==9&&day==30)||(month==10&&day==31)||(month==11&&day==30)||(month==12&&day==31))
            {
                day = 0;
                month++;
            }
        }
        if(month>12)
        {
            year++;
            month=1;
        }
        strncpy(l_data_name,data_name,strlen(start));
    }
    fprintf(file,"Average,%2.f\n",(double)sum/(double)total);
    fclose(file);
}