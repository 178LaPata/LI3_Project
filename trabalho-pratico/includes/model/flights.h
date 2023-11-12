#pragma once

#include "../../includes/model/date.h"
#include "../../includes/model/valid.h"

#include <glib.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct flights Flights; 

typedef struct cat_flights CAT_FLIGHTS;

CAT_FLIGHTS *create_cat_flights(char *entry_files);
void delete_cat_flights(CAT_FLIGHTS *cat_flights);