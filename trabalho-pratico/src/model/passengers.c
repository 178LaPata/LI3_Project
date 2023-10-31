#include "../../includes/model/passengers.h"

#include <glib.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct passengers {
    int flight_id;
    char *user_id;
};

struct cat_passengers {
    GHashTable *passengers_hashtable;
};

void delete_passengers(void *data){
    Passengers *passengers = (Passengers *) data;
    free(passengers->user_id);
    free(passengers);
}

Passengers *create_passengers(char *line){
    Passengers *passengers = malloc(sizeof(Passengers));
    char *buffer;
    int i = 0;
    int val = 1;
    while((buffer = strsep(&line, ";")) != NULL){
        switch(i++){
            case 0:
                if (strlen(buffer) == 0) val = 0;
                passengers->flight_id = (int) strtol(buffer, (char **) NULL, 10);
                break;
            case 1:
                if (strlen(buffer) == 0) val = 0;
                passengers->user_id = strdup(buffer);
                break;
        }
    }
    if (val == 0){
        free(passengers);
        return NULL;
    }
    return passengers;
}

void insert_passengers(CAT_PASSENGERS *cat_passengers, Passengers *passengers){
    g_hash_table_insert(cat_passengers->passengers_hashtable, &passengers->flight_id, passengers);
}

CAT_PASSENGERS *create_cat_passengers(char *entry_files){

    FILE *fp;
    char open[50];
    strcpy(open, entry_files);
    fp = fopen(open, "r");
    if (!fp) {
        perror("Error opening passengers.csv");
        return NULL;
    }

    CAT_PASSENGERS *cat_passengers = malloc(sizeof(CAT_PASSENGERS));
    cat_passengers->passengers_hashtable = g_hash_table_new_full(g_int_hash, g_int_equal, NULL, delete_passengers);

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
        Passengers *passengers = create_passengers(line);
        if(passengers != NULL){
            insert_passengers(cat_passengers, passengers);
        }
    }
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time to parse passengers.csv: %f\n", cpu_time_used);

    printf("Number of passengers: %d\n\n", g_hash_table_size(cat_passengers->passengers_hashtable));

    free(line);
    fclose(fp);
    
    return cat_passengers;
}

void delete_cat_passengers(CAT_PASSENGERS *cat_passengers){
    g_hash_table_destroy(cat_passengers->passengers_hashtable);
    free(cat_passengers);
}

int calculate_total_flights(CAT_PASSENGERS *cat_passengers, char *id){
    int total_flights = 0;
    GHashTableIter iter;
    gpointer key, value;
    //printf("id recebido: %s\n", id);
    g_hash_table_iter_init(&iter, cat_passengers->passengers_hashtable);
    while (g_hash_table_iter_next(&iter, &key, &value)){
        Passengers *passengers = (Passengers *) value;
        printf("username: %s flight: %d\n", passengers->user_id, passengers->flight_id);
        if(strcmp(passengers->user_id, id)==0){
            total_flights++;
            //printf("id %s\n", passengers->user_id);
        }
    }
    printf("user id: %s\n", id);
    printf("Total flights: %d\n\n", total_flights);
    return total_flights;
}
