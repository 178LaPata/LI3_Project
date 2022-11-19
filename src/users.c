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

struct xd_users_array {
    int max_size;
    int size;
    XD_USERS *array;
};

int get_users_array_max_size (XD_USERS_ARRAY array){
    return array -> max_size;
}
int get_users_array_size (XD_USERS_ARRAY array){
    return array -> size;
}

XD_USERS* get_users_array (XD_USERS_ARRAY array){
    return array -> array;
}

XD_USERS get_users_index (XD_USERS_ARRAY array, int k){
    if (k >= array -> size) return NULL;
    return array -> array[k];
}

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
    if (strlen(line)<19) return 0;    

    sscanf(line, "%d-%d-%d %d:%d:%d", &user->account_creation.tm_year, &user->account_creation.tm_mon, &user->account_creation.tm_mday, &user->account_creation.tm_hour, &user->account_creation.tm_min, &user->account_creation.tm_sec);
    user->account_creation.tm_year -= 1900;
    user->account_creation.tm_mon -= 1;
    user->account_creation.tm_isdst = 1;
    user->account_creation.tm_wday = 3;
    user->account_creation.tm_yday = (user->account_creation.tm_mon * 30) + user->account_creation.tm_mday;

    return (line[4]!='/') && (is_valid_date(user->account_creation));
}

int set_users_pay_method (XD_USERS user, char* line){
    int 
}



