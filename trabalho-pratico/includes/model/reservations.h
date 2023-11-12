#pragma once

#include <glib.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../../includes/model/date.h"
#include "../../includes/model/valid.h"

typedef struct reservations Reservations;

typedef struct cat_reservations CAT_RESERVATIONS;

CAT_RESERVATIONS *create_cat_reservations(char *entry_files);
void delete_cat_reservations(CAT_RESERVATIONS *cat_reservations);
