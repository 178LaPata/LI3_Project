#include "users.h"
#include "date.h"


#include <glib.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
/*
    TODO:
    - ver o que e necessario validar 
    - fazer as funcoes de parse
    - criar hash table
    - dar free a tudo
    

*/
struct users {
    int id;
    char *name;
    char *email;
    int phone_number; // nao é definitivo
    Date birth_date;
    char *sex; 
    int passport;
    int country_code;
    char *adress;
    Date account_creation;
    enum pay_method pay_method; // ig maybe
    enum account_status account_status;

};

struct cat_users {
    GHashTable *users_hashtable;
};

// da free a um user e as suas variaveis
void delete_users(void *data){
    Users *users = (Users *) data;
    free(users->name);
    free(users->email);
    free(users->sex);
    free(users->adress);
    free(users);
}

Users *create_users(char *line){
    Users *users = malloc(sizeof(Users));
    char *buffer;
    int i = 0;
    int val = 1;
    while((buffer = strsep(&line, ";")) ! NULL){
        switch(i++){
            case 0:
                if(strlen(buffer) == 0){
                    users->name = strdup(buffer);
                    break;
                }
            case 1:
                if(strlen(buffer) == 0){
                    users->email = strdup(buffer);
                    break;
                }
            case 2:
                users->phone_number = verify_phoneNumber(buffer);
                if(users->phone_number == 0) val = 0;
                break;
            case 3:
                users->birth_date = verify_Date(buffer);
                if(users->birth_date == 0) val = 0;
                break;
            case 4:
                if(strlen(buffer) == 0){
                    users->sex = strdup(buffer);
                    break;
                }
            case 5:
                users->passport = verify_passport(buffer);
                if(users->passport == 0) val = 0;
                break;
            case 6:
                users->country_code = verify_countryCode(buffer);
                if(users->country_code == 0) val = 0;
                break;
            case 7:
                if(strlen(buffer) == 0){
                    users->adress = strdup(buffer);
                    break;
                }
            case 8:
                users->account_creation = verify_Date(buffer);
                if(users->account_creation == 0) val = 0;
                break;
            case 9:
                users->pay_method = verify_payMethod(buffer);
                if(users->pay_method == 0) val = 0; // mudar 0 para inativo ou wtv
                break;
            case 10:
                users->account_status = verify_accountStatus(buffer);
                if(users->account_status == 0) val = 0; // mudar 0 para inativo ou wtv
                break;
        }
    }
    if(val == 0){
        delete_users(users);
        return NULL;
    }
    return users;
}

void insert_users(CAT_USERS *cat_users, Users *users){
    g_hash_table_insert(cat_users->users_hashtable, users->id, users);
}

CAT_USERS *create_cat_users(char *entry_files){

    FILE *fp;
    char open[50];
    strcpy(open, entry_files);
    fp = fopen(strcat(open, "/users.csv"), "r");
    if (!fp) {
        perror("Error opening users.csv");
        return NULL;
    }

    CAT_USERS *cat_users = malloc(sizeof(struct cat_users));
    cat_users->users_hashtable = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, delete_users);

    char *line = NULL;
    size_t len = 0;

    clock_t start, end;
    double cpu_time_used;

    start = clock();
    while (getline(&line, &len, fp) > 0) {
        line[strcspn(line, "\n")] = 0;
        User *u = create_User(line);
        if (u != NULL) insert_User(cu, u);
    }
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time to parse users.csv", cpu_time_used);


    free(line);
    fclose(fp);

    return cu;
}
    
void delete_cat_users(CAT_USERS *cat_users){
    g_hash_table_destroy(cat_users->users_hashtable);
    free(cat_users);
}
