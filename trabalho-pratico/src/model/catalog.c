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
    cat->cat_flights = create_cat_flights(flights);
    cat->cat_users = create_cat_users(users);
    cat->cat_reservations = create_cat_reservations(reservations);
    cat->cat_passengers = create_cat_passengers(passengers);
    update_values_reservations(cat->cat_reservations);
    update_values_users(cat->cat_users, cat->cat_passengers, cat->cat_reservations);
    update_values_flights(cat->cat_flights, cat->cat_passengers);
    return cat;
}

void delete_catalog(catalog *cat) {
    delete_cat_users(cat->cat_users);
    delete_cat_flights(cat->cat_flights);
    delete_cat_reservations(cat->cat_reservations);
    free(cat);
}

Users *query1_users_aux(catalog *cat, char *id){
    return get_users(cat->cat_users, id);
}

Reservations *query1_reservations_aux(catalog *cat, char *id){
    return get_reservations(cat->cat_reservations, id);
}

Flights *query1_flights_aux(catalog *cat, char *id){
    return get_flights(cat->cat_flights, atoi(id));
}

// funcao que calcula a classificação média de um hotel, a partir do id do hotel
double query3_aux(catalog *cat, char *id){
    return calculate_average_rating(cat->cat_reservations, id);
}

GList *query4_aux(catalog *cat, char *hotel_id){
    return sort_reservations_data(cat->cat_reservations, hotel_id);
}

GList *query5_aux(catalog *cat, char *origin, char *beginD, char *endD){
    return sort_flights_data(cat->cat_flights, origin, beginD, endD);
}