#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>

typedef struct catalog Catalog;

#include "../includes/users.h"
#include "../includes/flights.h"
#include "../includes/reservations.h"
#include "../includes/passengers.h"
#include "../includes/date.h"
#include "../includes/valid.h"
#include "../includes/prints.h"

char* pointer_file (char *path, char *file);
Catalog *create_catalog(char *entry_files);
void delete_catalog(Catalog *cat);

char *query1(char *input, Catalog *cat);
char *query3(char *input);
char *query8(char *input);
char **query9(char *input);

int run_batch(char* inputs_path, char* queries_path);
int run_tests(char* inputs_path, char* queries_path, char* results_path);
int compare_files(char* path, int n);
int run_interactive();