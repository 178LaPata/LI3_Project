#include "../libs/users.h"

struct xd_users {
    char *username;
    char *name;
    char *gender;
    char *birth_date;
    char *account_creation;
    char *pay_method;
    char *account_status;
};

struct xd_users_array {     // Estrutura para o array de utilizadores
    int max_size;           // Tamanho máximo de utilizadores que cabem no array
    int size;               // Número de utilizadores no array
    XD_USERS *array;        // Array de utilizadores
};

int users_array_max_size (XD_USERS_ARRAY array){
    return array -> max_size;
}

int users_array_size (XD_USERS_ARRAY array){
    return array -> size;
}

XD_USERS* users_array (XD_USERS_ARRAY array){
    return array -> array;
}

XD_USERS users_index (XD_USERS_ARRAY array, int i){
    if (i >= array -> size) return NULL;
    return array -> array[i];
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

char* get_users_birth_date (XD_USERS user){
    return user -> birth_date;
}

char* get_users_account_creation (XD_USERS user){
    return user -> account_creation;
}

char* get_users_pay_method (XD_USERS user){
    return user -> pay_method;
}

char* get_users_account_status (XD_USERS user){
    return user -> account_status;
}












