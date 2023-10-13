#include <glib.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct passengers {
    int flight id;
    int user_id;
};

struct cat_passengers {
    GHashTable *passengers_hashtable;
};

void delete_passengers(void *data){
    Passengers *passengers = (Passengers *) data;
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
                passengers->user_id = (int) strtol(buffer, (char **) NULL, 10);
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
    fp = fopen(strcat(open, "/passengers.csv"), "r");
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

    start = clock();
    while (getline(&line, &len, fp) > 0){
        line[strcspn(line, "\n")] = 0;
        Passengers *passengers = create_passengers(line);
        if(passengers != NULL) insert_passengers(cat_passengers, passengers);
    }
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time to parse passengers.csv: %f\n", cpu_time_used);

    free(line);
    fclose(fp);
    
    return cat_passengers;
}

void delete_cat_passengers(CAT_PASSENGERS *cat_passengers){
    g_hash_table_destroy(cat_passengers->passengers_hashtable);
    free(cat_passengers);
}