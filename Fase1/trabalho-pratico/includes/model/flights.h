#pragma once

#include <glib.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct flights Flights; 
typedef struct cat_flights CAT_FLIGHTS;
typedef struct origin_passenger_count ORIGIN_PASSENGER_COUNT;  

#include "../../includes/model/date.h"
#include "../../includes/model/valid.h"
#include "../../includes/model/passengers.h"

char *get_origin_opc(ORIGIN_PASSENGER_COUNT *opc);
int get_total_passengers_opc(ORIGIN_PASSENGER_COUNT *opc);
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

Flights *create_flights(char *line);
void delete_flights(void *data);
void insert_flights(CAT_FLIGHTS *cat_flights, Flights *flights);
CAT_FLIGHTS *create_cat_flights(char *entry_files);
void delete_cat_flights(CAT_FLIGHTS *cat_flights);
void update_values_flights(CAT_FLIGHTS *cat_flights, CAT_PASSENGERS *cat_passengers);
Flights *get_flights (CAT_FLIGHTS *flights, char *id_flights);
GList* list_flights_origin(CAT_FLIGHTS *cat_flights, char *origin, Datetime beginD, Datetime endD);
gint data_mais_recenteF(gconstpointer a, gconstpointer b);
GList *sort_flights_data(CAT_FLIGHTS *cat_flights, char *origin, Datetime beginD, Datetime endD);
GList *list_flights_year(CAT_FLIGHTS *cat_flights, char *year);
GList *convert_hash_to_list(GList *list);
void free_origin_passenger_count(ORIGIN_PASSENGER_COUNT *opc);
gint origin_with_more_passengers(gconstpointer a, gconstpointer b);
GList *sort_flights_num_passengers(CAT_FLIGHTS *cat_flights, char *year);