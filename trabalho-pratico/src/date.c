#include "../includes/date.h"

struct date{
    char *year, *month, *day;
};

struct datetime{
    char *year, *month, *day, *hour, *minute, *second;
};

char *get_datetime_year(Datetime date){
    return date->year;
}

void free_date(Date date){
    if(date == NULL) return;
    free(date->year);
    free(date->month);
    free(date->day);
    free(date);
}

void free_datetime(Datetime datetime){
    if(datetime == NULL) return;
    free(datetime->year);
    free(datetime->month);
    free(datetime->day);
    free(datetime->hour);
    free(datetime->minute);
    free(datetime->second);
    free(datetime);
}

Date valid_date (char *date_str){

    if (strlen(date_str) != 10 || date_str[4] != '/' || date_str[7] != '/') return NULL;
    for (int i=0 ; date_str[i] ; i++){
        if (i==4 || i==7) continue;
        if (date_str[i]<'0' || date_str[i]>'9') return NULL;
    }

    Date date = malloc(sizeof(struct date));

    char *year = strdup(strsep(&date_str, "/"));
    char *month = strdup(strsep(&date_str, "/"));
    char *day = strdup(date_str);

    date->year  = strdup(year);
    date->month = strdup(month);
    date->day = strdup(day);

    free(year);
    free(month);
    free(day);

    if(atoi(date->year) >= 1900 && atoi(date->year) <= 9999){
        if(atoi(date->month) >= 1 && atoi(date->month) <= 12){
            if(atoi(date->day) >= 1 && atoi(date->day) <= 31){
                return date;
            }
        }
    }
    free(date);
    return NULL;
}

