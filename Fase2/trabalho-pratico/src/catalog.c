#include "../includes/catalog.h"

struct catalog {
    CACHE_USERS *cache_users;
    CACHE_FLIGHTS *cache_flights;
    CACHE_RESERVATIONS *cache_reservations;
    CACHE_PASSENGERS *cache_passengers;
};

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

Catalog *create_catalog(char *entry_files) {
    char *users = pointer_file(entry_files,"users.csv");
    char *flights = pointer_file(entry_files,"flights.csv"); 
    char *reservations = pointer_file(entry_files,"reservations.csv"); 
    char *passengers = pointer_file(entry_files,"passengers.csv");

    Catalog *cat = malloc(sizeof(Catalog));

    int cap = 100000;

    cat->cache_users = create_new_cache_users(cap);
    cat->cache_flights = create_new_cache_flights(cap);
    cat->cache_reservations = create_new_cache_reservations(cap);
    cat->cache_passengers = create_new_cache_passengers(cap);

    create_users_valid_file(users);
    create_flights_valid_file(flights);
    create_passengers_valid_file(passengers, cat->cache_flights, cat->cache_passengers, cat->cache_reservations, cat->cache_users);
    create_reservations_valid_file(reservations, cat->cache_passengers, cat->cache_reservations, cat->cache_users);
    
    create_users_aux_file();

    free(users);
    free(flights);
    free(reservations);
    free(passengers);
    return cat;
}

void delete_catalog(Catalog *cat) {
    delete_cache_users(cat->cache_users);
    delete_cache_flights(cat->cache_flights);
    delete_cache_reservations(cat->cache_reservations);
    delete_cache_passengers(cat->cache_passengers);
    free(cat);
}

char *query1(char *input, Catalog *cat){
    char *output = NULL;
    if(verify_only_numbers(input)==1) output = display_flight(input, cat->cache_flights);
    else {
        if(strncmp(input, "Book", 4)==0) output = display_reservation(input, cat->cache_reservations);
        else output = display_user(input, cat->cache_passengers, cat->cache_reservations, cat->cache_users);
    }
    return output;
}

//char **query2(char *input){
//    char **output = 
//}

char *query3(char *input){
    char *output = calculate_average_rating(input);
    return output;
}

char **query4(char *input){
    char **output = NULL;
    GList *list = sort_reservations_data(input);
    if (list) {
        output = malloc(sizeof(char *) * (g_list_length(list) + 1));
        int i = 0;
        for (GList *l = list; l != NULL; l = l->next) {
            Reservations *res = l->data;
            char *begin_date = date_to_string(get_begin_date(res));
            char *end_date = date_to_string(get_end_date(res));
            if (begin_date == NULL || end_date == NULL) continue; 
            output[i] = malloc(256);
            snprintf(output[i], 256, "%s;%s;%s;%s;%s;%.3f", get_id_reservations(res), begin_date, end_date,
                        get_user_id(res), get_rating(res), get_total_price(res));
            i++;
        }
        output[i] = NULL;
    }
    
    return output;
}

char **query5(char *input){
    char *origin = strsep(&input, " ");
    Datetime begin_date = valid_date_time(strsep(&input, " "));
    Datetime end_date = valid_date_time(strsep(&input, " "));
    char **output = NULL;
    GList *list = sort_flights_data(origin, begin_date, end_date);
    if (list) {
        output = malloc(sizeof(char *) * (g_list_length(list) + 1));
        int i = 0;
        for (GList *l = list; l != NULL; l = l->next) {
            Flights *fli = l->data;
            output[i] = malloc(256);
            snprintf(output[i], 256, "%s;%s;%s;%s;%s", get_id_flights(fli), datetime_to_string(get_schedule_departure_date(fli)), 
                        get_destination(fli), get_airline(fli), get_plane(fli));
            i++;
        }
        output[i] = NULL;
    }
    return output;
}

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

char **query9(char *input){
    char **output = search_users_with_prefix(input); 
    return output;
}






