#pragma once

#include <glib.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct cat_reservations CAT_RESERVATIONS;

#include "../../includes/model/date.h"
#include "../../includes/model/valid.h"
#include "../../includes/model/users.h"
#include "../../includes/model/reservation.h"

void insert_reservation(CAT_RESERVATIONS *cat_reservations, Reservation *reservation);
CAT_RESERVATIONS *create_cat_reservations(char *entry_files, CAT_USERS *cat_users);
GHashTable *get_reservations_hashtable(CAT_RESERVATIONS *cat_reservations);
void delete_cat_reservations(CAT_RESERVATIONS *cat_reservations);
char *reservations_to_line(Reservation *reservation);
void update_values_reservations(CAT_RESERVATIONS *cat_reservations);
double calculate_total_price(Reservation *reservation);
Reservation *get_reservations(CAT_RESERVATIONS *cat_reservations, char *id);
double calculate_average_rating(CAT_RESERVATIONS *cat_reservations, char *hotel_id);
GList* list_reservations_hotelID(CAT_RESERVATIONS *cat_reservations, char* hotel_id);
gint data_mais_recente(gconstpointer a, gconstpointer b);
GList *sort_reservations_data(CAT_RESERVATIONS *cat_reservations, char *hotel_id);
int calculate_total_price_between_dates(Reservation *reservation, Date begin, Date end);
int calcular_receita_total(CAT_RESERVATIONS *cat_reservations, char *hotel_id, Date begin, Date end);
