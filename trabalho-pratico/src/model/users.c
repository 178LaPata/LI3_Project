#include "../../includes/model/users.h"
#include "../../includes/model/date.h"
#include "../../includes/model/valid.h"



#include <glib.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct users {
    int id;
    char *name;
    char *email;
    int phone_number;
    Date birth_date;
    char *sex; 
    int passport;
    char *country_code;
    char *adress;
    Date account_creation;
    enum pay_method pay_method;
    enum account_status account_status;
};

struct cat_users {
    GHashTable *users_hashtable;
};

void delete_users(void *data){
    Users *users = (Users *) data;
    free(users->name);
    free(users->email);
    free(users->sex);
    free(users->country_code);
    free(users->adress);
    free(users);
}

Users *create_users(char *line){
    Users *users = malloc(sizeof(Users));
    char *buffer;
    int i = 0;
    int val = 1;
    while((buffer = strsep(&line, ";")) != NULL){
        switch(i++){
            case 0:
                if (strlen(buffer) == 0) val = 0;
                    users->name = strdup(buffer);
                    break;
            case 1:
                if (strlen(buffer) == 0) val = 0;
                    users->email = strdup(buffer);
                    break;
            case 2:
                users->phone_number = verify_phoneNumber(buffer);
                if(users->phone_number == 0) val = 0;
                break;
            case 3:
                users->birth_date = verify_Date(buffer);
                if(users->birth_date == 0) val = 0;
                break;
            case 4:
                // usar funcao tolower e strcmp
                if (strlen(buffer) == 0) val = 0;
                    users->sex = strdup(buffer);
                    break;
            case 5:
                //users->passport = verify_passport(buffer);
                if(users->passport == 0) val = 0;
                break;
            case 6:
                // usar funcao tolwer e strcmp com a primeira e ultima do abecedario  
                if (strlen(buffer) == 0) val = 0;
                    users->country_code == strdup(buffer);
                    break;
            case 7:
                if(strlen(buffer) == 0) val = 0;
                    users->adress = strdup(buffer);
                    break;
            case 8:
                users->account_creation = verify_Date(buffer);
                if(users->account_creation == 0) val = 0;
                break;
            case 9:
                users->pay_method = verify_payMethod(buffer);
                if(users->pay_method == noPayMethod) val = 0;
                break;
            case 10:
                users->account_status = verify_accountStatus(buffer);
                if(users->account_status == NoStatus) val = 0;
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
        Users *u = create_users(line);
        if (u != NULL) insert_users(cat_users, u);
    }
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time to parse users.csv", cpu_time_used);


    free(line);
    fclose(fp);

    return cat_users;
}
    
void delete_cat_users(CAT_USERS *cat_users){
    g_hash_table_destroy(cat_users->users_hashtable);
    free(cat_users);
}
