#include "../../includes/model/catalog.h"
typedef struct catalog {
    CAT_USERS *cat_users;
    CAT_FLIGHTS *cat_flights;
    CAT_RESERVATIONS *cat_reservations;
    CAT_PASSENGERS *cat_passengers;
} catalog;

char* pointer_file (char *path, char *file){
    char *file_name = malloc(strlen(path) + strlen(file) + 2); // + 2 por causa do \0 e pq n sabes se o path acaba em / ou nao
    
    strcat(file_name, path);
    if (path[strlen(path)] != '/')
        strcat(file_name,"/");
    strcat(file_name, file);
    return file_name; 
}

catalog *create_catalog(char *entry_files) {
    char *users = pointer_file(entry_files,"users.csv"), *flights =  pointer_file(entry_files,"flights.csv"), *reservations = pointer_file(entry_files,"reservations.csv"), *passengers = pointer_file(entry_files,"passengers.csv");
    catalog *cat = malloc(sizeof(struct catalog));
    cat->cat_users = create_cat_users(users);
    cat->cat_flights = create_cat_flights(flights);
    cat->cat_reservations = create_cat_reservations(reservations);
    cat->cat_passengers = create_cat_passengers(passengers);
    return cat;
}

void delete_catalog(catalog *cat) {
    delete_cat_users(cat->cat_users);
    delete_cat_flights(cat->cat_flights);
    delete_cat_reservations(cat->cat_reservations);
    free(cat);
}


void query1(catalog *cat, char *id){
    printf("Utilizador: %s\n\n", id);
    Users *user = query1_aux(cat->cat_users, id);
    if (user == NULL){
        printf("Utilizador não encontrado\n");
        return;
    }

    //int idade = calculate_age(user->birth_date);
    printf("Nome: %s\n", get_name(user));
    printf("Sexo: %s\n",get_sex(user));
    //printf("Idade: %d\n", idade);
    printf("Código do País: %s\n", get_country_code(user));
    printf("Passaporte: %s\n", get_passport(user));
    printf("Número de Voos: %d\n", get_flights_total(user));

}



// funcao parse queries
void parse_queries(char *line, catalog *cat, int output_num){

    int i = (int) strtol(strsep(&line, " "), (char **) NULL, 10);

    switch (i){
        case 1:
            char *id = strsep(&line, " ");
            break;
    }

}


int run_batch(char **input_file) {

    catalog *cat = create_catalog(input_file[1]);
    update_values_users(cat->cat_users, cat->cat_passengers);

    FILE *file_query;
    file_query = fopen(input_file[2], "r");
    
    if(file_query == NULL){
        perror("Erro:");
        exit(1);
    }
    char line[100];
    int buffer_size = 100;
    int num = 0;

    while(fgets(line, buffer_size, file_query)){
        char *query, *n_query, *query_arg, *arg1, *arg2, *arg3;
        query = strdup(line);
        n_query = strsep(&query, " ");
        query_arg = strsep(&query, "\n");
        //unsigned i;
        num++;
        switch (n_query[0]){
            case '1':
                query1(cat, query_arg);
                break;
            default:
                break;
        }
    }

    delete_catalog(cat);
    return 0;
}

