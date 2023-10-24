#include "../../includes/model/catalog.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>

typedef struct catalog {
    CAT_USERS *cat_users;
    CAT_FLIGHTS *cat_flights;
    CAT_RESERVATIONS *cat_reservations;
} catalog;

catalog *create_catalog(char *entry_files) {
    catalog *cat = malloc(sizeof(struct catalog));
    cat->cat_users = create_cat_users(entry_files);
    cat->cat_flights = create_cat_flights(entry_files);
    cat->cat_reservations = create_cat_reservations(entry_files);
    return cat;
}

void delete_catalog(catalog *cat) {
    delete_cat_users(cat->cat_users);
    delete_cat_flights(cat->cat_flights);
    delete_cat_reservations(cat->cat_reservations);
    free(cat);
}

// queries
char *q01_users(char *id, catalog *cat) {
    users_profile(cat->cat_users, id);
}

//char *q01_reservations(char *id, catalog *cat) {
//    Reservations *reservations = g_hash_table_lookup(cat->cat_reservations->reservations_hashtable, id);
//    reservations_profile(cat->cat_reservations, id);
//}
//
//char *q01_flights(int id, catalog *cat) {
//    Flights *flights = g_hash_table_lookup(cat->cat_flights->flights_hashtable, &id);
//    flights_profile(cat->cat_flights, id);
//}



// funcao parse queries
void parse_queries(char *line, catalog *cat, int output_num){

    int i = (int) strtol(strsep(&line, " "), (char **) NULL, 10);

    switch (i){
        case 1:
            char *id = strsep(&line, " ");
            break;
    }
}


int runBatch(char **input_file) {

    catalog *cat = create_catalog(input_file[1]);

    system("exec rm -rf Resultados/*");

    FILE *fp;
    fp = fopen(input_file[2], "r");
    if (!fp) {
        perror("Error");
        return -1;
    }

    char *line = NULL;
    size_t len = 0;
    int output_number = 1;

    while (getline(&line, &len, fp) != -1) {
        line[strcspn(line, "\n")] = 0;
        parse_queries(line, cat, output_number);
        output_number++;
    }

    free(line);
    fclose(fp);

    delete_catalog(cat);

    return 0;
}

