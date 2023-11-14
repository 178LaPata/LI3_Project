#pragma once

#include "../../includes/model/date.h"
#include "../../includes/model/valid.h"

#include <glib.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct reservations Reservations;
typedef struct cat_reservations CAT_RESERVATIONS;

char *get_id_reservations(Reservations *reservations);
char *get_user_id(Reservations *reservations);
char *get_hotel_id(Reservations *reservations);
char *get_hotel_name(Reservations *reservations);
int get_hotel_stars(Reservations *reservations);
int get_city_tax(Reservations *reservations);
char *get_adress_reservations(Reservations *reservations);
date get_begin_date(Reservations *reservations);
date get_end_date(Reservations *reservations);
int get_price_per_night(Reservations *reservations);
char *get_includes_breakfast(Reservations *reservations);
char *get_room_details(Reservations *reservations);
char *get_rating(Reservations *reservations);
char *get_comments(Reservations *reservations);
int get_nights(Reservations *reservations);
double get_total_price(Reservations *reservations);
void set_id_reservations(Reservations *reservations, char *id);
void set_user_id(Reservations *reservations, char *user_id);
void set_hotel_id(Reservations *reservations, char *hotel_id);
void set_hotel_name(Reservations *reservations, char *hotel_name);
void set_hotel_stars(Reservations *reservations, int hotel_stars);
void set_city_tax(Reservations *reservations, int city_tax);
void set_adress_reservations(Reservations *reservations, char *adress);
void set_begin_date(Reservations *reservations, date begin_date);
void set_end_date(Reservations *reservations, date end_date);
void set_price_per_night(Reservations *reservations, int price_per_night);
void set_includes_breakfast(Reservations *reservations, char *includes_breakfast);
void set_room_details(Reservations *reservations, char *room_details);
void set_rating(Reservations *reservations, char *rating);
void set_comments(Reservations *reservations, char *comments);
void set_nights(Reservations *reservations, int nights);
void set_total_price(Reservations *reservations, double total_price);

Reservations *create_reservations(char *line);
void delete_reservations(void *data);
void insert_reservations(CAT_RESERVATIONS *cat_reservations, Reservations *reservations);
CAT_RESERVATIONS *create_cat_reservations(char *entry_files);
void delete_cat_reservations(CAT_RESERVATIONS *cat_reservations);
void update_values_reservations(CAT_RESERVATIONS *cat_reservations);
int calculate_total_reservations(CAT_RESERVATIONS *cat_reservations, char *user);
double calculate_total_price(Reservations *reservations);
double calculate_total_spent(CAT_RESERVATIONS *cat_reservations, char *user);
Reservations *query1_reservations_aux(CAT_RESERVATIONS *reservations, char *id);
double query3_aux(CAT_RESERVATIONS *reservations, char *id);
double query8_aux(CAT_RESERVATIONS *reservations, char *hotel_id, date begin, date end);