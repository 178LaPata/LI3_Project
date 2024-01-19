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

    int total_passengers;
    int median_delay;
};

struct cache_flights {
    GHashTable *flights_cache;
    GQueue *flights_queue;
    int capacity;
};

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
    return flights->total_passengers;
}

int get_delay(Flights *flights){
    return flights->median_delay;
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
    flights->total_passengers = num_passengers;
}

void set_delay(Flights *flights, int delay){
    flights->median_delay = delay;
}

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

void delete_cache_flights(CACHE_FLIGHTS *cache_flights){
    g_hash_table_destroy(cache_flights->flights_cache);
    g_queue_free(cache_flights->flights_queue);
    free(cache_flights);
}

CACHE_FLIGHTS *create_new_cache_flights(int capacity){
    CACHE_FLIGHTS *cache_flights = malloc(sizeof(struct cache_flights));
    cache_flights->flights_cache = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, delete_flights);
    cache_flights->flights_queue = g_queue_new();
    cache_flights->capacity = capacity;
    return cache_flights;
}

void insert_cache_flights(CACHE_FLIGHTS *cache_flights, Flights *flights){
    if(g_hash_table_contains(cache_flights->flights_cache, flights->id_flights)){
        g_queue_remove(cache_flights->flights_queue, flights);
        g_queue_push_head(cache_flights->flights_queue, flights);
    }
    else{
        if(g_queue_get_length(cache_flights->flights_queue) == cache_flights->capacity){
            Flights *f = g_queue_pop_tail(cache_flights->flights_queue);
            g_hash_table_remove(cache_flights->flights_cache, f->id_flights);
        }
        g_hash_table_insert(cache_flights->flights_cache, flights->id_flights, flights);
        g_queue_push_head(cache_flights->flights_queue, flights);
    }
}

Flights *cache_flights_lookup(CACHE_FLIGHTS *cache_flights, char *id){
    Flights *flights = g_hash_table_lookup(cache_flights->flights_cache, id);
    if(flights != NULL){
        g_queue_remove(cache_flights->flights_queue, flights);
        g_queue_push_head(cache_flights->flights_queue, flights);
    }
    return flights;
}

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
                int num_passengers = get_number_passengers(flights->id_flights);
                if(num_passengers > flights->total_seats) val = 0;
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

    flights->total_passengers = 0;
    flights->median_delay = 0;
    free(copy_line);
    return flights;
}

int create_flights_valid_file(char *file){
    FILE *fp = fopen(file, "r");
    if(!fp) return 1;

    char buffer[1000000];
    char *buffer2 = NULL;  
    char *linha = "id;airline;plane_model;total_seats;origin;destination;schedule_departure_date;schedule_arrival_date;real_departure_date;real_arrival_date;pilot;copilot;notes";
    validate_csv_error(linha, "flights");

    clock_t start, end;
    double cpu_time_used;
    start = clock();

    FILE *fp2 = fopen("entrada/flights_valid.csv", "w");
    if (!fp2) return -1;
    
    while(fgets(buffer, 1000000, fp)){
        buffer2 = strdup(buffer); 
        Flights *f = create_flights(buffer2);
        if(f != NULL) {
            set_num_passengers(f, get_number_passengers(f->id_flights));
            set_delay(f, calculate_seconds(f->schedule_departure_date, f->real_departure_date));
            char *buffer3 = flights_toString(f);
            fprintf(fp2, "%s\n", buffer3);
        }
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time to parse flights.csv: %f\n", cpu_time_used);
    fclose(fp);
    fclose(fp2);
    return 0;
}

char *flights_to_string(Flights *fli){
    char *id_fli = get_id_flights(fli);
    char *airline = get_airline(fli);
    char *plane = get_plane(fli);
    int seats = get_seats(fli);
    char *origin = get_origin(fli);
    char *destination = get_destination(fli);
    char *sdd = datetime_to_string(get_schedule_departure_date(fli));
    char *sad = datetime_to_string(get_schedule_arrival_date(fli));
    char *rdd = datetime_to_string(get_real_departure_date(fli));
    char *rad = datetime_to_string(get_real_arrival_date(fli));
    char *pilot = get_pilot(fli);
    char *copilot = get_copilot(fli);
    char *notes = get_notes(fli);

    char *buffer = malloc(sizeof(char) * 1000);
    sprintf(buffer, "%s;%s;%s;%d;%s;%s;%s;%s;%s;%s;%s;%s;%s", id_fli, airline, plane, seats, origin, destination, sdd, sad, rdd, rad, pilot, copilot, notes);
    return buffer;

}

Flights *search_flight(CACHE_FLIGHTS *cache_flights, char *flight_id){
    Flights *flights = cache_flights_lookup(cache_flights, flight_id);
    if(flights != NULL) return flights;

    FILE *fp = fopen("entrada/flights_valid.csv", "r");
    if(!fp) return NULL;

    char buffer[1000000];
    char *buffer2 = NULL;  

    while (fgets(buffer, 1000000, fp) != NULL) {
        buffer2 = strdup(buffer);
        char *id = strsep(&buffer2, ";");
        if (strcmp(id, flight_id) == 0) {
            flights = create_flights(buffer);
            insert_cache_flights(cache_flights, flights);
            free(buffer2);
            return flights;
        }
        free(buffer2);
    }
    fclose(fp);
    return NULL;
}

int verify_flight(char *id){
    FILE *fp = fopen("entrada/flights_valid.csv", "r");
    if(!fp) return 1;

    char buffer[1000000];
    char *buffer2 = NULL;  
    char *id2 = NULL;
    int val = 0;

    while(fgets(buffer, 1000000, fp)){
        buffer2 = strdup(buffer); 
        id2 = strsep(&buffer2, ";");
        if(strcmp(id, id2) == 0) val = 1;
    }

    fclose(fp);
    return val;
}
