#pragma once

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <glib.h>

#define DATE "2023/10/01"
#define DATETIME "2023/10/01 00:00:00"

typedef struct date *Date;

typedef struct datetime *Datetime;

char *get_datetime_year(Datetime date);
Date valid_date (char *date_str);
Datetime valid_date_time(char *datetime_str);
void free_date(Date date);
void free_datetime(Datetime datetime);
int calculate_age(Date birth_date);
int calculate_days(Date begin_date, Date end_date);
int calculate_seconds(Datetime begin, Datetime end);
char *date_to_string(Date date);
char *datetime_to_string(Datetime datetime);
int most_recent_date(Date date1, Date date2);
int most_recent_datetime(Datetime datetime1, Datetime datetime2);
int most_recent(Datetime date1, Date date2);
int equal_dates(Date date1, Date date2);
int equal_datetime(Datetime date1, Datetime date2);
int between_date(Date date1, Date date2, Date date3);
int between_datetime(Datetime date1, Datetime beginD, Datetime endD);