#include "../includes/passengers.h"

struct passengers {
    char *flight_id;
    char *user_id;
};

struct cache_passengers {
    GHashTable *passengers_cache;
    GQueue *passengers_queue;
    int capacity;
};

void delete_passengers(void *data){
    Passengers *passengers = (Passengers *) data;
    free(passengers->flight_id);
    free(passengers->user_id);
    free(passengers);
}

void delete_cache_passengers(CACHE_PASSENGERS *cache_passengers){
    g_hash_table_destroy(cache_passengers->passengers_cache);
    g_queue_free(cache_passengers->passengers_queue);
    free(cache_passengers);
}

CACHE_PASSENGERS *create_new_cache_passengers(int capacity){
    CACHE_PASSENGERS *cache_passengers = malloc(sizeof(struct cache_passengers));
    cache_passengers->passengers_cache = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, delete_passengers);
    cache_passengers->passengers_queue = g_queue_new();
    cache_passengers->capacity = capacity;
    return cache_passengers;
}

void insert_cache_passengers(CACHE_PASSENGERS *cache_passengers, Passengers *passengers){
    if(g_hash_table_contains(cache_passengers->passengers_cache, passengers->user_id)){
        g_queue_remove(cache_passengers->passengers_queue, passengers);
        g_queue_push_head(cache_passengers->passengers_queue, passengers);
    }
    else{
        if(g_queue_get_length(cache_passengers->passengers_queue) == cache_passengers->capacity){
            Passengers *p = g_queue_pop_tail(cache_passengers->passengers_queue);
            g_hash_table_remove(cache_passengers->passengers_cache, p->user_id);
        }
        g_hash_table_insert(cache_passengers->passengers_cache, passengers->user_id, passengers);
        g_queue_push_head(cache_passengers->passengers_queue, passengers);
    }
}

Passengers *cache_passengers_lookup(CACHE_PASSENGERS *cache_passengers, char *id){
    Passengers *passengers = g_hash_table_lookup(cache_passengers->passengers_cache, id);
    if(passengers != NULL){
        g_queue_remove(cache_passengers->passengers_queue, passengers);
        g_queue_push_head(cache_passengers->passengers_queue, passengers);
    }
    return passengers;
}

Passengers *create_valid_passengers(char *line){
    Passengers *passengers = malloc(sizeof(Passengers));
    char *buffer;
    int i = 0;
    char *copy_line = strdup(line);

    passengers->flight_id = NULL;
    passengers->user_id = NULL;
    
    while((buffer = strsep(&line, ";")) != NULL){
        switch(i++){
            case 0:
                passengers->flight_id = strdup(buffer);
                break;
            case 1:
                passengers->user_id = strdup(buffer);
                break;
        }
    }
    free(copy_line);
    return passengers;
}

Passengers *copy_passengers(Passengers *passengers){
    Passengers *copy = malloc(sizeof(Passengers));
    copy->flight_id = strdup(passengers->flight_id);
    copy->user_id = strdup(passengers->user_id);
    return copy;
}


Passengers *create_passengers(char *line, CACHE_FLIGHTS *cache_flights, CACHE_USERS *cache_users){
    Passengers *passengers = malloc(sizeof(Passengers));
    char *buffer;
    int i = 0;
    int val = 1;
    char *copy_line = strdup(line);

    passengers->flight_id = NULL;
    passengers->user_id = NULL;
    
    while((buffer = strsep(&line, ";")) != NULL){
        switch(i++){
            case 0:
                if (strlen(buffer) == 0) val = 0;
                passengers->flight_id = strdup(buffer);
                Flights* fli = search_flight(cache_flights, passengers->flight_id);
                if (fli == NULL) val = 0;
                delete_flights(fli);
                break;
            case 1:
                if (strlen(buffer) == 0) val = 0;
                passengers->user_id = strdup(buffer);
                Users* user = search_user(passengers->user_id, cache_users);
                if (user == NULL) val = 0;
                delete_users(user);
                break;
        }
    }
    if (val == 0){
        validate_csv_error(copy_line, "passengers");
        delete_passengers(passengers);
        free(copy_line);
        return NULL;
    }
    
    free(copy_line);
    return passengers;
}

int create_passengers_valid_file(char *file, CACHE_FLIGHTS *cache_flights, CACHE_USERS *cache_users){
    FILE *fp = fopen(file, "r");
    if(!fp) return 0;

    char buffer[1000000];
    char *buffer2 = NULL;

    char *linha = "flight_id;user_id";
    validate_csv_error(linha, "passengers");

    clock_t start, end;
    double cpu_time_used;
    start = clock();

    FILE *fp2 = fopen("entrada/passengers_valid.csv", "w");
    if(!fp2) return 0;

    if(fgets(buffer, sizeof(buffer), fp) == NULL){
        perror("fgets failed");
        return -1;
    }

    while (fgets(buffer, 1000000, fp)) {
        buffer2 = strdup(buffer); 
        buffer2[strcspn(buffer2, "\n")] = '\0';
        Passengers *p = create_passengers(buffer2, cache_flights, cache_users);
        if(p) {
            fprintf(fp2, "%s", buffer);
            delete_passengers(p);
        }
        free(buffer2);
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time to parse passengers.csv: %f\n", cpu_time_used);
    fclose(fp);
    fclose(fp2);
    return 0;
}


int get_number_passengers(char *flight_id){
    FILE *fp = fopen("entrada/passengers_valid.csv", "r");
    if(!fp) return 0;

    char buffer[1000000];
    char *buffer2 = NULL;  
    char *original_buffer2 = NULL;  

    int i = 0;
    while (fgets(buffer, 1000000, fp) != NULL) {
        buffer2 = strdup(buffer);
        original_buffer2 = buffer2;  
        char *id = strsep(&buffer2, ";");
        if (strcmp(id, flight_id) == 0) {
            i++;
        }
        free(original_buffer2); 
    }
    fclose(fp);
    return i;
}

Passengers *search_passenger(CACHE_PASSENGERS *cache_passengers, char *user_id){
    Passengers *passengers = cache_passengers_lookup(cache_passengers, user_id);
    if(passengers == NULL){
        FILE *fp = fopen("entrada/passengers_valid.csv", "r");
        if(!fp) return NULL;

        char buffer[1000000];
        int val = 0;

        while (fgets(buffer, 1000000, fp) != NULL) {
            int aux = strchr(buffer, ';') - buffer;
            if(strncmp(user_id, buffer, aux) == 0) {
                passengers = create_valid_passengers(buffer);
                insert_cache_passengers(cache_passengers, passengers);
                val = 1;
            }
        }
        fclose(fp);
        if(val == 0) return NULL;
    }
    return copy_passengers(passengers);
}

