#include "../libs/users.h"
#include "../libs/date.h"

struct xd_users {
    char* line; 
    char* username;
    char* name;
    char gender;
    XD_DATE* birth_date;
    struct tm account_creation;
    char* pay_method;
    char* account_status;
};

char* get_users_username (XD_USERS user){
    return user -> username;
}

char* get_users_name (XD_USERS user){
    return user -> name;
}

char* get_users_gender (XD_USERS user){
    return user -> gender;
} 

XD_DATE* get_users_birth_date (XD_USERS user){
    return user -> birth_date;
}

struct tm get_users_account_creation (XD_USERS user){
    return user -> account_creation;
}

char* get_users_pay_method (XD_USERS user){
    return user -> pay_method;
}

char* get_users_account_status (XD_USERS user){
    return user -> account_status;
}

int set_users_username (XD_USERS user, char* line){
    user -> username = strdup(line);
    return strlen(line) > 0;
}

int set_users_name (XD_USERS user, char* line){
    user -> name = strdup(line);
    return strlen(line) > 0;
}

int set_users_gender (XD_USERS user, char* line){
    user -> gender = strdu(line);
    return strlen(line) > 0;
}

int set_users_birth_date (XD_USERS user, char* line){
    int ola = atoi(line);
    user -> date = ola;
    return (ola >= 0) && strlen(line) > 0;
}

int set_users_account_creation (XD_USERS user, char* line){
    if (strlen(line) ) return 0;

}



int set_created_at (char* line, GH_USER usr)  // Funçao utilizada para preencher o campo da data de criaçao
{
    if (strlen(line)<19) return 0;   // Se a linha tiver menos de 19 caracteres não tem informação suficente para fazer o parse


    //Coloca na data os valores segundo o formato especificado
    sscanf(line, "%d-%d-%d %d:%d:%d", &usr->created_at.tm_year, &usr->created_at.tm_mon, &usr->created_at.tm_mday, &usr->created_at.tm_hour, &usr->created_at.tm_min, &usr->created_at.tm_sec);
    usr->created_at.tm_year -= 1900; // Subtrai 1900 ao ano (porque na estrutura struct tm, o campo tm_year conta o numero de anos que passou desde 1900)
    usr->created_at.tm_mon -= 1;     // Subtrai 1 ao mes (porque na estrutura struct tm, o campo tm_mon conta o numero de meses que passou desde janeiro)
    usr->created_at.tm_isdst = 1;
    usr->created_at.tm_wday = 3;
    usr->created_at.tm_yday = (usr->created_at.tm_mon * 30) + usr->created_at.tm_mday;

    return (line[4]!='/') && (is_valid_date(usr->created_at));   // Retorna o valor que a função retorna, que é verdadeiro se estiver entre a data atual e 2005-07-04 00:00:00
}
