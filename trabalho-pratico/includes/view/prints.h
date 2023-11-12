#pragma once

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int print_file_one_line(char *output, int output_number);
int print_file_multiple_lines(char **output, int N, int output_number);
int print_file_error_one_line(char *output, int output_number);
int print_file_error_multiple_lines(char *output, int output_number);

