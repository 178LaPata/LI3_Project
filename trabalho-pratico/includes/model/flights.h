#pragma once

#include <glib.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct cat_flights CAT_FLIGHTS;

#include "../../includes/model/flight.h"
#include "../../includes/model/date.h"
#include "../../includes/model/valid.h"
#include "../../includes/model/passengers.h"

void insert_flight(CAT_FLIGHTS *cat_flights, Flight *flight);
CAT_FLIGHTS *create_cat_flights(char *entry_files);
void delete_cat_flights(CAT_FLIGHTS *cat_flights);
void update_values_flights(CAT_FLIGHTS *cat_flights, CAT_PASSENGERS *cat_passengers);
Flight *get_flights (CAT_FLIGHTS *flights, char *id_flights);
GList* list_flights_origin(CAT_FLIGHTS *cat_flights, char *origin, Datetime beginD, Datetime endD);
gint data_mais_recenteF(gconstpointer a, gconstpointer b);
GList *sort_flights_data(CAT_FLIGHTS *cat_flights, char *origin, Datetime beginD, Datetime endD);
GList *list_flights_year(CAT_FLIGHTS *cat_flights, char *year);
GList *convert_hash_to_list(GList *list);
void free_origin_passenger_count(ORIGIN_PASSENGER_COUNT *opc);
gint origin_with_more_passengers(gconstpointer a, gconstpointer b);
GList *sort_flights_num_passengers(CAT_FLIGHTS *cat_flights, char *year);