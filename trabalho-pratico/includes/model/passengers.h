#pragma once

#include <glib.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct cat_passengers CAT_PASSENGERS;
typedef struct list_passengers List_Passengers;

#include "../../includes/model/date.h"
#include "../../includes/model/valid.h"
#include "../../includes/model/users.h"
#include "../../includes/model/flights.h"
#include "../../includes/model/passenger.h"

List_Passengers *create_passenger_list(Passenger* passenger);
void delete_passenger_list(void *data);
void insert_passenger_list(List_Passengers *list_passengers, Passenger *passenger);
void insert_passenger(CAT_PASSENGERS *cat_passengers, Passenger *passenger);
CAT_PASSENGERS *create_cat_passengers(char *entry_files, CAT_USERS *cat_users, CAT_FLIGHTS *cat_flights);
void delete_cat_passengers(CAT_PASSENGERS *cat_passengers);
GHashTable *get_passengers_hashtable(CAT_PASSENGERS *cat_passengers);
int get_num_passengers_list(CAT_PASSENGERS *cat_passengers, char *id);
char *get_user_from_list(CAT_PASSENGERS *cat_passengers, char *id, int i);
Passenger *get_passenger(CAT_PASSENGERS *cat_passengers, List_Passengers *list_passengers, char *flight_id, int i);