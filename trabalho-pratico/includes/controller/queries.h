#pragma once
#include "../../includes/view/prints.h"
#include "../../includes/model/catalog.h"

void query1_users(catalog *cat, char *id);
void query1_flights(catalog *cat, int id);
void query1_reservations(catalog *cat, char *id);
void query3(catalog *cat, char *hotel_id);
void query8(catalog *cat, char *hotel_id, date begin, date end);

void parse_queries(char *line, catalog *cat, int output_num);
int run_batch(char **input_file);