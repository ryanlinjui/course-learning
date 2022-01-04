#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
 
int32_t day_diff(int32_t year_start, int32_t month_start, int32_t day_start, int32_t year_end, int32_t month_end, int32_t day_end)
{
    int32_t y2, m2, d2;
    int32_t y1, m1, d1;
    m1 = (month_start + 9) % 12;
    y1 = year_start - m1/10;
    d1 = 365*y1 + y1/4 - y1/100 + y1/400 + (m1*306 + 5)/10 + (day_start - 1);
    m2 = (month_end + 9) % 12;
    y2 = year_end - m2/10;
    d2 = 365*y2 + y2/4 - y2/100 + y2/400 + (m2*306 + 5)/10 + (day_end - 1);    
    return (d2 - d1);
}

int32_t Day_caculate(int32_t year, int32_t month,int32_t day) //2020/3/5 ac:4 wr:3
{                                                             //1998/8/24 ac:1 wr:-5
    int32_t Day2021[12] = {5,1,1,4,6,2,4,7,3,5,1,3};          //2020/3/1 ac:7
    int32_t LenYear_add = 0;                                  //2022/3/1 ac:2
    if(year>=2021)                                            //1998/8/1 ac:6
    {
        if(year%4==0 && month>2)
        {   
            LenYear_add += 1;
        }
        int32_t LenYear_num = LenYear_add+((year-2021)/4);
        return (((Day2021[month-1]+(year-2021)+LenYear_num)+((day-1)%7)-1)%7)+1;
    }
    else
    {
        if(year%4==0 && month<=2)
        {   
            LenYear_add -= 1;
        }
        int32_t LenYear_num = LenYear_add+((year-2021)/4);
        return (((Day2021[month-1]+(year-2021)+LenYear_num)+((day-1)%7)-1)%7)+1;
    }
}

int32_t WeekDay_caculate(int32_t day_total,int32_t day_start,int32_t day_end) 
{
    //not include then day-start and day-end
    if(day_total==0||day_total==1)
    {
        return 0;
    }
    int32_t weekday_total = (day_total/7)*5;
    if(day_total%7==0)
    {
        return weekday_total-1;
    }
    if(day_start>=6&&day_start<=7)
    {
        day_start=1;
    }
    if(day_end>=6&&day_end<=7)
    {
        day_end = 5;
    }
    return weekday_total+(day_end-day_start)-1;
}

int32_t ThenDay_min_caculate(int32_t day_total,int32_t day_hour_start,int32_t day_min_start,int32_t day_hour_end,int32_t day_min_end)
{
    int32_t day_start_total_min = 0;
    int32_t day_end_total_min = 0;
    int32_t day_start = day_hour_start*60+day_min_start;
    int32_t day_end = day_hour_end*60+day_min_end;
    if(day_total>0){
        //day_start_total_min calculate
        if(day_start<9*60)
        {
            day_start_total_min = 8*60;
        }
        else if(day_start>185*6)
        {
            day_start_total_min = 0;
        }
        else if(day_start<12*60)
        {
            day_start_total_min = 5*60+(12*60-day_start_total_min);
        }
        else if(day_start>135*6)
        {
            day_start_total_min = 185*6-day_start_total_min;
        }
        else
        {
            day_start_total_min = 5*60;   
        }
        //day_end_total_min calculate
        if(day_end<9*60)
        {
            day_end_total_min = 0;
        }
        else if(day_end>185*6)
        {
            day_end_total_min =8*60;
        }
        else if(day_end<12*60)
        {
            day_end_total_min = day_end_total_min-9*60;
        }
        else if(day_end>135*6)
        {
            day_end_total_min = 3*60+(day_end_total_min-135*6);
        }
        else
        {
            day_end_total_min = 3*60;
        }
        return day_start_total_min+day_end_total_min;
    }
    else
    {
        int32_t data[2] = {day_start,day_end};
        for(int i=0; i<2;i++)
        {
            if(data[i]<8*30)
            {
                data[i] = 8*30;
            }
            else if(data[i]>185*3)
            {
                data[i] = 185*3;
            }
        }
        if((data[0]>=12*60&&data[0]<=135*6)||(data[1]>=12*60&&data[1]<=135*6))
        {
            if(data[0]>=12*60&&data[0]<=135*6&&data[1]>=12*60&&data[1]<=135*6)
            {
                return 0;
            }   
            else if(data[0]>=12*60&&data[0]<=135*6)
            {
                data[0] = 135*6;
            }
            else if(data[1]>=12*60&&data[1]<=135*6)
            {
                data[1] = 12*60;
            }
        }
        return data[1]-data[0];
    }
    
}

int main()
{
    int32_t month_day[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int32_t year[2],month[2],day[2],hour[2],min[2];
    int32_t total_min=0,wt=8,day_diff_total=0,day_start=0,day_end=0,weekday_total=0,then_day_min_total=0;
    printf("$ ./hw0203\n");
    printf("From: ");
    scanf("%d/%d/%d %d:%d",&year[0],&month[0],&day[0],&hour[0],&min[0]);
    printf("To: ");
    scanf("%d/%d/%d %d:%d",&year[1],&month[1],&day[1],&hour[1],&min[1]);
    if(hour[0]<0||hour[1]<0||hour[0]>23||hour[1]>23||min[0]<0||min[1]<0||min[0]>=60||min[1]>=60||year[0]<0||year[1]<0||month[0]<0||month[1]<0||month[0]>12||month[1]>12||day[0]<1||day[1]<1)
    {
        printf("ERROR\n");
        return 0;
    }
    if(day[0]>month_day[month[0]]||day[1]>month_day[month[1]])
    {
        if(day[0]==29||day)
    }
    day_diff_total = day_diff(year[0],month[0],day[0],year[1],month[1],day[1]);
    if(day_diff_total<0)
    {
        printf("ERROR\n");
        return 0;
    }
    day_start = Day_caculate(year[0],month[0],day[0]);
    day_end = Day_caculate(year[1],month[1],day[1]);
    weekday_total = WeekDay_caculate(day_diff_total,day_start,day_end);
    then_day_min_total = ThenDay_min_caculate(day_diff_total,hour[0],min[0],hour[1],min[1]);
    total_min = then_day_min_total+weekday_total*wt;
    printf("Working Hours : %d hours %d mins.\n",total_min/60,total_min%60);
    return 0;
}
