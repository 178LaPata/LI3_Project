#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>

typedef struct catalog catalog;

#include "../includes/users.h"
#include "../includes/flights.h"
#include "../includes/reservations.h"
#include "../includes/passengers.h"
#include "../includes/date.h"

char* pointer_file (char *path, char *file);
catalog *create_catalog(char *entry_files);
void delete_catalog(catalog *cat);
void update_hash_userRes(CAT_RESERVATIONS *r, CAT_USERS *u);
void update_hash_userPas(CAT_PASSENGERS *p, CAT_USERS *u);

