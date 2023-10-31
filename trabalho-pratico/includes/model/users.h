#include "../../includes/model/date.h"
#include "../../includes/model/valid.h"
#include "../../includes/model/passengers.h"

typedef struct users Users;

typedef struct cat_users CAT_USERS;

CAT_USERS *create_cat_users(char *entry_files);
void delete_cat_users(CAT_USERS *cat_users);

void update_values_users(CAT_USERS *cat_users, CAT_PASSENGERS *cat_passengers);

char *get_id(Users *users);
char *get_name(Users *users);
char *get_email(Users *users);
char *get_phone_number(Users *users);
date get_birth_date(Users *users);
char *get_sex(Users *users);
char *get_passport(Users *users);
char *get_country_code(Users *users);
char *get_adress(Users *users);
datetime get_account_creation(Users *users);
enum pay_method get_pay_method(Users *users);
enum account_status get_account_status(Users *users);
int get_flights_total(Users *users);
void set_id(Users *users, char *id);
void set_name(Users *users, char *name);
void set_email(Users *users, char *email);
void set_phone_number(Users *users, char *phone_number);
void set_birth_date(Users *users, date birth_date);
void set_sex(Users *users, char *sex);
void set_passport(Users *users, char *passport);
void set_country_code(Users *users, char *country_code);
void set_adress(Users *users, char *adress);
void set_account_creation(Users *users, datetime account_creation);
void set_pay_method(Users *users, enum pay_method pay_method);
void set_account_status(Users *users, enum account_status account_status);
void set_flights_total(Users *users, int flights_total);

Users *query1_aux(CAT_USERS *users, char *id);