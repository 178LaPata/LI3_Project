#include "../../includes/model/users.h"
#include "../../includes/model/flights.h"
#include "../../includes/model/reservations.h"
#include "../../includes/model/passengers.h"

#include <glib.h>
#include <stdio.h>

char* pointer_file (char *path, char *file){
  char *file_name = malloc(strlen(path) + strlen(file) + 2); // + 2 por causa do \0 e pq n sabes se o path acaba em / ou nao
  
  strcat(file_name, path);
  if (path[strlen(path)] != '/')
    strcat(file_name,"/");
  strcat(file_name, file);

  return file_name; 
}

int str_is_num (char* str){
    unsigned i;
    int p=0;
    for(i=0; i<strlen(str); i++){
        if (str[i]<'0' || str[i]>'9'){
            p=1;
            return p;
        }
    }
    return p;
}

void print_hash_table(GHashTable *hash_table) {
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, hash_table);

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        g_print("Key: %s, Value: %s\n", (char *)key, (char *)value);
    }
}

int main (int argc, char **argv) {
    
    char *users = pointer_file(argv[1],"users.csv"), *flights =  pointer_file(argv[1],"flights.csv"), *reservations = pointer_file(argv[1],"reservations.csv"), *passengers = pointer_file(argv[1],"passengers.csv");
    CAT_USERS *cat_users = create_cat_users(users);
    CAT_FLIGHTS *cat_flights = create_cat_flights(flights);
    CAT_RESERVATIONS *cat_reservations = create_cat_reservations(reservations);
    //CAT_PASSENGERS *cat_passengers = create_cat_passengers(passengers);

    delete_cat_users(cat_users);
    delete_cat_flights(cat_flights);
    //delete_cat_reservations(cat_reservations); esta a dar erro
    //delete_cat_passengers(cat_passengers);

    free(users);
    free(flights);
    free(reservations);
    free(passengers);

    return 0;
}
