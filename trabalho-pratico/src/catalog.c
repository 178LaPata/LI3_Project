#include "../includes/catalog.h"

char* pointer_file (char *path, char *file) {
    char *file_name = malloc(strlen(path) + strlen(file) + 2);
    if (file_name == NULL) {
        return NULL;
    }

    file_name[0] = '\0';

    strcat(file_name, path);
    if (path[strlen(path) - 1] != '/') {
        strcat(file_name, "/");
    }
    strcat(file_name, file);

    return file_name; 
}

void create_catalog(char *entry_files) {
    char *users = pointer_file(entry_files,"users.csv");
    char *flights = pointer_file(entry_files,"flights.csv"); 
    char *reservations = pointer_file(entry_files,"reservations.csv"); 
    char *passengers = pointer_file(entry_files,"passengers.csv");

    int cap = 100000;

    CACHE_USERS *cache_users = create_new_cache_users(cap);
    CACHE_FLIGHTS *cache_flights = create_new_cache_flights(cap);
    CACHE_RESERVATIONS *cache_reservations = create_new_cache_reservations(cap);
    CACHE_PASSENGERS *cache_passengers = create_new_cache_passengers(cap);
    
    create_users_valid_file(users);
    create_flights_valid_file(flights);
    create_reservations_valid_file(reservations, cache_users);
    create_passengers_valid_file(passengers, cache_users, cache_flights);
    
    create_flights_aux_file();
    //create_reservations_aux_file();
    //create_users_aux_file(cache_passengers);
    //create_passengers_aux_file();

    free(users);
    free(flights);
    free(reservations);
    free(passengers);
}


//char *query1(char *input){
//
//}
//
//char **query2(char *input){
//    char **output = 
//}
//
char *query3(char *input){
    char *avgr = calculate_average_rating(input);
    return avgr;
}
//
//char **query4(char *input){
//    char **output = 
//}
//
//char **query5(char *input){
//    char **output = 
//}
//
//char **query6(char *input){
//    char **output = 
//}
//
//char **query7(char *input){
//    char **output = 
//}

char *query8(char *input){
    char *id = strsep(&input, " ");
    char *begin_date = strsep(&input, " ");
    char *end_date = strsep(&input, " ");
    Date bd = valid_date(begin_date);
    Date ed = valid_date(end_date);
    char *output = calculate_total_revenue(id, bd, ed);
    return output;
}

/*
char **query9(char *input){
    char **output = 
}

char **query10(char *input){
    char **output = 
}
char **query1F(char *input){
    char **output;
    int i = 0;
    if(verify_only_numbers(input)==1){
        Flights *fli = query1_flights_aux(cat, input);
        if (fli){
            output = displayF_flights(fli, input, i);
            i++;
        } 
    } else {
        if(strncmp(input, "Book", 4)==0){
            Reservations *r = query1_reservations_aux(cat, input);
            if (r){
                output = displayF_reservation(r, input, i);
                i++;
            }
        } else {
            Users *user = query1_users_aux(cat, input);
            if (user) {
                output = displayF_user(user, input, i);
                i++;
            } 
        }
    }
    return output;
}

char **query2F(char *input){
    char **output = 
}

char **query3F(char *input){
    char *avgr = calculate_average_rating(cat->cat_reservations, input);
    return avgr;
}

char **query4F(char *input){
    char **output = 
}

char **query5F(char *input){
    char **output = 
}

char **query6F(char *input){
    char **output = 
}

char **query7F(char *input){
    char **output = 
}

char *query8F(char *input){
    char **output = 
}

char **query9F(char *input){
    char **output = 
}

char **query10F(char *input){
    char **output = 
}
*/

