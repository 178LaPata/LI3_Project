#pragma once
#include "../../includes/view/prints.h"
#include "../../includes/model/catalog.h"

void query1(catalog *cat, char *id);
void parse_queries(char *line, catalog *cat, int output_num);
int run_batch(char **input_file);