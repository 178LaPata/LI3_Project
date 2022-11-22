#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct xd_date *XD_DATE;

int get_date_day (XD_DATE date);

int get_date_month (XD_DATE date);

int get_date_year (XD_DATE date);

int set_date (XD_DATE date, char* day, char* month, char* year);

int get_age (XD_DATE date);

int validar_date (XD_DATE date);