void run_queries(char *queries_path, int query){
    int i = (int) strtol(strsep(&queries_path, " "), (char **) NULL, 10);
    switch(i){
        case 1:
            //if(queries_path[1] == '0') {
            //    if(queries_path[2] == 'F') {
            //        char *arg_query = strsep(&queries_path, " ");
            //        write_to_file_mul_line(query10F(arg_query), query);
            //    }
            //    else{
            //        char *arg_query = strsep(&queries_path, " ");
            //        write_to_file_one_line(query10(arg_query), query);
            //    }                
            //    break;
            //} else if(queries_path[1] == 'F') {
            //    char *arg_query = strsep(&queries_path, " ");
            //    write_to_file_mul_line(query1F(arg_query), query);
            //}
            //else{
            //    char *arg_query = strsep(&queries_path, " ");
            //    write_to_file_one_line(query1(arg_query), query);
            //}
            break;
        case 2:
            //if(queries_path[1] == 'F') {
            //    char *arg_query = strsep(&queries_path, " ");
            //    write_to_file_mul_line(query2F(arg_query), query);
            //}
            //else{
            //    char *arg_query = strsep(&queries_path, " ");
            //    write_to_file_mul_line(query2(arg_query), query);
            //}
            break;
        case 3:
            if(queries_path[1] == 'F') {
                //char *arg_query = strsep(&queries_path, " ");
                //write_to_file_mul_line(query3F(arg_query), query);
            }
            else{
                char *arg_query = strsep(&queries_path, " ");
                write_to_file_one_line(query3(arg_query), query);
            }
            break;
        case 4:
            //if(queries_path[1] == 'F') {
            //    char *arg_query = strsep(&queries_path, " ");
            //    write_to_file_mul_line(query4F(arg_query), query);
            //}
            //else{
            //    char *arg_query = strsep(&queries_path, " ");
            //    write_to_file_mul_line(query4(arg_query), query);
            //}
            break;
        case 5:
            //if(queries_path[1] == 'F') {
            //    char *arg_query = strsep(&queries_path, " ");
            //    write_to_file_mul_line(query5F(arg_query), query);
            //}
            //else{
            //    char *arg_query = strsep(&queries_path, " ");
            //    write_to_file_mul_line(query5(arg_query), query);
            //}
            break;
        case 6:
            //if(queries_path[1] == 'F') {
            //    char *arg_query = strsep(&queries_path, " ");
            //    write_to_file_mul_line(query6F(arg_query), query);
            //}
            //else{
            //    char *arg_query = strsep(&queries_path, " ");
            //    write_to_file_mul_line(query6(arg_query), query);
            //}
            break;
        case 7:
            //if(queries_path[1] == 'F') {
            //    char *arg_query = strsep(&queries_path, " ");
            //    write_to_file_mul_line(query7F(arg_query), query);
            //}
            //else{
            //    char *arg_query = strsep(&queries_path, " ");
            //    write_to_file_mul_line(query7(arg_query), query);
            //}
            break;
        case 8:
            if(queries_path[1] == 'F') {
                //char *arg_query = strsep(&queries_path, " ");
                //write_to_file_mul_line(query8F(arg_query), query);
            }
            else{
                char *arg_query = strsep(&queries_path, " ");
                write_to_file_one_line(query8(arg_query), query);
            }
            break;
        case 9:
            //if(queries_path[1] == 'F') {
            //    char *arg_query = strsep(&queries_path, " ");
            //    write_to_file_mul_line(query9F(arg_query), query);
            //}
            //else{
            //    char *arg_query = strsep(&queries_path, " ");
            //    write_to_file_mul_line(query9(arg_query), query);
            //}
            break;
    }
}

int run_batch(char* inputs_path, char* queries_path) {
    create_catalog(inputs_path);
    system("exec rm -rf Resultados/*");

    FILE *fp;
    fp = fopen(queries_path, "r");
    if (!fp) {
        perror("Error");
        return -1;
    }

    char *line = NULL;
    size_t len = 0;
    //int op = 1;

    while (getline(&line, &len, fp) != -1) {
        line[strcspn(line, "\n")] = 0;
        //run_queries(line, op);
        //op++;
    }

    free(line);
    fclose(fp);
    return 0;
}

int run_interactive(){
    printf("Insira o caminho para a pasta com os ficheiros de entrada: \n");

    char inputs_path[30];

    fgets(inputs_path, 30, stdin);
    create_catalog(inputs_path);
    printf("\n");
    print_entry_menu();
    int op = 0;
    while(op == 0){
        printf("\nInsira um número de 1 a 10 para escolher a query a executar ou 0 para sair: \n");
        char query_arg[15];
        fgets(query_arg, 15, stdin);
        op = (int) strtol(query_arg, (char **) NULL, 10);
        switch(op){
            case 1:
                printf("Insira o id de um voo/utilizador/reserva: \n");
                //char input[15];
                //fgets(input, 15, stdin);
                //char *output = query1(input);
                break;
            case 2:
                printf("Insira o id do utilizador: \n");

                break;
            case 3:
                printf("Insira o id do hotel: \n");
                char input[15];
                fgets(input, 15, stdin);
                char *output = query3(input);
                write_to_terminal(output);
                break;
            case 4:
                printf("Insira o id do hotel: \n");
                break;
            case 5:
                printf("Insira a origem: \n");
                printf("Insira a data de inicio: \n");
                printf("Insira a data de fim: \n");
                break;
            case 6:
                printf("Insira o ano: \n");
                printf("Insira o número máximo de aeroportos a apresentar: \n");
                break;
            case 7:
                printf("Insira o número máximo de aeroportos a apresentar: \n");
                break;
            case 8:
                printf("Insira o id do hotel: \n");
                printf("Insira a data de inicio: \n");
                printf("Insira a data de fim: \n");
                break;
            case 9:
                printf("Insira o prefixo: \n");
                break;
            case 10:    
            // nao faco ideia
                break;
            case 0:
                op = 1;
                break;
        }
    }
    return 0;
}
