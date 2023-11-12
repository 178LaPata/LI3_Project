#include "../../includes/model/catalog.h"
typedef struct catalog {
    CAT_USERS *cat_users;
    CAT_FLIGHTS *cat_flights;
    CAT_RESERVATIONS *cat_reservations;
    CAT_PASSENGERS *cat_passengers;
} catalog;

char* pointer_file (char *path, char *file){
    char *file_name = malloc(strlen(path) + strlen(file) + 2);
    
    strcat(file_name, path);
    if (path[strlen(path)] != '/')
        strcat(file_name,"/");
    strcat(file_name, file);
    return file_name; 
}

catalog *create_catalog(char *entry_files) {
    char *users = pointer_file(entry_files,"users.csv"), *flights =  pointer_file(entry_files,"flights.csv"), *reservations = pointer_file(entry_files,"reservations.csv"), *passengers = pointer_file(entry_files,"passengers.csv");
    catalog *cat = malloc(sizeof(struct catalog));
    cat->cat_users = create_cat_users(users);
    cat->cat_flights = create_cat_flights(flights);
    cat->cat_reservations = create_cat_reservations(reservations);
    cat->cat_passengers = create_cat_passengers(passengers);
    update_values_users(cat->cat_users, cat->cat_passengers);
    return cat;
}

void delete_catalog(catalog *cat) {
    delete_cat_users(cat->cat_users);
    delete_cat_flights(cat->cat_flights);
    delete_cat_reservations(cat->cat_reservations);
    free(cat);
}
