#include "../includes/catalog.h"

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

char *query1(char *input, catalog *cat){
    char *output;
    if(verify_only_numbers(input)==1){
        Flights *fli = query1_flights_aux(cat, input);
        if (fli) output = display_flights(fli, input);
    } else {
        if(strncmp(input, "Book", 4)==0){
            Reservations *r = query1_reservations_aux(cat, input);
            if (r) output = display_reservations(r, input);
        } else {
            Users *user = query1_users_aux(cat, input);
            if (user) output = display_users(user, input);
        }
    }
    return output;
}


void run_queries(char *queries_path, catalog *cat, int query){
    int i = (int) strtol(strsep(&queries_path, " "), (char **) NULL, 10);
    switch(i){
        case 1:
            if(queries_path[1] == '0') {
                //if(queries_path[2] == 'F') {
                //    char *arg_query = strsep(&queries_path, " ");
                //    write_to_file_mul_line(query10F(arg_query, cat), query);
                //}
                //else{
                //    char *arg_query = strsep(&queries_path, " ");
                //    write_to_file_one_line(query10(arg_query, cat), query);
                //}                
                break;
            } else if(queries_path[1] == 'F') {
                char *arg_query = strsep(&queries_path, " ");
                write_to_file_mul_line(query1F(arg_query, cat), query);
            }
            else{
                char *arg_query = strsep(&queries_path, " ");
                write_to_file_one_line(query1(arg_query, cat), query);
            }
            break;
        case 2:

    }
}

int run_batch(char* inputs_path, char* queries_path) {
    catalog *cat = create_catalog(inputs_path);
    system("exec rm -rf Resultados/*");

    FILE *fp;
    fp = fopen(queries_path, "r");
    if (!fp) {
        perror("Error");
        return -1;
    }

    char *line = NULL;
    size_t len = 0;
    int op = 1;

    while (getline(&line, &len, fp) != -1) {
        line[strcspn(line, "\n")] = 0;
        run_queries(line, cat, op);
        op++;
    }

    free(line);
    fclose(fp);
    delete_catalog(cat);
    return 0;
}