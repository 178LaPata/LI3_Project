#include "../../includes/model/users.h"
#include "../../includes/model/date.h"
#include "../../includes/model/valid.h"

#include <glib.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

struct users {
    char *id;
    char *name;
    char *email;
    char *phone_number;
    date birth_date;
    char *sex; 
    char *passport;
    char *country_code;
    char *adress;
    datetime account_creation;
    enum pay_method pay_method;
    enum account_status account_status;

    int flights_total;
    int reservations_total;
    int spent_total;
};

struct cat_users {
    GHashTable *users_hashtable;
};

void delete_users(void *data){
    Users *users = (Users *) data;
    free(users->id);
    free(users->name);
    free(users->email);
    free(users->sex);
    free(users->passport);
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
                users->id = strdup(buffer);
                break;
            case 1:
                if (strlen(buffer) == 0) val = 0;
                users->name = strdup(buffer);
                break;
            case 2:
                users->email = verify_email(buffer);
                if (strlen(buffer) == 0) val = 0;
                break;
            case 3:
                if (strlen(buffer) == 0) val = 0;
                users->phone_number = verify_phone_number(buffer);
                break;
            case 4:
                if(strlen(buffer) == 0) val = 0;
                users->birth_date = valid_date(buffer); 
                break;
            case 5:
                if (strlen(buffer) == 0) val = 0;
                users->sex = strdup(buffer);
                if (tolower(buffer[0]) != 'm' && tolower(buffer[0]) != 'f') val = 0;
                break;
            case 6:
                users->passport = verify_passport(buffer);
                if (users->passport == NULL) val = 0;
                break;
            case 7:
                if (strlen(buffer) != 2 || !isalpha(buffer[0]) || !isalpha(buffer[1])) val = 0; 
                users->country_code = strdup(buffer);
                break;
            case 8:
                if(strlen(buffer) == 0) val = 0;
                users->adress = strdup(buffer);
                break;
            case 9:
                users->account_creation = valid_date_time(buffer);
                break;
            case 10:
                users->pay_method = verify_payMethod(buffer); 
                if(users->pay_method == noPayMethod) val = 0;
                break;
            case 11:
                users->account_status = verify_accountStatus(buffer);
                if(users->account_status == NoStatus) val = 0;
                break;
        }
    }

    if(val == 0){
        delete_users(users);
        return NULL;
   }

   users->flights_total = 0;
   users->reservations_total = 0;
   users->spent_total = 0;

   return users;
}


void insert_users(CAT_USERS *cat_users, Users *users){
    g_hash_table_insert(cat_users->users_hashtable, users->id, users);
}

CAT_USERS *create_cat_users(char *entry_files){

    FILE *fp;
    char open[50];
    strcpy(open, entry_files);
    fp = fopen(open, "r");
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

    int first_line = 1;

    start = clock();

    while (getline(&line, &len, fp) > 0) {
        if (first_line) {
            first_line = 0;
            continue;
        }
        line[strcspn(line, "\n")] = 0;
        Users *u = create_users(line);
        if (u != NULL) insert_users(cat_users, u);
    }

    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time to parse users.csv: %f\n", cpu_time_used);

    printf("Number of users: %d\n", g_hash_table_size(cat_users->users_hashtable));

    free(line);
    fclose(fp);

    return cat_users;
}
    
void delete_cat_users(CAT_USERS *cat_users){
    g_hash_table_destroy(cat_users->users_hashtable);
    free(cat_users);
}

//char *users_profile(CAT_USERS *cat_users, char *id) {
//    Users *users = g_hash_table_lookup(cat_users->users_hashtable, id);
//
//    if (users == NULL || users->account_status == Inactive) return NULL;  
//
//    char *name = users->name;
//    char *sex = users->sex;
//    int age = calculate_age(users->birth_date);
//    char *country_code = users->country_code;
//    int number_of_flights = users->flights_total;
//    int number_of_reservations = users->reservations_total;
//    int total_spent = users->spent_total;
//
//    char *answer = malloc(snprintf(NULL, 0, "%s;%s;%d;%s;%d;%d;%d\n", name, sex, age, country_code, number_of_flights, number_of_reservations, total_spent) + 1);
//
//    snprintf(answer, 100, "%s;%s;%d;%s;%d;%d;%d\n", name, sex, age, country_code, number_of_flights, number_of_reservations, total_spent);
//
//    return answer;
//}
