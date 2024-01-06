#pragma once

#include <glib.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <locale.h>

typedef struct cat_users CAT_USERS;

#include "../../includes/model/date.h"
#include "../../includes/model/valid.h"
#include "../../includes/model/passengers.h"
#include "../../includes/model/reservations.h"
#include "../../includes/model/flights.h"
#include "../../includes/model/user.h"

void insert_user(CAT_USERS *cat_users, const User *user);
CAT_USERS *create_cat_users(char *entry_files);
void delete_cat_users(CAT_USERS *cat_users);
User *get_users(CAT_USERS *cat_users, char *id);
void add_flights_total(User *user, int value);
void add_reservations_total(User *user, int value);
void add_spent_total(User *user, double value);
GList *list_users_prefixo(CAT_USERS *cat_users, char *prefix);
gint ordena_id(gconstpointer a, gconstpointer b);
GList *sort_users_id(CAT_USERS *cat_users, char *prefix);