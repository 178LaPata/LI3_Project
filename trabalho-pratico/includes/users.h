#pragma once

#include <glib.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <locale.h>

typedef struct users Users;
typedef struct cache_users CACHE_USERS;

#include "../includes/date.h"
#include "../includes/valid.h"
#include "../includes/passengers.h"
#include "../includes/reservations.h"
#include "../includes/flights.h"

char *get_id(Users *users);
char *get_name(Users *users);
char *get_email(Users *users);
char *get_phone_number(Users *users);
Date get_birth_date(Users *users);
char *get_sex(Users *users);
char *get_passport(Users *users);
char *get_country_code(Users *users);
char *get_adress(Users *users);
Datetime get_account_creation(Users *users);
enum pay_method get_pay_method(Users *users);
enum account_status get_account_status(Users *users);
int get_flights_total(Users *users);
int get_reservations_total(Users *users);
double get_spent_total(Users *users);
void set_id(Users *users, char *id);
void set_name(Users *users, char *name);
void set_email(Users *users, char *email);
void set_phone_number(Users *users, char *phone_number);
void set_birth_date(Users *users, Date birth_date);
void set_sex(Users *users, char *sex);
void set_passport(Users *users, char *passport);
void set_country_code(Users *users, char *country_code);
void set_adress(Users *users, char *adress);
void set_account_creation(Users *users, Datetime account_creation);
void set_pay_method(Users *users, enum pay_method pay_method);
void set_account_status(Users *users, enum account_status account_status);
void set_flights_total(Users *users, int flights_total);
void set_reservations_total(Users *users, int reservations_total);
void set_spent_total(Users *users, double spent_total);

void delete_users(void *data);
void delete_cache_users(CACHE_USERS *cache_users);
CACHE_USERS *create_new_cache_users(int capacity);
void insert_cache_users(CACHE_USERS *cache_users, Users *users);
Users *cache_users_lookup(CACHE_USERS *cache_users, char *id);
Users *create_users(char *line);
int create_users_valid_file(char *file);
int create_users_aux_file();
char *user_to_string(Users *user);
void add_flights_total(Users *users, int value);
void add_reservations_total(Users *users, int value);
void add_spent_total(Users *users, double value);
int compare_users(const void *a, const void *b);
int sort_users_by_name(char *file);
Users *search_user(CACHE_USERS *cache_users, char *id);
int verify_user(char *id);
