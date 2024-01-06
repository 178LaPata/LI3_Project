#include "../../includes/controller/batchC.h"

int run_batch(char* inputs_path, char* queries_path) {
    catalog *cat = create_catalog(inputs_path);

    if (cat == NULL) {
        printf("Invalid inputs path: %s\n", inputs_path);
        exit(1);
    }

    char *queryDup = strdup(queries_path);
    if (queryDup == NULL) {
        delete_catalog(cat);
        exit(1);
    }

    int r = run_queries(cat, queryDup);

    free(queryDup);
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
            if(queries_path[1] == '0') {
                //if(queries_path[2] == 'F') query10F(cat, queries_path, fp_output);
                //else query10(cat, queries_path, fp_output);
                break;
            } else if(queries_path[1] == 'F') query1F(cat, queries_path, fp_output);
            else query1(cat, queries_path, fp_output);
            break;
        case '2':
            //if(queries_path[1] == 'F') query2F(cat, queries_path, fp_output);
            //else query2(cat, queries_path, fp_output);
            break;
        case '3':
            if(queries_path[1] == 'F') query3F(cat, queries_path, fp_output);
            else query3(cat, queries_path, fp_output);
            break;
        case '4':
            if(queries_path[1] == 'F') query4F(cat, queries_path, fp_output);
            else query4(cat, queries_path, fp_output);
            break;
        case '5':
            if(queries_path[1] == 'F') query5F(cat, queries_path, fp_output);
            else query5(cat, queries_path, fp_output);
            break;
        case '6':
            //if(queries_path[1] == 'F') query6F(cat, queries_path, fp_output);
            //else query6(cat, queries_path, fp_output);
            break;
        case '7':
            //if(queries_path[1] == 'F') query7F(cat, queries_path, fp_output);
            //else query7(cat, queries_path, fp_output);
            break;
        case '8':
            if(queries_path[1] == 'F') query8F(cat, queries_path, fp_output);
            else query8(cat, queries_path, fp_output);
            break;  
        case '9':
            if(queries_path[1] == 'F') query9F(cat, queries_path, fp_output);
            else query9(cat, queries_path, fp_output);
            break;          
        default:
            break;
    }
    return 0;
}

void query1(catalog *cat, char *query, FILE *fp) {
    (void)strsep(&query, " ");
    char *arg_query = strsep(&query, "\n");

    if(verify_only_numbers(arg_query)==1){
        Flights *fli = query1_flights_aux(cat, arg_query);
        if (fli) batch_print_query1_flights(fli, fp);
    } else {
        if(strncmp(arg_query, "Book", 4)==0){
            Reservations *r = query1_reservations_aux(cat, arg_query);
            if (r) batch_print_query1_reservations(r, fp);
        } else {
            Users *user = query1_users_aux(cat, arg_query);
            if (user) batch_print_query1_user(user, fp);
        }
    }
}

void query1F(catalog *cat, char *query, FILE *fp) {
    (void)strsep(&query, " ");
    char *arg_query = strsep(&query, "\n");
    int i = 0;

    if(verify_only_numbers(arg_query)==1){
        Flights *fli = query1_flights_aux(cat, arg_query);
        if (fli){
            i++;
            batch_print_query1F_flights(fli, fp, i);
        }
    } else {
        if(strncmp(arg_query, "Book", 4)==0){
            Reservations *r = query1_reservations_aux(cat, arg_query);
            if (r){
                i++;
                batch_print_query1F_reservations(r, fp, i);
            }
        } else {
            Users *user = query1_users_aux(cat, arg_query);
            if (user){
                i++;
                batch_print_query1F_user(user, fp, i);
            }
        }
    }
}

void query3(catalog *cat, char *query, FILE *fp) {
    (void)strsep(&query, " ");
    char *arg_query = strsep(&query, "\n");
    double total = 0.0;
    total = query3_aux(cat, arg_query);
    batch_print_query3(total, fp);
}

void query3F(catalog *cat, char *query, FILE *fp) {
    (void)strsep(&query, " ");
    char *arg_query = strsep(&query, "\n");
    int i = 0;
    double total = 0.0;
    total = query3_aux(cat, arg_query);
    i++;
    batch_print_query3F(total, fp, i);
}

void query4(catalog *cat, char *query, FILE *fp){
    (void)strsep(&query, " ");
    char *arg_query = strsep(&query, "\n");

    GList *list = query4_aux(cat, arg_query);
    GList *aux = list;
    while(aux){
        Reservations *r = (Reservations *) aux->data;
        batch_print_query4(r, fp);
        aux = aux->next;
    }
    g_list_free(list);

}

void query4F(catalog *cat, char *query, FILE *fp){
    (void)strsep(&query, " ");
    char *arg_query = strsep(&query, "\n");
    int i = 0;

    GList *list = query4_aux(cat, arg_query);
    GList *aux = list;
    while(aux){
        Reservations *r = (Reservations *) aux->data;
        i++;
        batch_print_query4F(r, fp, i);
        aux = aux->next;
        if (aux)
            fprintf(fp, "\n");
    }
    g_list_free(list);

}

