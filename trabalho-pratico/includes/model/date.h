#pragma once

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <glib.h>

#define DATE "2023/10/01"
#define DATETIME "2023/10/01 00:00:00"

typedef struct date *date;

typedef struct datetime *datetime;

date valid_date (char *date_str);
datetime valid_date_time(char *datetime_str);
int calculate_age(date birth_date);
int calculate_days(date begin_date, date end_date);
int calculate_seconds(datetime begin, datetime end);
char *date_to_string(date date);
char *datetime_to_string(datetime datetime);
int most_recent_date(date date1, date date2);
int most_recent_datetime(datetime datetime1, datetime datetime2);
int most_recent(datetime date1, date date2);
int equal_dates(date date1, date date2);
int equal_datetime(datetime date1, datetime date2);
int between_date(date date1, date date2, date date3);
int between_datetime(datetime date1, datetime beginD, datetime endD);