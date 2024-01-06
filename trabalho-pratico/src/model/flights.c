#include "../../includes/model/flights.h"

struct cat_flights {
    GHashTable *flights_hashtable;
};

void insert_flight(CAT_FLIGHTS *cat_flights,  Flight *flight){
    g_hash_table_insert(cat_flights->flights_hashtable, flight->id_flight, flight);
}

CAT_FLIGHTS *create_cat_flights(char *entry_files){

    FILE *fp;
    char open[50];
    strcpy(open, entry_files);
    fp = fopen(open, "r");
    if (!fp) {
        perror("Error opening flights.csv");
        return NULL;
    }    

    CAT_FLIGHTS *cat_flights = malloc(sizeof(CAT_FLIGHTS));
    cat_flights->flights_hashtable = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, delete_flight);
    
    char *linha = "id;airline;plane_model;total_seats;origin;destination;schedule_departure_date;schedule_arrival_date;real_departure_date;real_arrival_date;pilot;copilot;notes";
    validate_csv_error(linha, "flights");

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
        Flight *flight = create_flight(line);
        if(flight != NULL) insert_flight(cat_flights, flight);
    }
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Time to parse flights.csv: %f\n", cpu_time_used);

    free(line);
    fclose(fp);

    return cat_flights;
}

void delete_cat_flights(CAT_FLIGHTS *cat_flights){
    g_hash_table_destroy(cat_flights->flights_hashtable);
    free(cat_flights);
}

void update_values_flights(CAT_FLIGHTS *cat_flights, CAT_PASSENGERS *cat_passengers){
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init (&iter, cat_flights->flights_hashtable);
    while (g_hash_table_iter_next (&iter, &key, &value)){
        Flight *flight = (Flight *) value;
        set_num_passengers(flight, get_num_passengers_list(cat_passengers, get_id_flight(flight)));
        set_delay(flight, calculate_seconds(flight->schedule_departure_date, flight->real_departure_date));
        if(get_num_passengers(flight) > get_seats(flight)){
            // nao tenho a certeza se e suposto fazer assim, fica assim pra ja
            //validate_csv_error(get_id_flights(flights), "flights");
        }
    }
}

Flight *get_flights (CAT_FLIGHTS *flights, char *id_flight){
    return g_hash_table_lookup(flight->flights_hashtable, id_flight);
}

GList* list_flights_origin(CAT_FLIGHTS *cat_flights, char *origin, Datetime beginD, Datetime endD){
    GList *list = NULL;
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init (&iter, cat_flights->flights_hashtable);
    while (g_hash_table_iter_next (&iter, &key, &value)){
        Flight *flight = (Flight *) value;
        if (strcmp(get_origin(flight), origin) == 0){
            if(between_datetime(flight->schedule_departure_date, beginD, endD) == 1) {
                list = g_list_append(list, flight);
            }
        }
    }
    return list;
}

gint data_mais_recenteF(gconstpointer a, gconstpointer b){
    Flight *flight1 = (Flight *) a;
    Flight *flight2 = (Flight *) b;
    
    if(equal_datetime(flight1->schedule_departure_date, flight2->schedule_departure_date)){
        if(flight1->id_flight < flight2->id_flight) return -1;
        else return 1;
    }
    return most_recent_datetime(flight2->schedule_departure_date, flight1->schedule_departure_date);
}

GList *sort_flights_data(CAT_FLIGHTS *cat_flights, char *origin, Datetime beginD, Datetime endD){
    GList *values = list_flights_origin(cat_flights, origin, beginD, endD);
    return g_list_sort(values, data_mais_recenteF);
}


// query 6
GList *list_flights_year(CAT_FLIGHTS *cat_flights, char *year){
    GList *list = NULL;
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init (&iter, cat_flights->flights_hashtable);
    while (g_hash_table_iter_next (&iter, &key, &value)){
        Flight *flight = (Flight *) value;
        if (strcmp(get_datetime_year(flight->schedule_departure_date), year) == 0){
            list = g_list_append(list, flight);
        }
    }
    return list;
}

GList *convert_hash_to_list(GList *list) {
    GHashTable *origin_passenger_counts = g_hash_table_new_full(g_str_hash, g_str_equal, free, NULL);

    while (list != NULL) {
        Flight *flight = (Flight *) list->data;
        ORIGIN_PASSENGER_COUNT *opc = g_hash_table_lookup(origin_passenger_counts, flight->origin);

        if (opc == NULL) {
            opc = malloc(sizeof(ORIGIN_PASSENGER_COUNT));
            opc->origin = strdup(flight->origin);
            opc->total_passengers = flight->num_passengers;
            g_hash_table_insert(origin_passenger_counts, opc->origin, opc);
        } else {
            opc->total_passengers += flight->num_passengers;
        }

        list = list->next;
    }

    GList *sorted_list = NULL;
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, origin_passenger_counts);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        ORIGIN_PASSENGER_COUNT *original_opc = (ORIGIN_PASSENGER_COUNT *) value;
        ORIGIN_PASSENGER_COUNT *new_opc = malloc(sizeof(ORIGIN_PASSENGER_COUNT));
        *new_opc = *original_opc; 
        new_opc->origin = strdup(original_opc->origin);
        new_opc->total_passengers = original_opc->total_passengers;
        sorted_list = g_list_prepend(sorted_list, new_opc);
    }
    
    g_hash_table_destroy(origin_passenger_counts);

    return sorted_list;
}

void free_origin_passenger_count(ORIGIN_PASSENGER_COUNT *opc) {
    free(opc->origin);
    free(opc);
}

gint origin_with_more_passengers(gconstpointer a, gconstpointer b){
    ORIGIN_PASSENGER_COUNT *opc1 = (ORIGIN_PASSENGER_COUNT *) a;
    ORIGIN_PASSENGER_COUNT *opc2 = (ORIGIN_PASSENGER_COUNT *) b;
    
    if(opc1->total_passengers == opc2->total_passengers){
        if(strcmp(opc1->origin, opc2->origin) < 0) return -1;
        else return 1;
    }
    return opc2->total_passengers - opc1->total_passengers;
}

GList *sort_flights_num_passengers(CAT_FLIGHTS *cat_flights, char *year) {
    GList *values = list_flights_year(cat_flights, year);
    GList *final = convert_hash_to_list(values);
    GList *sorted_flights = g_list_sort(final, origin_with_more_passengers);
    return sorted_flights;
}