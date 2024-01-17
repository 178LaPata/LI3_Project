#include "../includes/flights.h"

// estrutura dos flights
struct flights {
    char *id_flights;
    char *airline;
    char *plane_model;
    int total_seats;
    char *origin;
    char *destination;
    Datetime schedule_departure_date;  
    Datetime schedule_arrival_date;  
    Datetime real_departure_date;  
    Datetime real_arrival_date;  
    char *pilot;
    char *copilot;
    char *notes;
    
    int num_passengers;
    int delay;
};

// estrutura da hashtable dos flights
struct cat_flights {
    GHashTable *flights_hashtable;
};

struct origin_passenger_count {
    char *origin;
    int total_passengers;
};

char *get_origin_opc(ORIGIN_PASSENGER_COUNT *opc) {
    return opc->origin;
}

int get_total_passengers_opc(ORIGIN_PASSENGER_COUNT *opc) {
    return opc->total_passengers;
}

char *get_id_flights(Flights *flights){
    return flights->id_flights;
}

char *get_airline(Flights *flights){
    return flights->airline;
}

char *get_plane(Flights *flights){
    return flights->plane_model;
}

int get_seats(Flights *flights){
    return flights->total_seats;
}

char *get_origin(Flights *flights){
    return flights->origin;
}

char *get_destination(Flights *flights){
    return flights->destination;
}

Datetime get_schedule_departure_date(Flights *flights){
    return flights->schedule_departure_date;
}

Datetime get_schedule_arrival_date(Flights *flights){
    return flights->schedule_arrival_date;
}

Datetime get_real_departure_date(Flights *flights){
    return flights->real_departure_date;
}

Datetime get_real_arrival_date(Flights *flights){
    return flights->real_arrival_date;
}

char *get_pilot(Flights *flights){
    return flights->pilot;
}

char *get_copilot(Flights *flights){
    return flights->copilot;
}

char *get_notes(Flights *flights){
    return flights->notes;
}

int get_num_passengers(Flights *flights){
    return flights->num_passengers;
}

int get_delay(Flights *flights){
    return flights->delay;
}

void set_id_flights(Flights *flights, char *id_flights){
    flights->id_flights = strdup(id_flights);
}

void set_airline(Flights *flights, char *airline){
    flights->airline = strdup(airline);
}

void set_plane(Flights *flights, char *plane){
    flights->plane_model = strdup(plane);
}

void set_seats(Flights *flights, int seats){
    flights->total_seats = seats;
}

void set_origin(Flights *flights, char *origin){
    flights->origin = strdup(origin);
}

void set_destination(Flights *flights, char *destination){
    flights->destination = strdup(destination);
}

void set_schedule_departure_date(Flights *flights, Datetime schedule_departure_date){
    flights->schedule_departure_date = schedule_departure_date;
}

void set_schedule_arrival_date(Flights *flights, Datetime schedule_arrival_date){
    flights->schedule_arrival_date = schedule_arrival_date;
}

void set_real_departure_date(Flights *flights, Datetime real_departure_date){
    flights->real_departure_date = real_departure_date;
}

void set_real_arrival_date(Flights *flights, Datetime real_arrival_date){
    flights->real_arrival_date = real_arrival_date;
}

void set_pilot(Flights *flights, char *pilot){
    flights->pilot = strdup(pilot);
}

void set_copilot(Flights *flights, char *copilot){
    flights->copilot = strdup(copilot);
}

void set_notes(Flights *flights, char *notes){
    flights->notes = strdup(notes);
}

void set_num_passengers(Flights *flights, int num_passengers){
    flights->num_passengers = num_passengers;
}

void set_delay(Flights *flights, int delay){
    flights->delay = delay;
}

