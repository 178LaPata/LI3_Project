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

int write_to_terminal(char *output){
    printf("%s\n", output);
    free(output);
    return 0;
}

int write_to_terminal_mul_line(char **output){
    int i = 0;
    while (output[i] != NULL) {
        printf("%s\n", output[i]);
        i++;
    }
    return 0;
}

void print_entry_menu(){
    printf(" ------------------------------------------------------------------------------------------------------------ \n");
    printf("| OPÇÃO |                                           QUERY                                                    |\n");
    printf("|------------------------------------------------------------------------------------------------------------|\n");
    printf("|   1   |  Listar o resumo de um utilizador, voo, ou reserva, consoante o identificador recebido             |\n");
    printf("|       |  por argumento.                                                                                    |\n");
    printf("|------------------------------------------------------------------------------------------------------------|\n");
    printf("|   2   |  Listar os voos ou reservas de um utilizador, se o segundo argumento for flights ou                |\n");
    printf("|       |  reservations, respetivamente, ordenados por data (da mais recente para a mais antiga).            |\n");
    printf("|------------------------------------------------------------------------------------------------------------|\n");
    printf("|   3   |  Apresentar a classificação média de um hotel, a partir do seu identificador.                      |\n");
    printf("|       |                                                                                                    |\n");
    printf("|------------------------------------------------------------------------------------------------------------|\n");
    printf("|   4   |  Listar as reservas de um hotel, ordenadas por data de início (da mais recente para                |\n");
    printf("|       |  a mais antiga).                                                                                   |\n");
    printf("|------------------------------------------------------------------------------------------------------------|\n");
    printf("|   5   |  Listar os voos com origem num dado aeroporto, entre duas datas, ordenados por                     |\n");
    printf("|       |  data de partida estimada (da mais recente para a mais antiga).                                    |\n");
    printf("|------------------------------------------------------------------------------------------------------------|\n");
    printf("|   6   |  Listar o top N aeroportos com mais passageiros, para um dado ano.                                 |\n");
    printf("|       |                                                                                                    |\n");
    printf("|------------------------------------------------------------------------------------------------------------|\n");
    printf("|   7   |  Listar o top N aeroportos com a maior mediana de atrasos.                                         |\n");
    printf("|       |                                                                                                    |\n");
    printf("|------------------------------------------------------------------------------------------------------------|\n");
    printf("|   8   |  Apresentar a receita total de um hotel entre duas datas (inclusive), a partir                     |\n");
    printf("|       |  do seu identificador.                                                                             |\n");
    printf("|------------------------------------------------------------------------------------------------------------|\n");
    printf("|   9   |  Listar todos os utilizadores cujo nome começa com o prefixo passado por argumento,                |\n");
    printf("|       |  ordenados por nome (de forma crescente).                                                          |\n");
    printf("|------------------------------------------------------------------------------------------------------------|\n");
    printf("|   10  |  Apresentar várias métricas gerais da aplicação.                                                   |\n");
    printf("|       |                                                                                                    |\n");
    printf("|------------------------------------------------------------------------------------------------------------|\n");
    printf("|   0   |  Sair do programa.                                                                                 |\n");
    printf("|       |                                                                                                    |\n"); 
    printf(" ------------------------------------------------------------------------------------------------------------ \n");
}   

