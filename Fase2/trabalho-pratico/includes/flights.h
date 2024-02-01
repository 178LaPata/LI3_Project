#pragma once

#include <glib.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct flights Flights; 
typedef struct cache_flights CACHE_FLIGHTS;

#include "../includes/date.h"
#include "../includes/valid.h"
#include "../includes/passengers.h"
#include "../includes/reservations.h"
#include "../includes/catalog.h"

char *get_id_flights(Flights *flights);
char *get_airline(Flights *flights);
char *get_plane(Flights *flights);
int get_seats(Flights *flights);
char *get_origin(Flights *flights);
char *get_destination(Flights *flights);
Datetime get_schedule_departure_date(Flights *flights);
Datetime get_schedule_arrival_date(Flights *flights);
Datetime get_real_departure_date(Flights *flights);
Datetime get_real_arrival_date(Flights *flights);
char *get_pilot(Flights *flights);
char *get_copilot(Flights *flights);
char *get_notes(Flights *flights);
int get_num_passengers(Flights *flights);
int get_delay(Flights *flights);
void set_id_flights(Flights *flights, char *id_flights);
void set_airline(Flights *flights, char *airline);
void set_plane(Flights *flights, char *plane);
void set_seats(Flights *flights, int seats);
void set_origin(Flights *flights, char *origin);
void set_destination(Flights *flights, char *destination);
void set_schedule_departure_date(Flights *flights, Datetime schedule_departure_date);
void set_schedule_arrival_date(Flights *flights, Datetime schedule_arrival_date);
void set_real_departure_date(Flights *flights, Datetime real_departure_date);
void set_real_arrival_date(Flights *flights, Datetime real_arrival_date);
void set_pilot(Flights *flights, char *pilot);
void set_copilot(Flights *flights, char *copilot);
void set_notes(Flights *flights, char *notes);
void set_num_passengers(Flights *flights, int num_passengers);
void set_delay(Flights *flights, int delay);

void delete_flights(void *data);
void delete_cache_flights(CACHE_FLIGHTS *cache_flights);
CACHE_FLIGHTS *create_new_cache_flights(int capacity);
Flights *insert_cache_flights(CACHE_FLIGHTS *cache_flights, Flights *flights);
Flights *cache_flights_lookup(CACHE_FLIGHTS *cache_flights, char *id);
Flights *create_valid_flights(char *line);
Flights *copy_flights(Flights *flight);
Flights *create_flights(char *line);
int create_flights_valid_file(char *file);
int create_flights_aux_file();
char *flights_to_string(Flights *fli);
Flights *search_flight(CACHE_FLIGHTS *cache_flights, char *flight_id);
Flights *search_flight_queries(CACHE_FLIGHTS *cache_flights, char *flight_id);
char *display_flight(char *flight_id, CACHE_FLIGHTS *cache_flights);
GList* list_flights_origin(char *origin, Datetime beginD, Datetime endD);
gint data_mais_recenteF(gconstpointer a, gconstpointer b);
GList *sort_flights_data(char *origin, Datetime beginD, Datetime endD);
