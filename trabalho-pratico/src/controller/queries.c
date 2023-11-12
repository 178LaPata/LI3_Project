#include "../../includes/model/catalog.h"

// sq isto pode ser feito nos users 
// estando aqui esta funcao nao pode ter prints ig 
void query1(catalog *cat, char *id){
    printf("Utilizador: %s\n\n", id);
    Users *user = query1_aux(cat->cat_users, id);
    if (user == NULL){
        printf("Utilizador não encontrado\n");
        return;
    }
    printDate(get_birth_date(user));

    int idade = calculate_age(get_birth_date(user));

    printf("Nome: %s\n", get_name(user));
    printf("Sexo: %s\n",get_sex(user));
    printf("Idade: %d\n", idade);
    printf("Código do País: %s\n", get_country_code(user));
    printf("Passaporte: %s\n", get_passport(user));
    printf("Número de Voos: %d\n", get_flights_total(user));

}



// funcao que da parse as queries
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

