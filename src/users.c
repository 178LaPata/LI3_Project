#include "../libs/users.h"
#include "../libs/date.h"

#include <glib.h>

struct xd_user {
    char* username;
    char* name;
    char gender;
    XD_DATE birth_date;
    XD_DATE account_creation; 
    char* pay_method;
    char* account_status;
};

struct xd_user_ht{
    GHashTable* xd_user_hash;
};

char* get_user_username (XD_USER user){
    return user -> username;
}

char* get_user_name (XD_USER user){
    return user -> name;
}

char get_user_gender (XD_USER user){
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
    printf("%c;", user -> gender);
    printf("%d/%d/%d;", get_date_day(user -> birth_date), get_date_month(user -> birth_date), get_date_year(user -> birth_date)); 
    printf("%d/%d/%d;", get_date_day(user -> account_creation), get_date_month(user -> account_creation), get_date_year(user -> account_creation));
    printf("%s;", user -> pay_method);
    printf("%s \n", user -> account_status);
    return 1;
}

int write_user_infos (FILE *file, XD_USER user){
    if(!user)
        return 0;
    fprintf(file, "%s;", user -> username);
    fprintf(file, "%s;", user -> name);
    fprintf(file, "%c;", user -> gender);
    fprintf(file, "%d/%d/%d;", get_date_day(user -> birth_date), get_date_month(user -> birth_date), get_date_year(user -> birth_date)); 
    fprintf(file, "%d/%d/%d;", get_date_day(user -> account_creation), get_date_month(user -> account_creation), get_date_year(user -> account_creation)); 
    fprintf(file, "%s;", user-> pay_method);
    fprintf(file, "%s;", user-> account_status);
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

void set_user_gender (XD_USER user, char line){
    user -> gender = line;
}

int set_user_birth_date (XD_USER user, char* line){
    char* bufferbd;
    if((bufferbd = strsep(&line, "/\n")) != NULL){  
      
        get_date_day(user -> birth_date) = atoi(bufferbd);
    } 
    if((bufferbd = strsep(&line, "/\n")) != NULL){  
      
        get_date_month(user -> birth_date) = atoi(bufferbd);
    }
    if((bufferbd = strsep(&line, "/\n")) != NULL){  
      
        get_date_year(user -> birth_date) = atoi(bufferbd);
    }   
    return strlen(line) > 0;
}

int set_user_account_creation (XD_USER user, char* line){
    char* bufferac;
    if((bufferac = strsep(&line, "/\n")) != NULL){  
      
        get_date_day(user -> account_creation) = atoi(bufferac);
    } 
    if((bufferac = strsep(&line, "/\n")) != NULL){  
      
        get_date_month(user -> account_creation) = atoi(bufferac);
    }
    if((bufferac = strsep(&line, "/\n")) != NULL){  
      
        get_date_year(user -> account_creation) = atoi(bufferac);
    }   
    return strlen(line) > 0;
}

int set_user_pay_method (XD_USER user, char* line){
    user -> pay_method = strdup(line);
    return strlen(line) > 0;
}

int valid_user_account (char* status){
    if (strcmp(status, "active") || strcmp(status, "inactive")) return 1;
    else return 0;
}

int set_user_account_status (XD_USER user, char* status){
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
    return user;
}
}

XD_USER_HT* create_userHt(char* file_ent){
  FILE *f;
  char open[50];

  f = fopen("users.csv", "r");

  if (!f){
    perror("Erro");
    return NULL;
  }

  XD_USER_HT* new = malloc (sizeof(struct xd_user_ht));
  new -> xd_user_hash = g_hash_table_new(g_str_hash, g_str_equal);

  char line[1000];
  int buffer_size = 1000;

  while(fgets(line, buffer_size, f)) {
      XD_USER user = build_user(strdup(line));
      if (user != NULL) g_hash_table_insert(new -> xd_user_hash, user -> username, user);
      printf("%s\n", line);
}
  fclose(f);
  return new;
}