/*

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

void run_queries(char *queries_path, int query, Catalog *cat){
    int i = (int) strtol(strsep(&queries_path, " "), (char **) NULL, 10);
    switch(i){
        case 1:
            //if(queries_path[1] == '0') {
            //    if(queries_path[2] == 'F') {
            //        write_to_file_mul_line(query10F(arg_query), query);
            //    }
            //    else{
            //        write_to_file_one_line(query10(arg_query), query);
            //    }                
            //    break;
            //} else 
            if(queries_path[1] == 'F') {
                //char *arg_query = strsep(&queries_path, " ");
                //write_to_file_mul_line(query1F(arg_query), query);
            }
            else{
                char *arg_query = strsep(&queries_path, " ");
                write_to_file_one_line(query1(arg_query, cat), query);
            }
            break;
        case 2:
            //if(queries_path[1] == 'F') {
            //    write_to_file_mul_line(query2F(arg_query), query);
            //}
            //else{
            //    write_to_file_mul_line(query2(arg_query), query);
            //}
            break;
        case 3:
            if(queries_path[1] == 'F') {
            //    char *arg_query = strsep(&queries_path, " ");
            //    write_to_file_mul_line(query3F(arg_query), query);
            }
            else{
                char *arg_query = strsep(&queries_path, " ");
                write_to_file_one_line(query3(arg_query), query);
            }
            break;
        case 4:
            if(queries_path[1] == 'F') {
            //    write_to_file_mul_line(query4F(arg_query), query);
            }
            else{
                //write_to_file_mul_line(query4(queries_path), query);
            }
            break;
        case 5:
            if(queries_path[1] == 'F') {
            //    write_to_file_mul_line(query5F(arg_query), query);
            }
            else{
                //write_to_file_mul_line(query5(queries_path), query);
            }
            break;
        case 6:
            //if(queries_path[1] == 'F') {
            //    write_to_file_mul_line(query6F(arg_query), query);
            //}
            //else{
            //    write_to_file_mul_line(query6(arg_query), query);
            //}
            break;
        case 7:
            //if(queries_path[1] == 'F') {
            //    write_to_file_mul_line(query7F(arg_query), query);
            //}
            //else{
            //    write_to_file_mul_line(query7(arg_query), query);
            //}
            break;
        case 8:
            if(queries_path[1] == 'F') {
            //    write_to_file_mul_line(query8F(arg_query), query);
            }
            else{
                write_to_file_one_line(query8(queries_path), query);
            }
            break;
        case 9:
            if(queries_path[1] == 'F') {
            //    write_to_file_mul_line(query9F(arg_query), query);
            }
            else{
                write_to_file_mul_line(query9(queries_path), query);
            }
            break;
    }
}

int run_batch(char* inputs_path, char* queries_path) {
    Catalog *cat = create_catalog(inputs_path);

    FILE *fp;
    fp = fopen(queries_path, "r");
    if (!fp) {
        perror("Error");
        return -1;
    }

    char *line = NULL;
    size_t len = 0;
    int op = 1;

    while (getline(&line, &len, fp) != -1) {
        line[strcspn(line, "\n")] = 0;
        run_queries(line, op, cat);
        op++;
    }

    free(line);
    fclose(fp);
    return 0;
}

int run_tests(char* inputs_path, char* queries_path, char* results_path){
    Catalog *cat = create_catalog(inputs_path);

    FILE *fp;
    fp = fopen(queries_path, "r");
    if (!fp) {
        perror("Error");
        return -1;
    }

    char *line = NULL;
    size_t len = 0;
    int op = 1;

    clock_t start, end;
    double cpu_time_used;

    while (getline(&line, &len, fp) != -1) {
        line[strcspn(line, "\n")] = 0;
        start = clock();
        run_queries(line, op, cat);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("The time to run query %d was %f\n", op, cpu_time_used);
        compare_files(results_path, op);
        op++;
    }

    free(line);
    fclose(fp);
    delete_catalog(cat);
    return 0;
}

int compare_files(char* path, int n) {
    char file1[300], file2[300];
    sprintf(file1, "./Resultados/command%d_output.txt", n);
    sprintf(file2, "./%s/command%d_output.txt", path, n);

    FILE *fp1 = fopen(file1, "r");
    FILE *fp2 = fopen(file2, "r");

    if (!fp1 || !fp2) {
        perror("Error");
        return -1;
    }

    char *line1 = NULL;
    char *line2 = NULL;

    size_t len1 = 0;
    size_t len2 = 0;

    int i = 1;

    while (getline(&line1, &len1, fp1) != -1 && getline(&line2, &len2, fp2) != -1) {
        line1[strcspn(line1, "\n")] = 0;
        line2[strcspn(line2, "\n")] = 0;
        if (strcmp(line1, line2) != 0) {
            printf("\nline: %d\n", i);
            printf("obtain: %s\n", line1);
            printf("expected: %s\n\n", line2);
            return 0;
        }
        i++;
    }

    free(line1);
    free(line2);
    fclose(fp1);

    return 1;
}

int run_interactive(){
    printf("Insira o caminho para a pasta com os ficheiros de entrada: \n");

    char inputs_path[30];

    if(fgets(inputs_path, 30, stdin) == NULL){
        perror("fgets failed");
        return -1;
    }
    Catalog *cat = create_catalog(inputs_path);
    printf("\n");
    print_entry_menu();
    int op = 0;
    while(op == 0){
        printf("\nInsira um número de 1 a 10 para escolher a query a executar ou 0 para sair: \n");
        char query_arg[15];
        if(fgets(query_arg, 15, stdin) == NULL){
            perror("fgets failed");
            return -1;
        }
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
                if(fgets(input, 15, stdin) == NULL){
                    perror("fgets failed");
                    return -1;
                }
                char *output = query3(input);
                write_to_terminal(output);
                break;
            case 4:
                printf("Insira o id do hotel: \n");
                char input[15];
                if(fgets(input, 15, stdin) == NULL){
                    perror("fgets failed");
                    return -1;
                }
                char **output = query4(input);
                write_to_terminal_mul_line(output);
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