void query5(catalog *cat, char *query, FILE *fp){
    (void)strsep(&query, " ");
    char *origem = strsep(&query, " ");
    query++;
    char *beginDate = strsep(&query, "\"");
    query += 2;
    char *endDate = strsep(&query, "\"");

    Datetime beginD = valid_date_time(beginDate);
    Datetime endD = valid_date_time(endDate);

    GList *list = query5_aux(cat, origem, beginD, endD);
    GList *aux = list;
    while(aux){
        Flights *fli = (Flights *) aux->data;
        batch_print_query5(fli, fp);
        aux = aux->next;
    }
    g_list_free(list);
    free_datetime(beginD);
    free_datetime(endD);
}

void query5F(catalog *cat, char *query, FILE *fp){
    (void)strsep(&query, " ");
    char *origem = strsep(&query, " ");
    query++;
    char *beginDate = strsep(&query, "\"");
    query += 2;
    char *endDate = strsep(&query, "\"");

    Datetime beginD = valid_date_time(beginDate);
    Datetime endD = valid_date_time(endDate);

    int i = 0;
    GList *list = query5_aux(cat, origem, beginD, endD);
    GList *aux = list;
    while(aux){
        Flights *fli = (Flights *) aux->data;
        i++;
        batch_print_query5F(fli, fp, i);
        aux = aux->next;
        if (aux)
            fprintf(fp, "\n");
    }
    g_list_free(list);
    free_datetime(beginD);
    free_datetime(endD);
}

void query6(catalog *cat, char *query, FILE *fp){
    (void)strsep(&query, " ");
    char *year = strsep(&query, " ");
    char *n = strsep(&query, "\n");

    int n_int = atoi(n);
    int i = 0;
    GList *list = query6_aux(cat, year);
    GList *aux = list;
    while(aux && i < n_int){
        ORIGIN_PASSENGER_COUNT *opc = (ORIGIN_PASSENGER_COUNT *) aux->data;
        batch_print_query6(opc, fp);
        aux = aux->next;
        i++;
    }
    g_list_free_full(list, (GDestroyNotify) free_origin_passenger_count);
}

void query6F(catalog *cat, char *query, FILE *fp){
    (void)strsep(&query, " ");
    char *year = strsep(&query, " ");
    char *n = strsep(&query, "\n");

    int n_int = atoi(n);
    int i = 0;
    int j = 0;

    GList *list = query6_aux(cat, year);
    GList *aux = list;
    while(aux && j < n_int){
        ORIGIN_PASSENGER_COUNT *opc = (ORIGIN_PASSENGER_COUNT *) aux->data;
        i++;
        batch_print_query6F(opc, fp, i);
        aux = aux->next;
        j++;
    }
    g_list_free_full(list, (GDestroyNotify) free_origin_passenger_count);
}

void query8(catalog *cat, char *query, FILE *fp){

    (void)strsep(&query, " ");
    char *hotelID_agr = strsep(&query, " ");
    char *begin_agr = strsep(&query, " ");
    char *end_agr = strsep(&query, "\n");
    int total = 0;

    Date begin = valid_date(begin_agr);
    Date end = valid_date(end_agr);

    total = query8_aux(cat, hotelID_agr, begin, end);
    batch_print_query8(total, fp);
    free_date(begin);   
    free_date(end);
}

void query8F(catalog *cat, char *query, FILE *fp){
    (void)strsep(&query, " ");
    char *hotelID_agr = strsep(&query, " ");
    char *begin_agr = strsep(&query, " ");
    char *end_agr = strsep(&query, "\n");
    int total = 0;
    int i = 0;

    Date begin = valid_date(begin_agr);
    Date end = valid_date(end_agr);

    total = query8_aux(cat, hotelID_agr, begin, end);
    i++;
    batch_print_query8F(total, fp, i);
    free_date(begin);   
    free_date(end);
}

void query9(catalog *cat, char *query, FILE *fp){
    (void)strsep(&query, " ");
    char *prefix_arg = strsep(&query, "\n");
    if(prefix_arg[0] == '\"'){
        prefix_arg++;
        prefix_arg = strsep(&prefix_arg, "\"");
    }
    GList *list = query9_aux(cat, prefix_arg);
    GList *aux = list;

    while(aux){
        Users *user = (Users *) aux->data;
        batch_print_query9(user, fp);
        aux = aux->next;
    }
    g_list_free(list);
}

void query9F(catalog *cat, char *query, FILE *fp){
    (void)strsep(&query, " ");
    char *prefix_arg = strsep(&query, "\n");
    if(prefix_arg[0] == '\"'){
        prefix_arg++;
        prefix_arg = strsep(&prefix_arg, "\"");
    }
    int i = 0;

    GList *list = query9_aux(cat, prefix_arg);
    GList *aux = list;

    while(aux){
        Users *user = (Users *) aux->data;
        i++;
        batch_print_query9F(user, fp, i);
        aux = aux->next;
        if (aux)
            fprintf(fp, "\n");
    }
    g_list_free(list);
}