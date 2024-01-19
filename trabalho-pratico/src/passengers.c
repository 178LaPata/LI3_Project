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
    if(g_hash_table_contains(cache_passengers->passengers_cache, passengers->flight_id)){
        g_queue_remove(cache_passengers->passengers_queue, passengers);
        g_queue_push_head(cache_passengers->passengers_queue, passengers);
    }
    else{
        if(g_queue_get_length(cache_passengers->passengers_queue) == cache_passengers->capacity){
            Passengers *p = g_queue_pop_tail(cache_passengers->passengers_queue);
            g_hash_table_remove(cache_passengers->passengers_cache, p->flight_id);
        }
        g_hash_table_insert(cache_passengers->passengers_cache, passengers->flight_id, passengers);
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

Passengers *create_passengers(char *line){
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
                if(verify_flight(passengers->flight_id) == 0) val = 0;
                break;
            case 1:
                if (strlen(buffer) == 0) val = 0;
                passengers->user_id = strdup(buffer);
                if(verify_user(passengers->user_id) == 0) val = 0;
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

int create_passengers_valid_file(char *file){
    FILE *fp = fopen(file, "r");
    if(!fp) return 1;

    char buffer[1000000];
    char *buffer2 = NULL;  

    char *linha = "flight_id;user_id";
    validate_csv_error(linha, "passengers");

    clock_t start, end;
    double cpu_time_used;
    start = clock();

    FILE *fp2 = fopen("entrada/passengers_valid.csv", "w");
    if (!fp2) return -1;
    // cria um array para guardar as linhas do ficheiro ordenadas pelo id do voo
    char **array = malloc(sizeof(char *) * 1000000);
    int i = 0;
    while (fgets(buffer, 1000000, fp)) {
        buffer[strcspn(buffer, "\n")] = 0;
        buffer2 = strdup(buffer);
        char *token = strtok(buffer, ";");
        char *id = strdup(token);
        array[i++] = id;
        free(buffer2);
    }
    // ordena o array pelo id do voo
    qsort(array, i, sizeof(char *), compare_id_flights);
    // escreve no ficheiro as linhas ordenadas pelo id do voo
    for (int j = 0; j < i; j++) {
        char *id = array[j];
        for (int k = 0; k < i; k++) {
            char *buffer2 = strdup(buffer);
            char *token = strtok(buffer2, ";");
            char *id2 = strdup(token);
            if (strcmp(id, id2) == 0) {
                fprintf(fp2, "%s\n", buffer);
                break;
            }
            free(buffer2);
        }
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time to parse flights.csv: %f\n", cpu_time_used);
    fclose(fp);
    fclose(fp2);
    return 0;
}

int compare_id_flights(const void *a, const void *b) {
    Passengers *passengers1 = (Passengers *) a;
    Passengers *passengers2 = (Passengers *) b;
    return strcmp(passengers1->flight_id, passengers2->flight_id);
}

// retorna o numero de passageiros de um voo
int get_number_passengers(char *flight_id){
    FILE *fp = fopen("entrada/passengers_valid.csv", "r");
    if(!fp) return 0;

    char buffer[1000000];
    char *buffer2 = NULL;  

    int i = 0;
    while (fgets(buffer, 1000000, fp) != NULL) {
        buffer2 = strdup(buffer);
        char *id = strsep(&buffer2, ";");
        if (strcmp(id, flight_id) == 0) {
            i++;
        }
        free(buffer2);
    }
    fclose(fp);
    return i;
}

int verify_passenger(char *user_id){
    FILE *fp = fopen("entrada/passengers_valid.csv", "r");
    if(!fp) return 0;

    char buffer[1000000];
    char *buffer2 = NULL;  

    int i = 0;
    while (fgets(buffer, 1000000, fp) != NULL) {
        buffer2 = strdup(buffer);
        char *id = strsep(&buffer2, ";");
        if (strcmp(id, user_id) == 0) {
            i++;
        }
        free(buffer2);
    }
    fclose(fp);
    if (i == 0) return 0;
    return 1;
}

