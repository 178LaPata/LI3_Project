#pragma once

#define BUFFER 64

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

enum pay_method{
    debit_card,
    credit_card,
    cash,
    noPayMethod
};

enum account_status{
    NoStatus,
    Active,
    Inactive
};

enum pay_method verify_payMethod(char *token);
enum account_status verify_accountStatus (char* token);
char *verify_email(char *email);
char *verify_passport(char *passport);
char *verify_phone_number(char *phone_number);
int verify_stars(char *stars);
int verify_maior_que_zero(char *number);
int verify_maior_igual_que_zero(char *number);
char *verify_includes_breakfast(char *includes_breakfast);
char *verify_rating(char *rating);
int verify_only_numbers(char *str);
void validate_csv_error(char *line, char *file_name);
void writeToFile(char *line, char *file_name);