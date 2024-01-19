#include "../includes/prints.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int write_to_file_one_line(char *output, int output_number) {
    char *file_name = malloc(100 * sizeof(char));
    sprintf(file_name, "Resultados/command%d_output.txt", output_number);
    FILE *fp = fopen(file_name, "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(fp, "%s\n", output);
    fclose(fp);
    return 0;
}

int write_to_file_mul_line(char **output, int output_number) {
    char *file_name = malloc(100 * sizeof(char));
    sprintf(file_name, "Resultados/command%d_output.txt", output_number);
    FILE *fp = fopen(file_name, "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    int i = 0;
    while (output[i] != NULL) {
        fprintf(fp, "%s\n", output[i]);
        i++;
    }
    fclose(fp);
    return 0;
}



