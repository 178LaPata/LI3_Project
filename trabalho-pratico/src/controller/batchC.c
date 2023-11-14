#include "../../includes/controller/batchC.h"

int run_batch(char *inputs_path, char *queries_path) {
    catalog *cat = create_catalog(inputs_path);

    if (cat == NULL) {
        printf("Invalid inputs path: %s\n", inputs_path);
        exit(1);
    }

    char *queryDup = strdup(queries_path);
    int r = run_queries(cat, queryDup);

    delete_catalog(cat);

    return r;
}

int run_queries(catalog *cat, char *queries_path) {
    char *query = NULL;
    size_t len = 0;
    char file[BUFFER];
    int n_query = 1;
    FILE *fp_queries = fopen(queries_path, "r");

    while (getline(&query, &len, fp_queries) != -1) {
        sprintf(file, "./Resultados/command%d_output.txt", n_query++);
        FILE *fp_output = fopen(file, "w");
        run_query(cat, query, fp_output);
        fclose(fp_output);
    }

    free(query);

    return n_query;
}

int run_query(catalog *cat, char *queries_path, FILE *fp_output) {
    switch (queries_path[0]){
        case '1':
            query1(cat, queries_path, fp_output);
            break;
        case '2':
            //query2(cat, queries_path);
            break;
        case '3':
            //query3(cat, queries_path);
            break;
        case '4':
            break;
        case '5':
            break;
        case '6':
            break;
        case '7':
            break;
        case '8':
            //query8(cat, queries_path, fp_output);
            break;            
        default:
            break;
    }
    return 0;
}

void query1(catalog *cat, char *query, FILE *fp) {
    char *nr_query = strsep(&query, " ");
    char *arg_query = strsep(&query, "\n");
    if(str_is_num(arg_query)==0){
        Flights *fli = query1_flights_aux(cat, arg_query);
        if (fli) batch_print_query1_flights(fli, fp);
    } else {
        if(strncmp(arg_query, "Book", 4)==0){
            Reservations *r = query1_reservations_aux(cat, arg_query);
            if (r) batch_print_query1_reservations(r, fp);
        else {
            Users *user = query1_users_aux(cat, arg_query);
            if (user) batch_print_query1_user(user, fp);
        }
        }
    }
}
