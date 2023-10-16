#include "../../includes/model/date.h"

#define DATE "2023/10/01"
#define DATETIME "2023/10/01 00:00:00"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

struct date{
    char *year, *month, *day;
};

struct dateTime{
    char *year, *month, *day, *hour, *minutes, *seconds;
};

Date valid_date(char *date_str) {
    Date date = malloc(sizeof(struct date));

    if (date == NULL) {
        fprintf(stderr, "Erro ao alocar memória para Date.\n");
        exit(EXIT_FAILURE);
    }

    date->year = strsep(&date_str, "/");
    date->month = strsep(&date_str, "/");
    date->day = date_str;

    if (atoi(date->year) >= 1900 && atoi(date->year) <= 9999) {
        if (atoi(date->month) >= 1 && atoi(date->month) <= 12) {
            if (atoi(date->day) >= 1 && atoi(date->day) <= 31) {
                return date;
            }
        }
    }

    free(date);
    return NULL;
}

