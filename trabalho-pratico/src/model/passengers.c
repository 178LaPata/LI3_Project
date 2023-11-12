#include "../../includes/model/passengers.h"

// estrutura dos passengers
struct passengers {
    int flight_id;
    char *user_id;
};

// estrutura da hashtable dos passengers
struct cat_passengers {
    GHashTable *passengers_hashtable;
};

struct list_passengers {
    char **passengers_list;
    int size, n;
};

// da free a um passengers e as variaveis
void delete_passengers(void *data){
    Passengers *passengers = (Passengers *) data;
    free(passengers->user_id);
    free(passengers);
}

List_Passengers *create_passenger_list(Passengers* passengers){
    List_Passengers *list_passengers = malloc(sizeof(List_Passengers));
    list_passengers->passengers_list = malloc(2 * sizeof(char *));
    list_passengers->size = 2;
    list_passengers->n = 0;
    insert_passenger_list(list_passengers, passengers);
    return list_passengers;
}

void insert_passenger_list(List_Passengers *list_passengers, Passengers *passengers){
    if (list_passengers->n == list_passengers->size){
        list_passengers->size *= 2;
        list_passengers->passengers_list = realloc(list_passengers->passengers_list, list_passengers->size * sizeof(char *));
    }
    list_passengers->passengers_list[list_passengers->n++] = passengers->user_id;
}

void delete_passenger_list(void *data){
    List_Passengers *list_passengers = (List_Passengers *) data;
    for (int i=0 ; i<list_passengers->n ; i++)
        free(list_passengers->passengers_list[i]);
    free(list_passengers);
}

// cria um passengers a partir de uma linha do ficheiro e verifica se os dados sao validos
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

// insere um passengers na hashtable
void insert_passengers(CAT_PASSENGERS *cat_passengers, Passengers *passengers){
    if (!g_hash_table_contains(cat_passengers->passengers_hashtable, &passengers->flight_id))
        g_hash_table_insert(cat_passengers->passengers_hashtable, &passengers->flight_id, create_passenger_list(passengers));
    else
        insert_passenger_list(g_hash_table_lookup(cat_passengers->passengers_hashtable, &passengers->flight_id), passengers);
}

// cria a hashtable dos passengers
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
    cat_passengers->passengers_hashtable = g_hash_table_new_full(g_int_hash, g_int_equal, NULL, delete_passenger_list);

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

// da free a hashtable dos passengers
void delete_cat_passengers(CAT_PASSENGERS *cat_passengers){
    g_hash_table_destroy(cat_passengers->passengers_hashtable);
    free(cat_passengers);
}

int calculate_total_flights_list(List_Passengers *list_passengers, char *id){
    for (int i=0 ; i<list_passengers->n ; i++)
        if (strcmp(list_passengers->passengers_list[i], id) == 0) return 1;
    return 0;
}

// calcula o numero de voos de um user
int calculate_total_flights(CAT_PASSENGERS *cat_passengers, char *id){
    int total_flights = 0;
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, cat_passengers->passengers_hashtable);
    while (g_hash_table_iter_next(&iter, &key, &value)){
        List_Passengers *list_passengers = (List_Passengers *) value;
        total_flights += calculate_total_flights_list(list_passengers, id);
    }
    return total_flights;
}