// cria um flights a partir de uma linha do ficheiro e verifica se os dados sao validos
Flights *create_flights(char *line){
    Flights *flights = malloc(sizeof(Flights));
    char *buffer;
    int i = 0;
    int val = 1;
    char *copy_line = strdup(line);

    Datetime sdd = NULL, sad = NULL, rdd = NULL, rad = NULL;

    flights->id_flights = NULL;
    flights->airline = NULL;
    flights->plane_model = NULL;
    flights->total_seats = 0;
    flights->origin = NULL;
    flights->destination = NULL;
    flights->schedule_departure_date = NULL;
    flights->schedule_arrival_date = NULL;
    flights->real_departure_date = NULL;
    flights->real_arrival_date = NULL;
    flights->pilot = NULL;
    flights->copilot = NULL;
    flights->notes = NULL;
    flights->num_passengers = 0;
    flights->delay = 0;
    
    while((buffer = strsep(&line, ";")) != NULL){
        switch(i++){
            case 0:
                if (strlen(buffer) == 0) val = 0;
                flights->id_flights = strdup(buffer);
                break;
            case 1:
                if (strlen(buffer) == 0) val = 0;
                flights->airline = strdup(buffer);
                break;
            case 2:
                if (strlen(buffer) == 0) val = 0;
                flights->plane_model = strdup(buffer);
                break; 
            case 3: 
                if(!verify_only_numbers(buffer)) val = 0;
                flights->total_seats = atoi(buffer);
                break;
            case 4:
                if (strlen(buffer) != 3) val = 0;
                for(int j = 0; buffer[j]; j++){
                    buffer[j] = toupper(buffer[j]);
                }
                flights->origin = strdup(buffer);
                break;
            case 5:
                if (strlen(buffer) != 3) val = 0;
                for(int j = 0; buffer[j]; j++){
                    buffer[j] = toupper(buffer[j]);
                }
                flights->destination = strdup(buffer);
                break;
            case 6:
                sdd = valid_date_time(buffer);
                flights->schedule_departure_date = sdd;
                if (flights->schedule_departure_date == NULL) val = 0;
                break;
            case 7:
                sad = valid_date_time(buffer);
                flights->schedule_arrival_date = sad;
                if (flights->schedule_arrival_date == NULL) val = 0;
                if(most_recent_datetime(flights->schedule_departure_date, flights->schedule_arrival_date) == 1) val = 0;
                break;
            case 8:
                rdd = valid_date_time(buffer);
                flights->real_departure_date = rdd;
                if (flights->real_departure_date == NULL) val = 0;
                break;
            case 9:
                rad = valid_date_time(buffer);
                flights->real_arrival_date = rad;
                if (flights->real_arrival_date == NULL) val = 0;
                if(most_recent_datetime(flights->real_departure_date, flights->real_arrival_date) == 1) val = 0;
                break;
            case 10:
                if (strlen(buffer) == 0) val = 0;
                flights->pilot = strdup(buffer);
                break;
            case 11:
                if (strlen(buffer) == 0) val = 0;
                flights->copilot = strdup(buffer);
                break;
            case 12:
                flights->notes = strdup(buffer);
                break;
        } 

        if (val == 0){
            validate_csv_error(copy_line, "flights");
            delete_flights(flights);
            free(copy_line);
            return NULL;
        }
    }

    flights->num_passengers = 0;
    flights->delay = 0;

    free(copy_line);
    return flights;
}

// da free a um flights e as variaveis
void delete_flights(void *data){
    Flights *flights = (Flights *) data;
    free(flights->id_flights);
    free(flights->airline);
    free(flights->plane_model);
    free(flights->origin);
    free(flights->destination);
    free(flights->pilot);
    free(flights->copilot);
    free(flights->notes);
    free_datetime(flights->schedule_departure_date);
    free_datetime(flights->schedule_arrival_date);
    free_datetime(flights->real_departure_date);
    free_datetime(flights->real_arrival_date);

    free(flights);
}

// insere um flights na hashtable
void insert_flights(CAT_FLIGHTS *cat_flights, Flights *flights){
    g_hash_table_insert(cat_flights->flights_hashtable, flights->id_flights, flights);
}

// cria a hashtable dos flights
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
    cat_flights->flights_hashtable = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, delete_flights);
    
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
        Flights *flights = create_flights(line);
        if(flights != NULL) insert_flights(cat_flights, flights);
    }
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Time to parse flights.csv: %f\n", cpu_time_used);

    free(line);
    fclose(fp);

    return cat_flights;
}

// da free a uma hashtable dos flights
void delete_cat_flights(CAT_FLIGHTS *cat_flights){
    g_hash_table_destroy(cat_flights->flights_hashtable);
    free(cat_flights);
}

void update_values_flights(CAT_FLIGHTS *cat_flights, CAT_PASSENGERS *cat_passengers){
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init (&iter, cat_flights->flights_hashtable);
    while (g_hash_table_iter_next (&iter, &key, &value)){
        Flights *flights = (Flights *) value;
        set_num_passengers(flights, get_num_passengers_list(cat_passengers, get_id_flights(flights)));
        set_delay(flights, calculate_seconds(flights->schedule_departure_date, flights->real_departure_date));
        if(get_num_passengers(flights) > get_seats(flights)){
            // nao tenho a certeza se e suposto fazer assim, fica assim pra ja
            //validate_csv_error(get_id_flights(flights), "flights");
        }
    }
}

