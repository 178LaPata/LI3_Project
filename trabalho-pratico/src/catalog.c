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

    create_users_valid_file(users);
    create_users_aux_file();
    create_flights_valid_file(flights);
    create_reservations_valid_file(reservations);
    create_passengers_valid_file(passengers);

    free(users);
    free(flights);
    free(reservations);
    free(passengers);
}

/*
char *query1(char *input, catalog *cat){
    char *output;
    if(verify_only_numbers(input)==1){
        Flights *fli = query1_flights_aux(cat, input);
        if (fli) output = display_flights(fli, input);
    } else {
        if(strncmp(input, "Book", 4)==0){
            Reservations *r = query1_reservations_aux(cat, input);
            if (r) output = display_reservation(r, input);
        } else {
            Users *user = query1_users_aux(cat, input);
            if (user) output = display_user(user, input);
        }
    }
    return output;
}

char **query2(char *input, catalog *cat){
    char **output = 
}

char *query3(char *input, catalog *cat){
    char *avgr = calculate_average_rating(cat->cat_reservations, input);
    return avgr;
}

char **query4(char *input, catalog *cat){
    char **output = 
}

char **query5(char *input, catalog *cat){
    char **output = 
}

char **query6(char *input, catalog *cat){
    char **output = 
}

char **query7(char *input, catalog *cat){
    char **output = 
}

char *query8(char *input, catalog *cat){
    char **output = 
}

char **query9(char *input, catalog *cat){
    char **output = 
}

char **query10(char *input, catalog *cat){
    char **output = 
}

char **query1F(char *input, catalog *cat){
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

char **query2F(char *input, catalog *cat){
    char **output = 
}

char **query3F(char *input, catalog *cat){
    char *avgr = calculate_average_rating(cat->cat_reservations, input);
    return avgr;
}

char **query4F(char *input, catalog *cat){
    char **output = 
}

char **query5F(char *input, catalog *cat){
    char **output = 
}

char **query6F(char *input, catalog *cat){
    char **output = 
}

char **query7F(char *input, catalog *cat){
    char **output = 
}

char *query8F(char *input, catalog *cat){
    char **output = 
}

char **query9F(char *input, catalog *cat){
    char **output = 
}

char **query10F(char *input, catalog *cat){
    char **output = 
}

void run_queries(char *queries_path, catalog *cat, int query){
    int i = (int) strtol(strsep(&queries_path, " "), (char **) NULL, 10);
    switch(i){
        case 1:
            if(queries_path[1] == '0') {
                if(queries_path[2] == 'F') {
                    char *arg_query = strsep(&queries_path, " ");
                    write_to_file_mul_line(query10F(arg_query, cat), query);
                }
                else{
                    char *arg_query = strsep(&queries_path, " ");
                    write_to_file_one_line(query10(arg_query, cat), query);
                }                
                break;
            } else if(queries_path[1] == 'F') {
                char *arg_query = strsep(&queries_path, " ");
                write_to_file_mul_line(query1F(arg_query, cat), query);
            }
            else{
                char *arg_query = strsep(&queries_path, " ");
                write_to_file_one_line(query1(arg_query, cat), query);
            }
            break;
        case 2:
            if(queries_path[1] == 'F') {
                char *arg_query = strsep(&queries_path, " ");
                write_to_file_mul_line(query2F(arg_query, cat), query);
            }
            else{
                char *arg_query = strsep(&queries_path, " ");
                write_to_file_mul_line(query2(arg_query, cat), query);
            }
            break;
        case 3:
            if(queries_path[1] == 'F') {
                char *arg_query = strsep(&queries_path, " ");
                write_to_file_mul_line(query3F(arg_query, cat), query);
            }
            else{
                char *arg_query = strsep(&queries_path, " ");
                write_to_file_mul_line(query3(arg_query, cat), query);
            }
            break;
        case 4:
            if(queries_path[1] == 'F') {
                char *arg_query = strsep(&queries_path, " ");
                write_to_file_mul_line(query4F(arg_query, cat), query);
            }
            else{
                char *arg_query = strsep(&queries_path, " ");
                write_to_file_mul_line(query4(arg_query, cat), query);
            }
            break;
        case 5:
            if(queries_path[1] == 'F') {
                char *arg_query = strsep(&queries_path, " ");
                write_to_file_mul_line(query5F(arg_query, cat), query);
            }
            else{
                char *arg_query = strsep(&queries_path, " ");
                write_to_file_mul_line(query5(arg_query, cat), query);
            }
            break;
        case 6:
            if(queries_path[1] == 'F') {
                char *arg_query = strsep(&queries_path, " ");
                write_to_file_mul_line(query6F(arg_query, cat), query);
            }
            else{
                char *arg_query = strsep(&queries_path, " ");
                write_to_file_mul_line(query6(arg_query, cat), query);
            }
            break;
        case 7:
            if(queries_path[1] == 'F') {
                char *arg_query = strsep(&queries_path, " ");
                write_to_file_mul_line(query7F(arg_query, cat), query);
            }
            else{
                char *arg_query = strsep(&queries_path, " ");
                write_to_file_mul_line(query7(arg_query, cat), query);
            }
            break;
        case 8:
            if(queries_path[1] == 'F') {
                char *arg_query = strsep(&queries_path, " ");
                write_to_file_mul_line(query8F(arg_query, cat), query);
            }
            else{
                char *arg_query = strsep(&queries_path, " ");
                write_to_file_mul_line(query8(arg_query, cat), query);
            }
            break;
        case 9:
            if(queries_path[1] == 'F') {
                char *arg_query = strsep(&queries_path, " ");
                write_to_file_mul_line(query9F(arg_query, cat), query);
            }
            else{
                char *arg_query = strsep(&queries_path, " ");
                write_to_file_mul_line(query9(arg_query, cat), query);
            }
            break;
    }
}

*/
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
    int op = 1;

    while (getline(&line, &len, fp) != -1) {
        line[strcspn(line, "\n")] = 0;
        //run_queries(line, cat, op);
        printf("%s\n", line);
        op++;
    }

    free(line);
    fclose(fp);
    return 0;
}
