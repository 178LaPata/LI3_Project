#pragma once

#include "../../includes/model/date.h"
#include "../../includes/model/valid.h"
#include "../../includes/model/passengers.h"

#include <glib.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct flights Flights; 
typedef struct cat_flights CAT_FLIGHTS;

int get_id_flights(Flights *flights);
char *get_company(Flights *flights);
char *get_plane(Flights *flights);
int get_seats(Flights *flights);
char *get_origin(Flights *flights);
char *get_destination(Flights *flights);
datetime get_schedule_departure_date(Flights *flights);
datetime get_schedule_arrival_date(Flights *flights);
datetime get_real_departure_date(Flights *flights);
datetime get_real_arrival_date(Flights *flights);
char *get_pilot(Flights *flights);
char *get_copilot(Flights *flights);
char *get_notes(Flights *flights);
int get_num_passengers(Flights *flights);
int get_delay(Flights *flights);
void set_id_flights(Flights *flights, int id);
void set_company(Flights *flights, char *company);
void set_plane(Flights *flights, char *plane);
void set_seats(Flights *flights, int seats);
void set_origin(Flights *flights, char *origin);
void set_destination(Flights *flights, char *destination);
void set_schedule_departure_date(Flights *flights, datetime schedule_departure_date);
void set_schedule_arrival_date(Flights *flights, datetime schedule_arrival_date);
void set_real_departure_date(Flights *flights, datetime real_departure_date);
void set_real_arrival_date(Flights *flights, datetime real_arrival_date);
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
Flights *get_flights (CAT_FLIGHTS *flights, int id);