char *display_flights(CAT_FLIGHTS *flights, char *id_flights){
    Flights *flight = g_hash_table_lookup(flights->flights_hashtable, id_flights);
    if(flight == NULL) return NULL;
    char *airline = get_airline(flight);
    char *plane = get_plane(flight);
    char *origin = get_origin(flight);
    char *destination = get_destination(flight);
    char *schedule_departure_date datetime_to_string(get_schedule_departure_date(flight));
    char *schedule_arrival_date = datetime_to_string(get_schedule_arrival_date(flight));
    int num_passengers = get_num_passengers(flight);
    int delay = get_delay(flight);

    char *display = malloc(snprintf(NULL, 0, "%s;%s;%s;%s;%s;%s;%d;%d", airline, plane, origin, destination, schedule_departure_date, schedule_arrival_date, num_passengers, delay) + 1);
    snprintf(display, 100,"%s;%s;%s;%s;%s;%s;%d;%d", airline, plane, origin, destination, schedule_departure_date, schedule_arrival_date, num_passengers, delay);
    return display;
}










// funcao que cria uma lista com os flights de uma determinada origem e entre duas datas
GList* list_flights_origin(CAT_FLIGHTS *cat_flights, char *origin, Datetime beginD, Datetime endD){
    GList *list = NULL;
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init (&iter, cat_flights->flights_hashtable);
    while (g_hash_table_iter_next (&iter, &key, &value)){
        Flights *flights = (Flights *) value;
        if (strcmp(get_origin(flights), origin) == 0){
            if(between_datetime(flights->schedule_departure_date, beginD, endD) == 1) {
                list = g_list_append(list, flights);
            }
        }
    }
    return list;
}

// funcao compara para ordenar os flights por data
gint data_mais_recenteF(gconstpointer a, gconstpointer b){
    Flights *flights1 = (Flights *) a;
    Flights *flights2 = (Flights *) b;
    
    if(equal_datetime(flights1->schedule_departure_date, flights2->schedule_departure_date)){
        if(flights1->id_flights < flights2->id_flights) return -1;
        else return 1;
    }
    return most_recent_datetime(flights2->schedule_departure_date, flights1->schedule_departure_date);
}

// funcao que ordena os flights por data
GList *sort_flights_data(CAT_FLIGHTS *cat_flights, char *origin, Datetime beginD, Datetime endD){
    GList *values = list_flights_origin(cat_flights, origin, beginD, endD);
    return g_list_sort(values, data_mais_recenteF);
}

// funcao que cria uma lista com os flights de um determinado ano
GList *list_flights_year(CAT_FLIGHTS *cat_flights, char *year){
    GList *list = NULL;
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init (&iter, cat_flights->flights_hashtable);
    while (g_hash_table_iter_next (&iter, &key, &value)){
        Flights *flights = (Flights *) value;
        if (strcmp(get_datetime_year(flights->schedule_departure_date), year) == 0){
            list = g_list_append(list, flights);
        }
    }
    return list;
}

// funcao que converte uma hashtable numa lista com os flights de uma determinada origem e o numero total de passageiros
GList *convert_hash_to_list(GList *list) {
    GHashTable *origin_passenger_counts = g_hash_table_new_full(g_str_hash, g_str_equal, free, NULL);

    while (list != NULL) {
        Flights *flight = (Flights *) list->data;
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

// funcao que compara duas origens por numero de passageiros
gint origin_with_more_passengers(gconstpointer a, gconstpointer b){
    ORIGIN_PASSENGER_COUNT *opc1 = (ORIGIN_PASSENGER_COUNT *) a;
    ORIGIN_PASSENGER_COUNT *opc2 = (ORIGIN_PASSENGER_COUNT *) b;
    
    if(opc1->total_passengers == opc2->total_passengers){
        if(strcmp(opc1->origin, opc2->origin) < 0) return -1;
        else return 1;
    }
    return opc2->total_passengers - opc1->total_passengers;
}

// funcao que ordena as origens por numero de passageiros
GList *sort_flights_num_passengers(CAT_FLIGHTS *cat_flights, char *year) {
    GList *values = list_flights_year(cat_flights, year);
    GList *final = convert_hash_to_list(values);
    GList *sorted_flights = g_list_sort(final, origin_with_more_passengers);
    return sorted_flights;
}