#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>

typedef struct catalog catalog;

#include "../../includes/model/users.h"
#include "../../includes/model/flights.h"
#include "../../includes/model/reservations.h"
#include "../../includes/model/passengers.h"
#include "../../includes/model/date.h"

char* pointer_file (char *path, char *file);
catalog *create_catalog(char *entry_files);
void delete_catalog(catalog *cat);
void update_hash_userRes(CAT_RESERVATIONS *r, CAT_USERS *u);
void update_hash_userPas(CAT_PASSENGERS *p, CAT_USERS *u);

Users *query1_users_aux(catalog *cat, char *id);
Reservations *query1_reservations_aux(catalog *cat, char *id);
Flights *query1_flights_aux(catalog *cat, char *id);
double query3_aux(catalog *cat, char *id);
GList *query4_aux(catalog *cat, char *hotel_id);
GList *query5_aux(catalog *cat, char *origin, Datetime beginD, Datetime endD);
GList *query6_aux(catalog *cat, char *year);
int query8_aux(catalog *cat, char *hotel_id, Date begin, Date end);
GList *query9_aux(catalog *cat, char *user_id);