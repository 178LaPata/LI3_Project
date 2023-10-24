typedef struct date *date;

typedef struct datetime *datetime;

date valid_date (char *date_str);

datetime valid_date_time(char *datetime_str);
int calculate_age(date birth_date);