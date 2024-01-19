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
#include "../includes/valid.h"
#include "../includes/prints.h"

char* pointer_file (char *path, char *file);
void create_catalog(char *entry_files);
int run_batch(char* inputs_path, char* queries_path);
int run_interactive();