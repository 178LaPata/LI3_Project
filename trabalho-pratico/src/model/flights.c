#include "../../includes/model/flights.h"

// estrutura dos flights
struct flights {
    int id;
    char *airline;
    char *plane_model;
    int total_seats;
    char *origin;
    char *destination;
    datetime schedule_departure_date;  
    datetime schedule_arrival_date;  
    datetime real_departure_date;  
    datetime real_arrival_date;  
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

int get_id_flights(Flights *flights){
    return flights->id;
}

char *get_company(Flights *flights){
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

datetime get_schedule_departure_date(Flights *flights){
    return flights->schedule_departure_date;
}

datetime get_schedule_arrival_date(Flights *flights){
    return flights->schedule_arrival_date;
}

datetime get_real_departure_date(Flights *flights){
    return flights->real_departure_date;
}

datetime get_real_arrival_date(Flights *flights){
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

void set_id_flights(Flights *flights, int id){
    flights->id = id;
}

void set_company(Flights *flights, char *company){
    flights->airline = strdup(company);
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

void set_schedule_departure_date(Flights *flights, datetime schedule_departure_date){
    flights->schedule_departure_date = schedule_departure_date;
}

void set_schedule_arrival_date(Flights *flights, datetime schedule_arrival_date){
    flights->schedule_arrival_date = schedule_arrival_date;
}

void set_real_departure_date(Flights *flights, datetime real_departure_date){
    flights->real_departure_date = real_departure_date;
}

void set_real_arrival_date(Flights *flights, datetime real_arrival_date){
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
    while((buffer = strsep(&line, ";")) != NULL){
        switch(i++){
            case 0:
                if (strlen(buffer) == 0) val = 0;
                flights->id = (int) strtol(buffer, (char **) NULL, 10);
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
                flights->total_seats = atoi(buffer);
                break;
            case 4:
                flights->origin = strdup(buffer);
                break;
            case 5:
                flights->destination = strdup(buffer);
                break;
            case 6:
                flights->schedule_departure_date = valid_date_time(buffer);
                if (flights->schedule_departure_date == NULL) val = 0;
                break;
            case 7:
                flights->schedule_arrival_date = valid_date_time(buffer);
                if (flights->schedule_arrival_date == NULL) val = 0;
                break;
            case 8:
                flights->real_departure_date = valid_date_time(buffer);
                if (flights->real_departure_date == NULL) val = 0;
                break;
            case 9:
                flights->real_arrival_date = valid_date_time(buffer);
                if (flights->real_arrival_date == NULL) val = 0;
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
    }

    if(val == 0){
        delete_flights(flights);
        return NULL;
    }

    flights->num_passengers = 0;
    flights->delay = 0;

    return flights;
}

// da free a um flights e as variaveis
void delete_flights(void *data){
    Flights *flights = (Flights *) data;
    free(flights->airline);
    free(flights->plane_model);
    free(flights->origin);
    free(flights->destination);
    free(flights->pilot);
    free(flights->copilot);
    free(flights->notes);
    free(flights);
}

// insere um flights na hashtable
void insert_flights(CAT_FLIGHTS *cat_flights, Flights *flights){
    g_hash_table_insert(cat_flights->flights_hashtable, &flights->id, flights);
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
    cat_flights->flights_hashtable = g_hash_table_new_full(g_int_hash, g_int_equal, NULL, delete_flights);

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

    printf("Number of flights: %d\n", g_hash_table_size(cat_flights->flights_hashtable));

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
    }
}

Flights *query1_flights_aux (CAT_FLIGHTS *flights, int id){
    return g_hash_table_lookup(flights->flights_hashtable, &id);
}

