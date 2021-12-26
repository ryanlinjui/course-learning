#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct{
    int64_t year;
    int64_t month;
    int64_t date;
    int64_t hour;
    int64_t minute;
}time;

void errorMessage();
void errorInputDetect(time);
void errorTimeDetect(time, time);
int64_t allldayCounter(time, time);
int8_t weekCounter(time);
int64_t workDayCounter(time, time, int64_t);
int64_t workTimeCounter(time, time, int64_t);


int main(){
    time startTime, endTime;
    printf("$ ./hw0203\n");
    printf("From: ");
    scanf("%lld/%lld/%lld %lld:%lld", &(startTime.year), &(startTime.month), &(startTime.date), &(startTime.hour), &(startTime.minute));
    errorInputDetect(startTime);
    printf("To: ");
    scanf("%lld/%lld/%lld %lld:%lld", &(endTime.year), &(endTime.month), &(endTime.date), &(endTime.hour), &(endTime.minute));
    errorInputDetect(endTime);
    errorTimeDetect(startTime, endTime);

    int64_t alllday = allldayCounter(startTime, endTime);
    int64_t workDay = workDayCounter(startTime, endTime, alllday);

    workTimeCounter(startTime, endTime, workDay);

    return 0;
}

void errorMessage(){
    printf("ERROR\n");
    exit(0);
}

void errorInputDetect(time day){
    int8_t monthDay[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(day.year <= 0 || day.month <= 0 || day.date <= 0 || day.hour < 0 || day.minute < 0 || day.minute >= 60){
        errorMessage();
    }
    if(day.month > 12){
        errorMessage();
    }
    if(day.date > monthDay[day.month - 1]){
        errorMessage();
    }
    if(day.hour > 24 || (day.hour == 24 && day.minute != 0) ){
        errorMessage();
    }
    if( !(day.year % 400 == 0 || ( day.year % 4 == 0 && day.year % 100 != 0 ) ) && day.month == 2 && day.date == 29){
        errorMessage();
    }

}

void errorTimeDetect(time start, time end){
    if(start.year > end.year){
        errorMessage();
    }
    else if(start.year == end.year){
        if(start.month > end.month){
            errorMessage();
        }
        else if(start.month == end.month){
            if(start.date > end.date){
                errorMessage();
            }
            else if(start.date == end.date){
                if(start.hour > end.hour){
                    errorMessage();
                }
                else if(start.hour == end.hour){
                    if(start.minute > end.minute){
                        errorMessage();
                    }
                }
            }
        }
    }
}

int64_t allldayCounter(time start,  time end){
    int64_t y1, m1, d1;
    int64_t y2, m2, d2;
    m1 = (start.month + 9) % 12;
    y1 = start.year - m1 / 10;
    d1 = 365 * y1 + y1 / 4 - y1 / 100 + y1 / 400 + (m1 * 306 + 5) / 10 + (start.date - 1);
    
    m2 = (end.month + 9) % 12;
    y2 = end.year - m2 / 10;
    d2 = 365 * y2 + y2 / 4 - y2 / 100 + y2 / 400 + (m2 * 306 + 5) / 10 + (end.date - 1);
    
    return (d2 - d1) + 1;
}

int8_t weekCounter(time day){
    return (day.date += day.month < 3 ? day.year-- : day.year - 2, 23 * day.month / 9 + day.date + 4 + day.year / 4- day.year / 100 + day.year / 400) % 7;
}

int64_t workDayCounter(time start, time end, int64_t alllday){
    int8_t startWeek = weekCounter(start);
    int8_t endWeek = weekCounter(end);
    int64_t holidayDay = ((alllday - 1) / 7) * 2 ;
    while(startWeek != endWeek){
        if(startWeek == 6 || startWeek == 0){
            holidayDay++;
        }
        startWeek = (startWeek + 1) % 7;
    }
    return alllday - holidayDay - (endWeek == 6 || endWeek == 0);
}

int64_t workTimeCounter(time start,time end, int64_t workDay){
    int64_t workHour = workDay * 8;
    int64_t workMinute = 0;
    int8_t startWeek = weekCounter(start);
    int8_t endWeek = weekCounter(end);
    if(startWeek != 0 && startWeek != 6){
        if(start.hour < 9 || start.hour == 9 && start.minute == 0){
        }
        else if(start.hour < 12 || start.hour == 12 && start.minute == 0){
            workHour -= start.hour - 9;
            workMinute -= start.minute;
        }
        else if(start.hour < 13 || start.hour == 13 && start.minute <= 30){
            workHour -= 3;
        }
        else if(start.hour < 18 || start.hour == 18 && start.minute <= 30){
            workHour -= (3 + start.hour - 13);
            workMinute -= (start.minute - 30);
        }
        else{
            workHour -= 8;
        }
    }
    
    if(endWeek != 0 && endWeek != 6){
        workHour -= 8;
        if(end.hour < 9 || end.hour == 9 && end.minute == 0){
        }
        else if(end.hour < 12 || end.hour == 12 && end.minute == 0){
            workHour += end.hour - 9;
            workMinute += end.minute;
        }
        else if(end.hour < 13 || end.hour == 13 && end.minute <= 30){
            workHour += 3;
        }
        else if(end.hour < 18 || end.hour == 18 && end.minute <= 30){
            workHour += (3 + end.hour - 13);
            workMinute += (end.minute - 30);
        }
        else{
            workHour += 8;
        }
    }
    
    if(workMinute >= 60){
        workHour += (workMinute / 60);
        workMinute %= 60;
    }
    while(workMinute < 0){
        workHour--;
        workMinute += 60;
    }
    printf("Working Hours : %lld hours %lld mins.\n", workHour, workMinute);
    return 0;
}