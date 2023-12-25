#include "../../includes/model/catalog.h"

typedef struct catalog {
    CAT_USERS *cat_users;
    CAT_FLIGHTS *cat_flights;
    CAT_RESERVATIONS *cat_reservations;
    CAT_PASSENGERS *cat_passengers;
} catalog; 

char* pointer_file (char *path, char *file) {
    char *file_name = malloc(strlen(path) + strlen(file) + 2);
    if (file_name == NULL) {
        return NULL;
    }

    file_name[0] = '\0';

    strcat(file_name, path);
    if (path[strlen(path) - 1] != '/') {
        strcat(file_name, "/");
    }
    strcat(file_name, file);

    return file_name; 
}

catalog *create_catalog(char *entry_files) {
    char *users = pointer_file(entry_files,"users.csv"), *flights =  pointer_file(entry_files,"flights.csv"), *reservations = pointer_file(entry_files,"reservations.csv"), *passengers = pointer_file(entry_files,"passengers.csv");
    catalog *cat = malloc(sizeof(struct catalog));
    cat->cat_flights = create_cat_flights(flights);
    cat->cat_users = create_cat_users(users);
    cat->cat_reservations = create_cat_reservations(reservations, cat->cat_users);
    cat->cat_passengers = create_cat_passengers(passengers, cat->cat_users, cat->cat_flights);
    update_values_reservations(cat->cat_reservations);
    update_values_flights(cat->cat_flights, cat->cat_passengers);
    update_hash_userRes(cat->cat_reservations, cat->cat_users);
    update_hash_userPas(cat->cat_passengers, cat->cat_users);
    free(users);
    free(flights);
    free(reservations);
    free(passengers);
    return cat;
}

void delete_catalog(catalog *cat) {
    delete_cat_users(cat->cat_users);
    delete_cat_flights(cat->cat_flights);
    delete_cat_reservations(cat->cat_reservations);
    delete_cat_passengers(cat->cat_passengers);
    free(cat);
}

// funcao que da update aos valores de um user a partir das reservas
void update_hash_userRes(CAT_RESERVATIONS *r, CAT_USERS *u){
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, get_reservations_hashtable(r));
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        Reservations *reservations = (Reservations *) value;
        char *userID = get_user_id(reservations);
        Users *user = get_users(u, userID);
        if(!user) continue;
        add_reservations_total(user, 1);
        add_spent_total(user, get_total_price(reservations));
    }
}

// funcao que da update aos valores de um user a partir dos passageiros
void update_hash_userPas(CAT_PASSENGERS *p, CAT_USERS *u){
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, get_passengers_hashtable(p));
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        for (int i = 0; i < get_num_passengers_list(p, key); i++) {
            char *userID = get_user_from_list(p, key, i);
            Users *user = get_users(u, userID);
            add_flights_total(user, 1);
        }
    }
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

GList *query5_aux(catalog *cat, char *origin, Datetime beginD, Datetime endD){
    return sort_flights_data(cat->cat_flights, origin, beginD, endD);
}

GList *query6_aux(catalog *cat, char *year){
    return sort_flights_num_passengers(cat->cat_flights, year);    
}

int query8_aux(catalog *cat, char *hotel_id, Date begin, Date end){
    return calcular_receita_total(cat->cat_reservations, hotel_id, begin, end);
}

GList *query9_aux(catalog *cat, char *user_id){
    return sort_users_id(cat->cat_users, user_id);
}