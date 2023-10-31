#include "../../includes/model/users.h"
#include "../../includes/model/flights.h"
#include "../../includes/model/reservations.h"
#include "../../includes/model/passengers.h"
#include "../../includes/model/output.h"
#include "../../includes/model/date.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>

typedef struct catalog catalog;

catalog *create_catalog(char *entry_files);
void delete_catalog(catalog *cat);

// queries
