#include "../libs/users.h"
#include "../libs/date.h"

struct xd_user {
    char* username;
    char* name;
    char* gender;
    XD_DATE birth_date;
    XD_DATE account_creation; 
    char* pay_method;
    char* account_status;
};

char* get_user_username (XD_USER user){
    return user -> username;
}

char* get_user_name (XD_USER user){
    return user -> name;
}

char* get_user_gender (XD_USER user){
    return user -> gender;
} 

XD_DATE get_user_birth_date (XD_USER user){
    return user -> birth_date;
}

XD_DATE get_user_account_creation (XD_USER user){
    return user -> account_creation;
}

char* get_user_pay_method (XD_USER user){
    return user -> pay_method;
}

char* get_user_account_status (XD_USER user){
    return user -> account_status;
}

int print_user_infos (XD_USER user){
    if(!user)
        return 0;
    printf("%s;", user -> username);
    printf("%s;", user -> name);
    printf("%s;", user -> gender);
    printf("%d/%d/%d;", user -> birth_date -> day, user -> birth_date -> month, user -> birth_date -> year); 
    printf("%d/%d/%d;", user -> account_creation -> day, user -> account_creation -> month, user -> account_creation -> year); 
    printf("%s;", user -> pay_method);
    printf("%s \n", user -> account_status);
    return 1;
}

int write_user_infos (FILE *file, XD_USER user){
    if(!user)
        return 0;
    fprintf(file, "%d;", user -> username);
    fprintf(file, "%s;", user -> name);
    fprintf(file, "%s;", user -> gender);
    fprintf(file, "%d/%d/%d;", user -> birth_date -> day, user -> birth_date -> month, user -> birth_date -> year); 
    fprintf(file, "%d/%d/%d;", user -> account_creation -> day, user -> account_creation -> month, user -> account_creation -> year); 
    fprintf(file, "%d;", user-> pay_method);
    fprintf(file, "%d;", user-> account_status);
    fputc('\n', file); 
    return 1;
}

int set_user_username (XD_USER user, char* line){
    user -> username = strdup(line);
    return strlen(line) > 0;
}

int set_user_name (XD_USER user, char* line){
    user -> name = strdup(line);
    return strlen(line) > 0;
}

int set_user_gender (XD_USER user, char* line){
    user -> gender = strdup(line);
    return strlen(line) > 0;
}

int set_user_birth_date (XD_USER user, char* line){
    char* bufferbd;
    if((bufferbd = strsep(&line, "/\n")) != NULL){  
      
        user -> birth_date -> day = atol(bufferbd);
    } 
    if((bufferbd = strsep(&line, "/\n")) != NULL){  
      
        user -> birth_date -> month = atol(bufferbd);
    }
    if((bufferbd = strsep(&line, "/\n")) != NULL){  
      
        user -> birth_date -> year = atol(bufferbd);
    } 
    return strlen(line) > 0;
}

int set_user_account_creation (XD_USER user, char* line){
    char* bufferac;
    if((bufferac = strsep(&line, "/\n")) != NULL){  
      
        user -> birth_date -> day = atol(bufferac);
    } 
    if((bufferac = strsep(&line, "/\n")) != NULL){  
      
        user -> birth_date -> month = atol(bufferac);
    }
    if((bufferac = strsep(&line, "/\n")) != NULL){  
      
        user -> birth_date -> year = atol(bufferac);
    }   
    return strlen(line) > 0;
}

int set_user_pay_method (XD_USER user, char* line){
    user -> pay_method = strdu(line);
    return strlen(line) > 0;
}

int valid_user_account (char status){
    if ((status == "active") || (status == "inactive")) return 1;
    else return 0;
}

int set_user_account_status (XD_USER user, char status){
    if (valid_user_account(status)) user -> account_status = status;
}

XD_USER build_user (char* line){
    XD_USER user = malloc(sizeof(struct xd_user));
    int i = 0;
    int val = 1;
    char* buffer;
    while ((buffer = strsep(&line, ";\n")) != NULL){
        switch (i++){
            case 0: 
                val = set_user_username(buffer, user);
                break;
            case 1:
                val = set_user_name(buffer, user);
                break;
            case 2:
                val = set_user_gender(buffer, user);
                break;
            case 3: 
                val = set_user_birth_date(buffer, user);
                break;
            case 4:
                val = set_user_account_creation(buffer, user);
                break;
            case 5:
                val = set_user_pay_method(buffer, user);
                break;
            case 6: 
                val = set_user_account_status(buffer, user);
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

