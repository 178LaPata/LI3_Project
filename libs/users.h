#ifndef USERS
#define USERS

#include "../libs/date.h"

typedef struct xd_user *XD_USER;

char* get_user_username (XD_USER user)
char* get_user_name (XD_USER user)
char get_user_gender (XD_USER user)

XD_DATE get_user_birth_date (XD_USER user);

XD_DATE get_user_account_creation (XD_USER user);

char* get_user_pay_method (XD_USER user);

char* get_user_account_status (XD_USER user);

int print_user_infos (XD_USER user);

int write_user_infos (FILE *file, XD_USER user);

int set_user_username (XD_USER user, char* line);

int set_user_name (XD_USER user, char* line);

int set_user_gender (XD_USER user, char* line);

int set_user_birth_date (XD_USER user, char* line);

int set_user_account_creation (XD_USER user, char* line);

int set_user_pay_method (XD_USER user, char* line);

int valid_user_account (char status);

int set_user_account_status (XD_USER user, char status);

XD_USER build_user (char* line);









