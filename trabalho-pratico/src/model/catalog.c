#include "../../includes/model/catalog.h"
#include "../../includes/model/users.h"
#include "../../includes/model/flights.h"
#include "../../includes/model/reservations.h"
#include "../../includes/model/passengers.h"


#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <ctype.h>

typedef struct catalog {
    CAT_USERS *cat_users;
    CAT_FLIGHTS *cat_flights;
    CAT_RESERVATIONS *cat_reservations;
} Catalog;

Catalog *create_Catalog(char *entry_files) {
    Catalog *c = malloc(sizeof(struct catalog));
    c->cat_users = create_cat_users(entry_files);
    c->cat_flights = create_cat_flights(entry_files);
    c->cat_reservations = create_cat_reservations(entry_files);
    return c;
}

void delete_Catalog(Catalog *c) {
    delete_cat_users(c->cat_users);
    delete_cat_flights(c->cat_flights);
    delete_cat_reservations(c->cat_reservations);
    free(c);
}


// queries

