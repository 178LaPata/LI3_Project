#pragma once

#include "../../includes/model/users.h"
#include "../../includes/model/flights.h"
#include "../../includes/model/reservations.h"
#include "../../includes/model/passengers.h"
#include "../../includes/model/date.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>

typedef struct catalog catalog;

char* pointer_file (char *path, char *file);
catalog *create_catalog(char *entry_files);
void delete_catalog(catalog *cat);
Users *query1_users_aux(catalog *cat, char *id);
Reservations *query1_reservations_aux(catalog *cat, char *id);
Flights *query1_flights_aux(catalog *cat, char *id);