#include "../includes/prints.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int write_to_file_one_line(char *output, int output_number) {

    char file_name[100];

    snprintf(file_name, 100, "Resultados/command%d_output.txt", output_number);

    FILE *fp;
    fp = fopen(file_name, "w+");
    if (!fp) {
        perror("Error");
        return -1;
    }

    fputs(output, fp);
    if (strlen(output) != 0) free(output);

    fclose(fp);

    return 0;
}

