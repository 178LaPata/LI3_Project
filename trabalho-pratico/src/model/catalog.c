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
    update_hash_user(cat->cat_reservations, cat->cat_users);
    return cat;
}

void delete_catalog(catalog *cat) {
    delete_cat_users(cat->cat_users);
    delete_cat_flights(cat->cat_flights);
    delete_cat_reservations(cat->cat_reservations);
    free(cat);
}

void update_hash_user(CAT_RESERVATIONS *r, CAT_USERS *u){
    GHashTableIter iter;
    gpointer key, value;

    GList *keys_to_remove = NULL;
    char *line = NULL;

    g_hash_table_iter_init(&iter, get_reservations_hashtable(r));
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        Reservations *reservations = (Reservations *) value;
        char *userID = get_user_id(reservations);
        Users *user = get_users(u, userID);
        if (user == NULL) {
            keys_to_remove = g_list_prepend(keys_to_remove, g_strdup(key));
            line = reservations_to_line(reservations);
            validate_csv_error(line, "reservations");
        } else {
            add_reservations_total(user, 1);
            add_spent_total(user, get_total_price(reservations));
        }
    }

    for (GList *l = keys_to_remove; l != NULL; l = l->next) {
        g_hash_table_remove(get_reservations_hashtable(r), l->data);
        g_free(l->data);
    }
    g_list_free(keys_to_remove);
}

Users *query1_users_aux(catalog *cat, char *id){
    return get_users(cat->cat_users, id);
}

Reservations *query1_reservations_aux(catalog *cat, char *id){
    return get_reservations(cat->cat_reservations, id);
}

Flights *query1_flights_aux(catalog *cat, char *id){
    return get_flights(cat->cat_flights, id);
}

double query3_aux(catalog *cat, char *id){
    return calculate_average_rating(cat->cat_reservations, id);
}

GList *query4_aux(catalog *cat, char *hotel_id){
    return sort_reservations_data(cat->cat_reservations, hotel_id);
}

GList *query5_aux(catalog *cat, char *origin, datetime beginD, datetime endD){
    return sort_flights_data(cat->cat_flights, origin, beginD, endD);
}

int query8_aux(catalog *cat, char *hotel_id, date begin, date end){
    return calcular_receita_total(cat->cat_reservations, hotel_id, begin, end);
}

