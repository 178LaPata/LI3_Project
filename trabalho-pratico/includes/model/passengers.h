#pragma once

#include <glib.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct passengers Passengers;
typedef struct cat_passengers CAT_PASSENGERS;
typedef struct list_passengers List_Passengers;

List_Passengers *create_passenger_list(Passengers* passengers);
void delete_passenger_list(void *data);
void insert_passenger_list(List_Passengers *list_passengers, Passengers *passengers);
Passengers *create_passengers(char *line);
void delete_passengers(void *data);
void insert_passengers(CAT_PASSENGERS *cat_passengers, Passengers *passengers);
CAT_PASSENGERS *create_cat_passengers(char *entry_files);
void delete_cat_passengers(CAT_PASSENGERS *cat_passengers);
int calculate_total_flights_list(List_Passengers *list_passengers, char *id);
int calculate_total_flights(CAT_PASSENGERS *cat_passengers, char *id);
int get_num_passengers_list(CAT_PASSENGERS *cat_passengers, int id);
