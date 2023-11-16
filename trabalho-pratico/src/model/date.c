#include "../../includes/model/date.h"

struct date{
    char *year, *month, *day;
};

struct datetime{
    char *year, *month, *day, *hour, *minute, *second;
};

struct date* valid_date (char *date_str){

    if (strlen(date_str) != 10 || date_str[4] != '/' || date_str[7] != '/') return NULL;
    for (int i=0 ; date_str[i] ; i++){
        if (i==4 || i==7) continue;
        if (date_str[i]<'0' || date_str[i]>'9') return NULL;
    }

    struct date* date = malloc(sizeof(struct date));

    date->year  = strdup(strsep(&date_str, "/"));
    date->month = strdup(strsep(&date_str, "/"));
    date->day = strdup(strsep(&date_str, " "));

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

struct datetime* valid_date_time(char *datetime_str) {
    if (strlen(datetime_str) != 19 || datetime_str[4] != '/' || datetime_str[7] != '/' || datetime_str[10] != ' ' || datetime_str[13] != ':' || datetime_str[16] != ':') return NULL;

    for (int i = 0; datetime_str[i]; i++) {
        if (i == 4 || i == 7 || i == 10 || i == 13 || i == 16) continue;
        if (datetime_str[i]<'0' || datetime_str[i]>'9') return NULL;
    }

    struct datetime* datetime = malloc(sizeof(struct datetime));

    datetime->year = strdup(strsep(&datetime_str, "/"));
    datetime->month = strdup(strsep(&datetime_str, "/"));
    datetime->day = strdup(strsep(&datetime_str, " "));
    datetime->hour = strdup(strsep(&datetime_str, ":"));
    datetime->minute = strdup(strsep(&datetime_str, ":"));
    datetime->second = strdup(strsep(&datetime_str, "\0"));

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
int calculate_age(date birth_date) {
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

int calculate_days(date begin_date, date end_date){
    int ano_inicio = atoi(begin_date->year);
    int mes_inicio = atoi(begin_date->month);
    int dia_inicio = atoi(begin_date->day);

    int ano_fim = atoi(end_date->year);
    int mes_fim = atoi(end_date->month);
    int dia_fim = atoi(end_date->day);

    struct tm inicio = {0};
    struct tm fim = {0};

    inicio.tm_year = ano_inicio - 1900;
    inicio.tm_mon = mes_inicio - 1;
    inicio.tm_mday = dia_inicio;

    fim.tm_year = ano_fim - 1900;
    fim.tm_mon = mes_fim - 1;
    fim.tm_mday = dia_fim;

    time_t inicio_t = mktime(&inicio);
    time_t fim_t = mktime(&fim);

    double dias = difftime(fim_t, inicio_t) / (60 * 60 * 24);

    return (int) dias;
}

int calculate_seconds(datetime begin, datetime end){
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

char *date_to_string(date date){
    char *date_str = malloc(sizeof(char) * 11);
    sprintf(date_str, "%s/%s/%s", date->year, date->month, date->day);
    return date_str;
}

char *datetime_to_string(datetime datetime){
    char *datetime_str = malloc(sizeof(char) * 20);
    sprintf(datetime_str, "%s/%s/%s %s:%s:%s", datetime->year, datetime->month, datetime->day, datetime->hour, datetime->minute, datetime->second);
    return datetime_str;
}

// funcao que verifica a funcao mais recente, retorna 1 se data1 for mais recente que data2 e 0 caso contrario
int most_recent_date(date date1, date date2){
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
int equal_dates(date date1, date date2){
    if(date1 == NULL && date2 == NULL) return 1;
    else if(date1 == NULL || date2 == NULL) return 0;
    
    if(strcmp(date1->year, date2->year) == 0 && strcmp(date1->month, date2->month) == 0 && strcmp(date1->day, date2->day) == 0) return 1;
    else return 0;
}

// funcao que verifica se a data1 esta entre a data2 e a data3, retornando 1 se estiver e 0 caso contrario
int between_dates(date date1, date date2, date date3){
    if(most_recent_date(date1, date2) == 1 && most_recent_date(date3, date1) == 1) return 1;
    else return 0;
}