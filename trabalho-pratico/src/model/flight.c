#include "../../includes/model/flight.h"

struct flight {
    char *id_flight;
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

struct origin_passenger_count {
    char *origin;
    int total_passengers;
};

char *get_id_flight(const Flight *flight){
    return flight->id_flight;
}

char *get_airline(const Flight *flight){
    return flight->airline;
}

char *get_plane(const Flight *flight){
    return flight->plane_model;
}

int get_seats(const Flight *flight){
    return flight->total_seats;
}

char *get_origin(const Flight *flight){
    return flight->origin;
}

char *get_destination(const Flight *flight){
    return flight->destination;
}

Datetime get_schedule_departure_date(const Flight *flight){
    return flight->schedule_departure_date;
}

Datetime get_schedule_arrival_date(const Flight *flight){
    return flight->schedule_arrival_date;
}

Datetime get_real_departure_date(const Flight *flight){
    return flight->real_departure_date;
}

Datetime get_real_arrival_date(const Flight *flight){
    return flight->real_arrival_date;
}

char *get_pilot(const Flight *flight){
    return flight->pilot;
}

char *get_copilot(const Flight *flight){
    return flight->copilot;
}

char *get_notes(const Flight *flight){
    return flight->notes;
}

int get_num_passengers(const Flight *flight){
    return flight->num_passengers;
}

int get_delay(const Flight *flight){
    return flight->delay;
}

char *get_origin_opc(const ORIGIN_PASSENGER_COUNT *opc) {
    return opc->origin;
}

int get_total_passengers_opc(const ORIGIN_PASSENGER_COUNT *opc) {
    return opc->total_passengers;
}

void set_id_flight(Flight *flight, char *id_flight){
    flight->id_flight = strdup(id_flight);
}

void set_airline(Flight *flight, char *airline){
    flight->airline = strdup(airline);
}

void set_plane(Flight *flight, char *plane){
    flight->plane_model = strdup(plane);
}

void set_seats(Flight *flight, int seats){
    flight->total_seats = seats;
}

void set_origin(Flight *flight, char *origin){
    flight->origin = strdup(origin);
}

void set_destination(Flight *flight, char *destination){
    flight->destination = strdup(destination);
}

void set_schedule_departure_date(Flight *flight, Datetime schedule_departure_date){
    flight->schedule_departure_date = schedule_departure_date;
}

void set_schedule_arrival_date(Flight *flight, Datetime schedule_arrival_date){
    flight->schedule_arrival_date = schedule_arrival_date;
}

void set_real_departure_date(Flight *flight, Datetime real_departure_date){
    flight->real_departure_date = real_departure_date;
}

void set_real_arrival_date(Flight *flight, Datetime real_arrival_date){
    flight->real_arrival_date = real_arrival_date;
}

void set_pilot(Flight *flight, char *pilot){
    flight->pilot = strdup(pilot);
}

void set_copilot(Flight *flight, char *copilot){
    flight->copilot = strdup(copilot);
}

void set_notes(Flight *flight, char *notes){
    flight->notes = strdup(notes);
}

void set_num_passengers(Flight *flight, int num_passengers){
    flight->num_passengers = num_passengers;
}

void set_delay(Flight *flight, int delay){
    flight->delay = delay;
}

Flight *create_flight(char *line){
    Flight *flight = malloc(sizeof(flight));
    char *buffer;
    int i = 0;
    int val = 1;
    char *copy_line = strdup(line);

    Datetime sdd = NULL, sad = NULL, rdd = NULL, rad = NULL;
    flight->id_flight = NULL;
    flight->airline = NULL;
    flight->plane_model = NULL;
    flight->total_seats = 0;
    flight->origin = NULL;
    flight->destination = NULL;
    flight->schedule_departure_date = NULL;
    flight->schedule_arrival_date = NULL;
    flight->real_departure_date = NULL;
    flight->real_arrival_date = NULL;
    flight->pilot = NULL;
    flight->copilot = NULL;
    flight->notes = NULL;
    flight->num_passengers = 0;
    flight->delay = 0;
    
    while((buffer = strsep(&line, ";")) != NULL){
        switch(i++){
            case 0:
                if (strlen(buffer) == 0) val = 0;
                flight->id_flight = strdup(buffer);
                break;
            case 1:
                if (strlen(buffer) == 0) val = 0;
                flight->airline = strdup(buffer);
                break;
            case 2:
                if (strlen(buffer) == 0) val = 0;
                flight->plane_model = strdup(buffer);
                break; 
            case 3: 
                if(!verify_only_numbers(buffer)) val = 0;
                flight->total_seats = atoi(buffer);
                break;
            case 4:
                if (strlen(buffer) != 3) val = 0;
                for(int j = 0; buffer[j]; j++){
                    buffer[j] = toupper(buffer[j]);
                }
                flight->origin = strdup(buffer);
                break;
            case 5:
                if (strlen(buffer) != 3) val = 0;
                for(int j = 0; buffer[j]; j++){
                    buffer[j] = toupper(buffer[j]);
                }
                flight->destination = strdup(buffer);
                break;
            case 6:
                sdd = valid_date_time(buffer);
                flight->schedule_departure_date = sdd;
                if (flight->schedule_departure_date == NULL) val = 0;
                break;
            case 7:
                sad = valid_date_time(buffer);
                flight->schedule_arrival_date = sad;
                if (flight->schedule_arrival_date == NULL) val = 0;
                if(most_recent_datetime(flight->schedule_departure_date, flight->schedule_arrival_date) == 1) val = 0;
                break;
            case 8:
                rdd = valid_date_time(buffer);
                flight->real_departure_date = rdd;
                if (flight->real_departure_date == NULL) val = 0;
                break;
            case 9:
                rad = valid_date_time(buffer);
                flight->real_arrival_date = rad;
                if (flight->real_arrival_date == NULL) val = 0;
                if(most_recent_datetime(flight->real_departure_date, flight->real_arrival_date) == 1) val = 0;
                break;
            case 10:
                if (strlen(buffer) == 0) val = 0;
                flight->pilot = strdup(buffer);
                break;
            case 11:
                if (strlen(buffer) == 0) val = 0;
                flight->copilot = strdup(buffer);
                break;
            case 12:
                flight->notes = strdup(buffer);
                break;
        } 

        if (val == 0){
            validate_csv_error(copy_line, "flight");
            delete_flight(flight);
            free(copy_line);
            return NULL;
        }
    }

    flight->num_passengers = 0;
    flight->delay = 0;

    free(copy_line);
    return flight;
}

void delete_flight(void *data){
    Flight *flight = (Flight *) data;
    free(flight->id_flight);
    free(flight->airline);
    free(flight->plane_model);
    free(flight->origin);
    free(flight->destination);
    free(flight->pilot);
    free(flight->copilot);
    free(flight->notes);
    free_datetime(flight->schedule_departure_date);
    free_datetime(flight->schedule_arrival_date);
    free_datetime(flight->real_departure_date);
    free_datetime(flight->real_arrival_date);

    free(flight);
}