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

// Função usada para dar print das informações do user
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

// Função usada para dar write as informações do user
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

// Funçao utilizada para preencher o username
int set_user_username (XD_USER user, char* line){
    user -> username = strdup(line);
    return strlen(line) > 0;
}

// Funçao utilizada para preencher o name
int set_user_name (XD_USER user, char* line){
    user -> name = strdup(line);
    return strlen(line) > 0;
}

// Funçao utilizada para preencher o gender
int set_user_gender (XD_USER user, char *line){
    user -> gender = line[0];
    return strlen(line) > 0;
}

// Funçao utilizada para preencher a birth_date
int set_user_birth_date (XD_USER user, char* line){
    char* bufferbd1;
    char* bufferbd2;
    char* bufferbd3;
    if((bufferbd1 = strsep(&line, "/\n")) == NULL){  
        return -1;
    } 
    if((bufferbd2 = strsep(&line, "/\n")) == NULL){  
        return -1;
    }
    if((bufferbd3 = strsep(&line, "/\n")) == NULL){  
        return -1;
    }   
    set_date(user -> birth_date, bufferbd1, bufferbd2, bufferbd3);
    return strlen(line) > 0;
}

// Funçao utilizada para preencher a account_creation
int set_user_account_creation (XD_USER user, char* line){
    char* bufferac1;
    char* bufferac2;
    char* bufferac3;
    if((bufferac1 = strsep(&line, "/\n")) == NULL){  
        return -1;
    } 
    if((bufferac2 = strsep(&line, "/\n")) == NULL){  
        return -1;
    }
    if((bufferac3 = strsep(&line, "/\n")) == NULL){  
        return -1;
    }   
    return strlen(line) > 0;
}

// Funçao utilizada para preencher o pay_method
int set_user_pay_method (XD_USER user, char* line){
    user -> pay_method = strdup(line);
    return strlen(line) > 0;
}

// Funçao utilizada para validar uma conta de utlizador
int valid_user_account (char* status){
    if (strcmp(status, "active") || strcmp(status, "inactive")) return 1;
    else return 0;
}

// Funçao utilizada para definir o status de uma conta
int set_user_account_status (XD_USER user, char* status){
    if (valid_user_account(status)) user -> account_status = status;
}

// Funçao usada para construir utilizador
XD_USER build_user (char* line){
    XD_USER user = malloc(sizeof(struct xd_user));
    int i = 0;
    int val = 1;
    char* buffer;
    while ((buffer = strsep(&line, ";\n")) != NULL){
        switch (i++){
            case 0: 
                val = set_user_username(user, buffer);
                break;
            case 1:
                val = set_user_name(user, buffer);
                break;
            case 2:
                val = set_user_gender(user, buffer);
                break;
            case 3: 
                val = set_user_birth_date(user, buffer);
                break;
            case 4:
                val = set_user_account_creation(user, buffer);
                break;
            case 5:
                val = set_user_pay_method(user, buffer);
                break;
            case 6: 
                val = set_user_account_status(user, buffer);
                break;
            default:
                val = 1;
                break;
        }
    return user;
}
}

// Funçao usada para criar a hash table dos users
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
      if (user != NULL) g_hash_table_insert(new -> xd_user_hash, user -> username, user); // recebe a hash table, a key e o valor que quero guardar
      printf("%s\n", line);
}
  fclose(f);
  return new;
}


