#include "../../includes/model/output.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* função responsável pelo output de queries com apenas uma linha
 * cria o ficheiro necessário, com o nome apropriado, onde escreve o output da query */
int printToFile_OneLine(char *output, int output_number) {

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

/* função responsável pelo output de queries com mais de uma linha
 * cria o ficheiro necessário, com o nome apropriado, onde escreve o output da query */
int printToFile_MultipleLines(char **output, int N, int output_number) {

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

//função responsável pelo output de queries com apenas uma linha para o terminal
void printToTerminal_OneLine(char *output) {
    printf("%s", output);
    if (strlen(output) != 0) free(output);
}

//função responsável pelo output de queries com mais de uma linha para o terminal
char **printToTerminal_MultipleLines(char **output, int N, int pagina) {

    for (int i = (pagina - 1) * 50; i < N && i < pagina * 50; i++)
        printf("%s", output[i]);

    return output;
}

