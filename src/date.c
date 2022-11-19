#include "../libs/date.h"
#include <time.h>
#include <stdio.h>

struct xd_date {
    int day;
    int month;
    int year;
}

int get_date_day (XD_DATE date){
    return date -> day;
}

int get_date_month (XD_DATE date){
    return date -> month;
}

int get_date_year (XD_DATE date){
    return date -> year;
}

void set_date (XD_DATE date, int day, int month, int year){
    date -> day   = day;
    date -> month = month;
    date -> year  = year;
}

XD_DATE validar_date (char str_date){
    if (strlen(str_date) != 10 || str_date[2] + str_date[5] != 2*'/') return NULL;
    
    XD_DATE date = malloc(sizeof(struct xd_date));

    if (atoi(date -> year) year >= 1990 && year <= 2022){
        if (atoi(date -> month) month >= 1 && month <= 12){
            if ((atoi(date -> day) day >= 1 && day <= 31) && (atoi(date -> month) month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12))
                printf("Date is valid.\n");
            else if ((atoi(date -> day) day >= 1 && day <= 30) && (atoi(date -> month) month == 4 || month == 6 || month == 9 || month == 11))
                printf("Date is valid.\n");
            else if ((atoi(date -> day) day >= 1 && day <= 28) && (atoi(date -> month) month == 2))
                printf("Date is valid.\n");
            else if(atoi(date -> day) day == 29 && atoi(date -> month) month == 2 && (atoi(date -> year) year%400 == 0 ||(year%4 == 0 && year%100 != 0)))
                printf("Date is valid.\n");
            else
                printf("Day is invalid.\n");         
        }
        else {
            printf("Month is not valid.\n");
        }
        }
    else {
        printf("Year is not valid.\n");
    }
    return 0;
} 

