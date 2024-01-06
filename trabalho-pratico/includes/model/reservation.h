#pragma once

#include <glib.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct reservation Reservation;

#include "../../includes/model/date.h"
#include "../../includes/model/valid.h"
#include "../../includes/model/users.h"

char *get_id_reservation(const Reservation *reservation);
char *get_user_id(const Reservation *reservation);
char *get_hotel_id(const Reservation *reservation);
char *get_hotel_name(const Reservation *reservation);
int get_hotel_stars(const Reservation *reservation);
int get_city_tax(const Reservation *reservation);
char *get_adress_reservation(const Reservation *reservation);
Date get_begin_date(const Reservation *reservation);
Date get_end_date(const Reservation *reservation);
int get_price_per_night(const Reservation *reservation);
char *get_includes_breakfast(const Reservation *reservation);
char *get_room_details(const Reservation *reservation);
char *get_rating(const Reservation *reservation);
char *get_comments(const Reservation *reservation);
int get_nights(const Reservation *reservation);
double get_total_price(const Reservation *reservation);
void set_id_reservation(Reservation *reservation, char *id_res);
void set_user_id(Reservation *reservation, char *user_id);
void set_hotel_id(Reservation *reservation, char *hotel_id);
void set_hotel_name(Reservation *reservation, char *hotel_name);
void set_hotel_stars(Reservation *reservation, int hotel_stars);
void set_city_tax(Reservation *reservation, int city_tax);
void set_adress_reservation(Reservation *reservation, char *adress);
void set_begin_date(Reservation *reservation, Date begin_date);
void set_end_date(Reservation *reservation, Date end_date);
void set_price_per_night(Reservation *reservation, int price_per_night);
void set_includes_breakfast(Reservation *reservation, char *includes_breakfast);
void set_room_details(Reservation *reservation, char *room_details);
void set_rating(Reservation *reservation, char *rating);
void set_comments(Reservation *reservation, char *comments);
void set_nights(Reservation *reservation, int nights);
void set_total_price(Reservation *reservation, double total_price);

Reservation *create_reservation(char *line, CAT_USERS *cat_users);
void delete_reservation(void *data);