Datetime valid_date_time(char *datetime_str) {
    if (strlen(datetime_str) != 19 || datetime_str[4] != '/' || datetime_str[7] != '/' || datetime_str[10] != ' ' || datetime_str[13] != ':' || datetime_str[16] != ':') return NULL;

    for (int i = 0; datetime_str[i]; i++) {
        if (i == 4 || i == 7 || i == 10 || i == 13 || i == 16) continue;
        if (datetime_str[i]<'0' || datetime_str[i]>'9') return NULL;
    }

    Datetime datetime = malloc(sizeof(struct datetime));

    char *year = strdup(strsep(&datetime_str, "/"));
    char *month = strdup(strsep(&datetime_str, "/"));
    char *day = strdup(strsep(&datetime_str, " "));
    char *hour = strdup(strsep(&datetime_str, ":"));
    char *minute = strdup(strsep(&datetime_str, ":"));
    char *second = strdup(datetime_str);

    datetime->year = strdup(year);
    datetime->month = strdup(month);
    datetime->day = strdup(day);
    datetime->hour = strdup(hour);
    datetime->minute = strdup(minute);
    datetime->second = strdup(second);

    free(year);
    free(month);
    free(day);
    free(hour);
    free(minute);
    free(second);

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

// calcula a idade de um user 
int calculate_age(Date birth_date) {
    int ano_atual, mes_atual, dia_atual;
    sscanf(DATE, "%d/%d/%d", &ano_atual, &mes_atual, &dia_atual);

    int ano_nascimento = atoi(birth_date->year);
    int mes_nascimento = atoi(birth_date->month);
    int dia_nascimento = atoi(birth_date->day);

    int idade = ano_atual - ano_nascimento;
    if (mes_atual < mes_nascimento || 
        (mes_atual == mes_nascimento && dia_atual < dia_nascimento)) {
        idade--;
    }

    return idade;
}

// calcula os dias entre duas datas
int calculate_days(Date begin_date, Date end_date){
    int ano_inicio = atoi(begin_date->year);
    int mes_inicio = atoi(begin_date->month);
    int dia_inicio = atoi(begin_date->day);

    int ano_fim = atoi(end_date->year);
    int mes_fim = atoi(end_date->month);
    int dia_fim = atoi(end_date->day);

    return (ano_fim - ano_inicio) * 365 + (mes_fim - mes_inicio) * 30 + (dia_fim - dia_inicio);
}

// calcula os segundos entre duas datetimes
int calculate_seconds(Datetime begin, Datetime end){
    int ano_inicio = atoi(begin->year);
    int mes_inicio = atoi(begin->month);
    int dia_inicio = atoi(begin->day);
    int hora_inicio = atoi(begin->hour);
    int minuto_inicio = atoi(begin->minute);
    int segundo_inicio = atoi(begin->second);

    int ano_fim = atoi(end->year);
    int mes_fim = atoi(end->month);
    int dia_fim = atoi(end->day);
    int hora_fim = atoi(end->hour);
    int minuto_fim = atoi(end->minute);
    int segundo_fim = atoi(end->second);

    struct tm inicio = {0};
    struct tm fim = {0};

    inicio.tm_year = ano_inicio - 1900;
    inicio.tm_mon = mes_inicio - 1;
    inicio.tm_mday = dia_inicio;
    inicio.tm_hour = hora_inicio;
    inicio.tm_min = minuto_inicio;
    inicio.tm_sec = segundo_inicio;

    fim.tm_year = ano_fim - 1900;
    fim.tm_mon = mes_fim - 1;
    fim.tm_mday = dia_fim;
    fim.tm_hour = hora_fim;
    fim.tm_min = minuto_fim;
    fim.tm_sec = segundo_fim;

    time_t inicio_t = mktime(&inicio);
    time_t fim_t = mktime(&fim);

    double segundos = difftime(fim_t, inicio_t);

    return (int) segundos;
}

// funcao que converte uma data para string
char *date_to_string(Date date){
    char *date_str = malloc(sizeof(char) * 11);
    sprintf(date_str, "%s/%s/%s", date->year, date->month, date->day);
    return date_str;
}

// funcao que converte uma datetime para string
char *datetime_to_string(Datetime datetime){
    char *datetime_str = malloc(sizeof(char) * 20);
    sprintf(datetime_str, "%s/%s/%s %s:%s:%s", datetime->year, datetime->month, datetime->day, datetime->hour, datetime->minute, datetime->second);
    return datetime_str;
}

// funcao que verifica a funcao mais recente, retorna 1 se data1 for mais recente que data2 e 0 caso contrario
int most_recent_date(Date date1, Date date2){
    if(date1 == NULL && date2 == NULL) return 1;
    else if(date1 == NULL || date2 == NULL) return 0;
    
    if(atoi(date1->year) > atoi(date2->year)) return 1;
    else if(atoi(date1->year) < atoi(date2->year)) return 0;
    else{
        if(atoi(date1->month) > atoi(date2->month)) return 1;
        else if(atoi(date1->month) < atoi(date2->month)) return 0;
        else{
            if(atoi(date1->day) > atoi(date2->day)) return 1;
            else if(atoi(date1->day) < atoi(date2->day)) return 0;
            else return 1;
        }
    }
}  

// funcao que verifica a funcao mais recente, retorna 1 se data1 for mais recente que data2 e 0 caso contrario
int most_recent_datetime(Datetime date1, Datetime date2){
    if(date1 == NULL && date2 == NULL) return 1;
    else if(date1 == NULL || date2 == NULL) return 0;
    
    if(atoi(date1->year) > atoi(date2->year)) return 1;
    else if(atoi(date1->year) < atoi(date2->year)) return 0;
    else{
        if(atoi(date1->month) > atoi(date2->month)) return 1;
        else if(atoi(date1->month) < atoi(date2->month)) return 0;
        else{
            if(atoi(date1->day) > atoi(date2->day)) return 1;
            else if(atoi(date1->day) < atoi(date2->day)) return 0;
            else{
                if(atoi(date1->hour) > atoi(date2->hour)) return 1;
                else if(atoi(date1->hour) < atoi(date2->hour)) return 0;
                else{
                    if(atoi(date1->minute) > atoi(date2->minute)) return 1;
                    else if(atoi(date1->minute) < atoi(date2->minute)) return 0;
                    else{
                        if(atoi(date1->second) > atoi(date2->second)) return 1;
                        else if(atoi(date1->second) < atoi(date2->second)) return 0;
                        else return 1;
                    }
                }
            }
        }
    }
}

// retorna 1 se date1 for mais recente que date2 e 0 caso contrario
int most_recent(Datetime date1, Date date2){
    if(date1 == NULL && date2 == NULL) return 1;
    else if(date1 == NULL || date2 == NULL) return 0;
    
    if(atoi(date1->year) > atoi(date2->year)) return 1;
    else if(atoi(date1->year) < atoi(date2->year)) return 0;
    else{
        if(atoi(date1->month) > atoi(date2->month)) return 1;
        else if(atoi(date1->month) < atoi(date2->month)) return 0;
        else{
            if(atoi(date1->day) > atoi(date2->day)) return 1;
            else if(atoi(date1->day) < atoi(date2->day)) return 0;
            else return 1;
        }
    }
}

// funcao que verifica se duas datas sao iguais, retornando 1 se forem iguais e 0 caso contrario
int equal_dates(Date date1, Date date2){
    if(date1 == NULL && date2 == NULL) return 1;
    else if(date1 == NULL || date2 == NULL) return 0;
    
    if(strcmp(date1->year, date2->year) == 0 && strcmp(date1->month, date2->month) == 0 && strcmp(date1->day, date2->day) == 0) return 1;
    else return 0;
}

// funcao que verifica se duas datetimes sao iguais, retornando 1 se forem iguais e 0 caso contrario
int equal_datetime(Datetime date1, Datetime date2){
    if(date1 == NULL && date2 == NULL) return 1;
    else if(date1 == NULL || date2 == NULL) return 0;
    
    if(strcmp(date1->year, date2->year) == 0 && strcmp(date1->month, date2->month) == 0 && 
       strcmp(date1->day, date2->day) == 0 && strcmp(date1->hour, date2->hour) == 0 && 
       strcmp(date1->minute, date2->minute) == 0 && strcmp(date1->second, date2->second) == 0) return 1;
    else return 0;
}

// funcao que verifica se a data1 esta entre a data2 e a data3, retornando 1 se estiver e 0 caso contrario
int between_date(Date date1, Date date2, Date date3){
    if(most_recent_date(date1, date2) == 1 && most_recent_date(date3, date1) == 1) return 1;
    else return 0;
}

// funcao que verifica se a datetime1 esta entre a datetime2 e a datetime3, retornando 1 se estiver e 0 caso contrario
int between_datetime(Datetime date1, Datetime beginD, Datetime endD){
    if(most_recent_datetime(date1, beginD) == 1 && most_recent_datetime(endD, date1) == 1) return 1;
    else return 0;
}
