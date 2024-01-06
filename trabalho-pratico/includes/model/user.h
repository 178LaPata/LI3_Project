#pragma once

#include <glib.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <locale.h>

typedef struct user User;

#include "../../includes/model/date.h"
#include "../../includes/model/valid.h"

char *get_id(const User *user);
char *get_name(const User *user);
char *get_email(const User *user);
char *get_phone_number(const User *user);
Date get_birth_date(const User *user);
char *get_sex(const User *user);
char *get_passport(const User *user);
char *get_country_code(const User *user);
char *get_adress(const User *user);
Datetime get_account_creation(const User *user);
enum pay_method get_pay_method(const User *user);
enum account_status get_account_status(const User *user);
int get_flights_total(const User *user);
int get_reservations_total(const User *user);
double get_spent_total(const User *user);

void set_id(User *user, char *id);
void set_name(User *user, char *name);
void set_email(User *user, char *email);
void set_phone_number(User *user, char *phone_number);
void set_birth_date(User *user, Date birth_date);
void set_sex(User *user, char *sex);
void set_passport(User *user, char *passport);
void set_country_code(User *user, char *country_code);
void set_adress(User *user, char *adress);
void set_account_creation(User *user, Datetime account_creation);
void set_pay_method(User *user, enum pay_method pay_method);
void set_account_status(User *user, enum account_status account_status);
void set_flights_total(User *user, int flights_total);
void set_reservations_total(User *user, int reservations_total);
void set_spent_total(User *user, double spent_total);

User *create_user(char *line);
void delete_user(void *data);