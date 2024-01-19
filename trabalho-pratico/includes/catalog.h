#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>


#include "../includes/users.h"
#include "../includes/flights.h"
#include "../includes/reservations.h"
#include "../includes/passengers.h"
#include "../includes/date.h"

char* pointer_file (char *path, char *file);
void create_catalog(char *entry_files);
