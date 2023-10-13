#include "date.h"

#define DATE "2023/10/01"
#define DATETIME "2023/10/01 00:00:00"

#include "stdio.h"
#include "stdlib.h"

struct date{
    char *year, *month, *day;
};

struct dateTime{
    char *year, *month, *day, *hour, *minutes, *seconds;
};

Date valid_date(char *date_str) {
    if (strlen(date_str) != 10 || date_str[4] + date_str[7] != 2*'/') return NULL;

    for (int i = 0; date_str[i]; i++) {
        if (i == 4 || i == 7) continue;
        if (date_str[i]<'0' || date_str[i]>'9') return NULL;
    }

    Date date = malloc(sizeof(struct date));

    date->year = strsep(&date_str, "/");
    date->month = strsep(&date_str, "/");
    date->day = strsep(&date_str, " ");

    if (atoi(date->year) >= 1900 && atoi(date->year) <= 9999) {
        if (atoi(date->month) >= 1 && atoi(date->month) <= 12) {
            if (atoi(date->day) >= 1 && atoi(date->day) <= 31) return date;
            else return NULL;
        }
        else return NULL;
    } else return NULL;

    free(date);
    return NULL;
}


DateTime valid_date_time(char *datetime_str) {
    if (strlen(datetime_str) != 19 || datetime_str[4] + datetime_str[7] + datetime_str[10] + datetime_str[13] + datetime_str[16] != 5*'/') return NULL;

    for (int i = 0; datetime_str[i]; i++) {
        if (i == 4 || i == 7 || i == 10 || i == 13 || i == 16) continue;
        if (datetime_str[i]<'0' || datetime_str[i]>'9') return NULL;
    }

    DateTime datetime = malloc(sizeof(struct datetime));

    datetime->year = strsep(&datetime_str, "/");
    datetime->month = strsep(&datetime_str, "/");
    datetime->day = strsep(&datetime_str, " ");
    datetime->hour = strsep(&datetime_str, ":");
    datetime->minute = strsep(&datetime_str, ":");
    datetime->second = strsep(&datetime_str, "\0");

    if (atoi(datetime->year) >= 1900 && atoi(datetime->year) <= 9999) {
        if (atoi(datetime->month) >= 1 && atoi(datetime->month) <= 12) {
            if (atoi(datetime->day) >= 1 && atoi(datetime->day) <= 31) {
                if (atoi(datetime->hour) >= 0 && atoi(datetime->hour) <= 23) {
                    if (atoi(datetime->minute) >= 0 && atoi(datetime->minute) <= 59) {
                        if (atoi(datetime->second) >= 0 && atoi(datetime->second) <= 59) return datetime;
                    }
                }
            }
        }
    }

    free(datetime);
    return NULL;
}
