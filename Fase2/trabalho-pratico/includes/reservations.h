#pragma once

#include <glib.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct reservations Reservations;
typedef struct cache_reservations CACHE_RESERVATIONS;

#include "../includes/date.h"
#include "../includes/valid.h"
#include "../includes/users.h"
#include "../includes/catalog.h"

char *get_id_reservations(Reservations *reservations);
char *get_user_id(Reservations *reservations);
char *get_hotel_id(Reservations *reservations);
char *get_hotel_name(Reservations *reservations);
int get_hotel_stars(Reservations *reservations);
int get_city_tax(Reservations *reservations);
char *get_adress_reservations(Reservations *reservations);
Date get_begin_date(Reservations *reservations);
Date get_end_date(Reservations *reservations);
int get_price_per_night(Reservations *reservations);
char *get_includes_breakfast(Reservations *reservations);
char *get_room_details(Reservations *reservations);
char *get_rating(Reservations *reservations);
char *get_comments(Reservations *reservations);
int get_nights(Reservations *reservations);
double get_total_price(Reservations *reservations);
void set_id_reservations(Reservations *reservations, char *id_res);
void set_user_id(Reservations *reservations, char *user_id);
void set_hotel_id(Reservations *reservations, char *hotel_id);
void set_hotel_name(Reservations *reservations, char *hotel_name);
void set_hotel_stars(Reservations *reservations, int hotel_stars);
void set_city_tax(Reservations *reservations, int city_tax);
void set_adress_reservations(Reservations *reservations, char *adress);
void set_begin_date(Reservations *reservations, Date begin_date);
void set_end_date(Reservations *reservations, Date end_date);
void set_price_per_night(Reservations *reservations, int price_per_night);
void set_includes_breakfast(Reservations *reservations, char *includes_breakfast);
void set_room_details(Reservations *reservations, char *room_details);
void set_rating(Reservations *reservations, char *rating);
void set_comments(Reservations *reservations, char *comments);
void set_nights(Reservations *reservations, int nights);
void set_total_price(Reservations *reservations, double total_price);

void delete_reservations(void *data);
void delete_cache_reservations(CACHE_RESERVATIONS *cache_reservations);
CACHE_RESERVATIONS *create_new_cache_reservations(int capacity);
Reservations *insert_cache_reservations(CACHE_RESERVATIONS *cache_reservations, Reservations *reservations);
Reservations *cache_reservations_lookup(CACHE_RESERVATIONS *cache_reservations, char *id);
Reservations *create_valid_reservations(char *line);
Reservations *copy_reservations(Reservations *reservations);
Reservations *create_reservations(char *line, CACHE_PASSENGERS *cache_passengers, CACHE_RESERVATIONS *cache_reservations, CACHE_USERS *cache_users);
int create_reservations_valid_file(char *file, CACHE_PASSENGERS *cache_passengers, CACHE_RESERVATIONS *cache_reservations, CACHE_USERS *cache_users);
double calculate_total_price(Reservations *reservations);
char *reservation_to_string(Reservations *r);
Reservations *search_reservation(CACHE_RESERVATIONS *cache_reservations, char *id_res);
char *verify_user_has_reservation(char *user_id);
char *calculate_average_rating(char *hotel_id);
int calculate_total_price_between_dates(Reservations *reservations, Date begin, Date end);
char *calculate_total_revenue(char *hotel_id, Date begin, Date end);
char *display_reservation(char *id_res, CACHE_RESERVATIONS *cache_reservations);
GList* list_reservations_hotelID(char* hotel_id);
gint data_mais_recente(gconstpointer a, gconstpointer b);
GList *sort_reservations_data(char *hotel_id);