#pragma once

#include <glib.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct passengers Passengers;
typedef struct cache_passengers CACHE_PASSENGERS;

#include "../includes/date.h"
#include "../includes/valid.h"
#include "../includes/users.h"
#include "../includes/flights.h"


void delete_passengers(void *data);
void delete_cache_passengers(CACHE_PASSENGERS *cache_passengers);
CACHE_PASSENGERS *create_new_cache_passengers(int capacity);
void insert_cache_passengers(CACHE_PASSENGERS *cache_passengers, Passengers *passengers);
Passengers *cache_passengers_lookup(CACHE_PASSENGERS *cache_passengers, char *id);
Passengers *create_passengers(char *line);
int create_passengers_valid_file(char *file);
int compare_id_flights(const void *a, const void *b);
int get_number_passengers(char *flight_id);
int verify_passenger(char *user_id);