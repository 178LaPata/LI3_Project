#include "../libs/date.h"
#include "../libs/users.h"
#include "../libs/drivers.h"

#include <time.h>

struct xd_date {
    int day;
    int month;
    int year;
};

int get_date_day (XD_DATE date){
    return date -> day;
}

int get_date_month (XD_DATE date){
    return date -> month;
}

int get_date_year (XD_DATE date){
    return date -> year;
}

int set_date (XD_DATE date, char* day, char* month, char* year){
    date -> day   = atoi(day);
    date -> month = atoi(month);
    date -> year  = atoi(year);
}

int get_age (XD_DATE date){
    time_t rawtime;
    struct tm *get_localtime;
    char buffer [80];

    time (&rawtime);
    get_localtime = localtime(&rawtime);

    strftime(buffer,80,"%d", get_localtime);

    int goat = (get_localtime->tm_year+1900) - (date -> year);
    if ((get_localtime->tm_mon+1) < (date->month)){
        goat--;
    }else if ((get_localtime->tm_mon+1) == (date->month)){
            if ((get_localtime->tm_mday) < (date->day)){
                goat--;
            }
    }


    return goat;
}

// void print em que dou a estrutura da data -- falta


//testa se uma data é valida (return 0-> valida / return 1 -> nao valida)
int validar_date (XD_DATE data){
    
    XD_DATE date = malloc(sizeof(struct xd_date));
    
    if (date -> year >= 1990 && date->year <= 2022){

        if (date -> month >= 1 && date->month <= 12){

            if(date->day <= 0 && date->day >= 32){

                printf("Day is not valid.\n");
            
                return 1;    
            }            
        }
        else {
            
            printf("Month is not valid.\n");
            
            return 1;
        }
    } else{
        printf("Year is not valid.\n");   
        return 1;
    }    
    return 0;
} 


