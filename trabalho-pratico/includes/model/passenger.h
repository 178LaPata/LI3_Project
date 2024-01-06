#pragma once

#include <glib.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct passenger Passenger;

#include "../../includes/model/date.h"
#include "../../includes/model/valid.h"
#include "../../includes/model/users.h"
#include "../../includes/model/flights.h"

Passenger *create_passenger(char *line, CAT_USERS *cat_users, CAT_FLIGHTS *cat_flights);
void delete_passenger(void *data);