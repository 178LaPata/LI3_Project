#include "../includes/passengers.h"

// estrutura dos passengers
struct passengers {
    char *flight_id;
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

List_Passengers *create_passenger_list(Passengers* passengers){
    List_Passengers *list_passengers = malloc(sizeof(List_Passengers));
    list_passengers->passengers_list = malloc(2 * sizeof(char *));
    list_passengers->size = 2;
    list_passengers->n = 0;
    insert_passenger_list(list_passengers, passengers);
    return list_passengers;
}

void delete_passenger_list(void *data){
    List_Passengers *list_passengers = (List_Passengers *) data;
    for (int i=0 ; i<list_passengers->n ; i++){
        free(list_passengers->passengers_list[i]);
    }
    free(list_passengers->passengers_list);
    free(list_passengers);
}

void insert_passenger_list(List_Passengers *list_passengers, Passengers *passengers){
    if (list_passengers->n == list_passengers->size){
        list_passengers->size *= 2;
        list_passengers->passengers_list = realloc(list_passengers->passengers_list, list_passengers->size * sizeof(char *));
    }
    list_passengers->passengers_list[list_passengers->n++] = strdup(passengers->user_id);
}

// cria um passengers a partir de uma linha do ficheiro e verifica se os dados sao validos
Passengers *create_passengers(char *line, CAT_USERS *cat_users, CAT_FLIGHTS *cat_flights){
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
                if(get_flights(cat_flights, passengers->flight_id) == NULL) val = 0;
                break;
            case 1:
                if (strlen(buffer) == 0) val = 0;
                passengers->user_id = strdup(buffer);
                if(get_users(cat_users, passengers->user_id) == NULL) val = 0;
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

// da free a um passengers e as variaveis
void delete_passengers(void *data){
    Passengers *passengers = (Passengers *) data;
    free(passengers->flight_id);
    free(passengers->user_id);
    free(passengers);
}

// insere um passengers na hashtable
void insert_passengers(CAT_PASSENGERS *cat_passengers, Passengers *passengers){
    if (!g_hash_table_contains(cat_passengers->passengers_hashtable, passengers->flight_id))
        g_hash_table_insert(cat_passengers->passengers_hashtable, strdup(passengers->flight_id), create_passenger_list(passengers));
    else
        insert_passenger_list(g_hash_table_lookup(cat_passengers->passengers_hashtable, passengers->flight_id), passengers);
}

// cria a hashtable dos passengers
CAT_PASSENGERS *create_cat_passengers(char *entry_files, CAT_USERS *cat_users, CAT_FLIGHTS *cat_flights){

    FILE *fp;
    char open[50];
    strcpy(open, entry_files);
    fp = fopen(open, "r");
    if (!fp) {
        perror("Error opening passengers.csv");
        return NULL;
    }

    CAT_PASSENGERS *cat_passengers = malloc(sizeof(CAT_PASSENGERS));
    cat_passengers->passengers_hashtable = g_hash_table_new_full(g_str_hash, g_str_equal, free, delete_passenger_list);
    
    char *linha = "flight_id;user_id";
    validate_csv_error(linha, "passengers");

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
        Passengers *passengers = create_passengers(line, cat_users, cat_flights);
        if(passengers != NULL){
            insert_passengers(cat_passengers, passengers);
            delete_passengers(passengers);
        }
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time to parse passengers.csv: %f\n", cpu_time_used);

    free(line);
    fclose(fp);
    
    return cat_passengers;
}

// da free a hashtable dos passengers
void delete_cat_passengers(CAT_PASSENGERS *cat_passengers){
    g_hash_table_destroy(cat_passengers->passengers_hashtable);
    free(cat_passengers);
}

GHashTable *get_passengers_hashtable(CAT_PASSENGERS *cat_passengers){
    return cat_passengers->passengers_hashtable;
}

// retorna o numero de passageiros de um voo
int get_num_passengers_list(CAT_PASSENGERS *cat_passengers, char *id){
    List_Passengers *list_passengers = g_hash_table_lookup(cat_passengers->passengers_hashtable, id);
    if(list_passengers == NULL) return 0;
    return list_passengers->n;
}

// retorna um passageiro de um voo
char *get_user_from_list(CAT_PASSENGERS *cat_passengers, char *id, int i){
    List_Passengers *list_passengers = g_hash_table_lookup(cat_passengers->passengers_hashtable, id);
    return list_passengers->passengers_list[i]; 
}

// retorna um passageiro
Passengers *get_passenger(CAT_PASSENGERS *cat_passengers, List_Passengers *list_passengers, char *flight_id, int i){
    char *user_id = list_passengers->passengers_list[i];
    Passengers *passengers = malloc(sizeof(Passengers));
    passengers->flight_id = strdup(flight_id);
    passengers->user_id = strdup(user_id);
    return passengers;
}

