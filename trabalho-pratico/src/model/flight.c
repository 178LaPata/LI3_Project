#include "../../includes/model/flight.h"

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

struct cat_flights {
    GHashTable *flights_hashtable;
};

struct origin_passenger_count {
    char *origin;
    int total_passengers;
};

char *get_origin_opc(const ORIGIN_PASSENGER_COUNT *opc) {
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