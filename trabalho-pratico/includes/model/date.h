#pragma once

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#define DATE "2023/10/01"
#define DATETIME "2023/10/01 00:00:00"

typedef struct date *date;

typedef struct datetime *datetime;

date valid_date (char *date_str);

datetime valid_date_time(char *datetime_str);
int calculate_age(date birth_date);
void printDate(date date);
