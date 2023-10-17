#include "../../includes/model/catalog.h"

typedef struct catalog {
    CAT_USERS *cat_users;
    CAT_FLIGHTS *cat_flights;
    CAT_RESERVATIONS *cat_reservations;
} Catalog;

Catalog *create_Catalog(char *entry_files) {
    Catalog *c = malloc(sizeof(struct catalog));
    c->cat_users = create_cat_users(entry_files);
    c->cat_flights = create_cat_flights(entry_files);
    c->cat_reservations = create_cat_reservations(entry_files);
    return c;
}

void delete_Catalog(Catalog *c) {
    delete_cat_users(c->cat_users);
    delete_cat_flights(c->cat_flights);
    delete_cat_reservations(c->cat_reservations);
    free(c);
}


// queries

// funcao parse queries


/* função responsável por abrir o ficheiro de input com as queries
 * chama a função parseQueries para dar parse a cada linha */
int runBatch(char **input_file) {

    Catalog *c = create_Catalog(input_file[1]);

    system("exec rm -rf Resultados/*");

    FILE *fp;
    fp = fopen(input_file[2], "r");
    if (!fp) {
        perror("Error");
        return -1;
    }

    char *line = NULL;
    size_t len = 0;
    int output_number = 1;

    while (getline(&line, &len, fp) != -1) {
        line[strcspn(line, "\n")] = 0;
        parseQueries(line, c, output_number);
        output_number++;
    }

    free(line);
    fclose(fp);

    delete_Catalog(c);

    return 0;
}

