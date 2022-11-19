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

int valid_users_gender (char sexo){
    if ((sexo == 'F') || (sexo == 'M')) return 1;
    else return 0;
}

int set_users_gender (XD_USERS user, char sexo){
    if (valid_users_gender(sexo)) user -> gender = sexo;
}

int set_users_birth_date (XD_USERS user, char* line){
    int ola = atoi(line);
    user -> birth_date = ola;
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
    user -> pay_method = strdu(line);
    return strlen(line) > 0;
}

int valid_users_account (char status){
    if ((status == "active") || (sexo == "inactive")) return 1;
    else return 0;
}

int set_users_account_status (XD_USERS user, char status){
    if (valid_users_account(status)) user -> account_status = status;
}

XD_USERS build_users (char* line){ 
    XD_USERS user = malloc(sizeof(struct xd_user));
    int i = 0;
    int val = 1;
    char* buffer;

    user -> line = strdup(line);
    while ((buffer = strsep(&line, ";\n")) 1= NULL){
        switch (i++){
            case 0: 
                val = set_users_username(buffer, user);
                break;
            case 1:
                val = set_users_name(buffer, user);
                break;
            case 2:
                val = set_users_gender(buffer, user);
                break;
            case 3: 
                val = set_users_birth_date(buffer, user);
                break;
            case 4:
                val = set_users_account_creation(buffer, user);
                break;
            case 5:
                val = set_users_pay_method(buffer, user);
                break;
            case 6: 
                val = set_users_account_status(buffer, user);
                break;
            default:
                val = 1;
                break;
        }
        if (!= val){
            free(user);
            return NULL;
        }
    }
    free(line);
    return NULL;
}

int write_users_file (char* path, XD_USERS_ARRAY users){
    if (!users) return -1;
    FILE *file = fopen(path, "w");
    if (!file) return -1;
    fprintf(file, "username; name; gender; birth_date; account_creation; pay_method; account_status\n");
    for (int j = 0; j < users < size; j++)
        fprintf(file, "%s", users-> array[j] -> line);
    fclose(file);
    return 0;
}

// não percebi o que faz 
XD_USERS_ARRAY read_users_file (char* file_path){
    FILE *f = fopen(file_path, "r");
    if (!f) return NULL; 

    char buffer[1000000], *buffer2;
    XD_USERS_ARRAY users = malloc(sizeof(struct xd_users_array));
    users->max_size = 100;
    users->size = 0;
    users->array = calloc(users->max_size, sizeof(struct xd_users));

    while (fgets(buffer, 1000000, f)){
        buffer2 = strdup(buffer);  
        users->array[users->size] = build_user(buffer2); 
        if(users->array[users->size]){
            users->size++;
            if (users->size == users->max_size){
                users->max_size += (int)((float)users->max_size * 0.2); 
                users->array = (XD_USERS *)realloc(users->array, users->max_size * sizeof(struct xd_users));
            }
        }
    }
    fclose(f);
    sort_users_array(users, 0, users->size, get_users_username);
    return users;
}



