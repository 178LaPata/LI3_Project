#include "../../includes/view/output.h"

int print_file_one_line(char *output, int output_number) {

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

int print_file_multiple_lines(char **output, int N, int output_number) {

    char file_name[100];

    snprintf(file_name, 100, "Resultados/command%d_output.txt", output_number);

    FILE *fp;
    fp = fopen(file_name, "w+");
    if (!fp) {
        perror("Error");
        return -1;
    }

    if (output == NULL) return 0;

    for (int i = 0; i < N; i++) {
        fputs(output[i], fp);
        free(output[i]);
    }
    free(output);
    fclose(fp);

    return 0;
}

int print_file_error_one_line(char *output, int output_number) {

}

int print_file_error_multiple_lines(char *output, int output_number) {

}