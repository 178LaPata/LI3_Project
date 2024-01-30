#pragma once

#include <glib.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct passengers Passengers;
typedef struct cat_passengers CAT_PASSENGERS;
typedef struct list_passengers List_Passengers;

#include "../../includes/model/date.h"
#include "../../includes/model/valid.h"
#include "../../includes/model/users.h"
#include "../../includes/model/flights.h"

List_Passengers *create_passenger_list(Passengers* passengers);
void delete_passenger_list(void *data);
void insert_passenger_list(List_Passengers *list_passengers, Passengers *passengers);
Passengers *create_passengers(char *line, CAT_USERS *cat_users, CAT_FLIGHTS *cat_flights);
void delete_passengers(void *data);
void insert_passengers(CAT_PASSENGERS *cat_passengers, Passengers *passengers);
CAT_PASSENGERS *create_cat_passengers(char *entry_files, CAT_USERS *cat_users, CAT_FLIGHTS *cat_flights);
void delete_cat_passengers(CAT_PASSENGERS *cat_passengers);
GHashTable *get_passengers_hashtable(CAT_PASSENGERS *cat_passengers);
int get_num_passengers_list(CAT_PASSENGERS *cat_passengers, char *id);
char *get_user_from_list(CAT_PASSENGERS *cat_passengers, char *id, int i);
Passengers *get_passenger(CAT_PASSENGERS *cat_passengers, List_Passengers *list_passengers, char *flight_id, int i);