#include "../includes/reservations.h"

struct reservations {
    char *id_res;
    char *user_id;
    char *hotel_id;
    char *hotel_name;
    int hotel_stars;
    int city_tax;
    char *adress;
    Date begin_date;
    Date end_date;
    int price_per_night;
    char *includes_breakfast;
    char *room_details;
    char *rating;
    char *comments;

    int nights; // numero de noites de uma reserva
    double price_res; // preco total de uma reserva
};
struct cache_reservations {
    GHashTable *reservations_cache;
    GQueue *reservations_queue;
    int capacity;
};

char *get_id_reservations(Reservations *reservations){
    return reservations->id_res;
}

char *get_user_id(Reservations *reservations){
    return reservations->user_id;
}

char *get_hotel_id(Reservations *reservations){
    return reservations->hotel_id;
}

char *get_hotel_name(Reservations *reservations){
    return reservations->hotel_name;
}

int get_hotel_stars(Reservations *reservations){
    return reservations->hotel_stars;
}

int get_city_tax(Reservations *reservations){
    return reservations->city_tax;
}

char *get_adress_reservations(Reservations *reservations){
    return reservations->adress;
}

Date get_begin_date(Reservations *reservations){
    return reservations->begin_date;
}

Date get_end_date(Reservations *reservations){
    return reservations->end_date;
}

int get_price_per_night(Reservations *reservations){
    return reservations->price_per_night;
}

char *get_includes_breakfast(Reservations *reservations){
    return reservations->includes_breakfast;
}

char *get_room_details(Reservations *reservations){
    return reservations->room_details;
}

char *get_rating(Reservations *reservations){
    return reservations->rating;
}

char *get_comments(Reservations *reservations){
    return reservations->comments;
}

int get_nights(Reservations *reservations){
    return reservations->nights;
}

double get_total_price(Reservations *reservations){
    return reservations->price_res;
}

void set_id_reservations(Reservations *reservations, char *id_res){
    reservations->id_res = strdup(id_res);
}

void set_user_id(Reservations *reservations, char *user_id){
    reservations->user_id = strdup(user_id);
}

void set_hotel_id(Reservations *reservations, char *hotel_id){
    reservations->hotel_id = strdup(hotel_id);
}

void set_hotel_name(Reservations *reservations, char *hotel_name){
    reservations->hotel_name = strdup(hotel_name);
}

void set_hotel_stars(Reservations *reservations, int hotel_stars){
    reservations->hotel_stars = hotel_stars;
}

void set_city_tax(Reservations *reservations, int city_tax){
    reservations->city_tax = city_tax;
}

void set_adress_reservations(Reservations *reservations, char *adress){
    reservations->adress = strdup(adress);
}

void set_begin_date(Reservations *reservations, Date begin_date){
    reservations->begin_date = begin_date;
}

void set_end_date(Reservations *reservations, Date end_date){
    reservations->end_date = end_date;
}

void set_price_per_night(Reservations *reservations, int price_per_night){
    reservations->price_per_night = price_per_night;
}

void set_includes_breakfast(Reservations *reservations, char *includes_breakfast){
    reservations->includes_breakfast = strdup(includes_breakfast);
}

void set_room_details(Reservations *reservations, char *room_details){
    reservations->room_details = strdup(room_details);
}

void set_rating(Reservations *reservations, char *rating){
    reservations->rating = strdup(rating);
}

void set_comments(Reservations *reservations, char *comments){
    reservations->comments = strdup(comments);
}

void set_nights(Reservations *reservations, int nights){
    reservations->nights = nights;
}

void set_total_price(Reservations *reservations, double price_res){
    reservations->price_res = price_res;
}

void delete_reservations(void *data){
    if (data == NULL)
        return;
    else{
        Reservations *reservations = (Reservations *) data;
        free(reservations->id_res);
        free(reservations->user_id);
        free(reservations->hotel_id);
        free(reservations->hotel_name);
        free(reservations->adress);
        free(reservations->includes_breakfast);
        free(reservations->room_details);
        free(reservations->rating);
        free(reservations->comments);
        free_date(reservations->begin_date);
        free_date(reservations->end_date);
        free(reservations);
    }
}

void delete_cache_reservations(CACHE_RESERVATIONS *cache_reservations){
    g_hash_table_destroy(cache_reservations->reservations_cache);
    g_queue_free(cache_reservations->reservations_queue);
    free(cache_reservations);
}

CACHE_RESERVATIONS *create_new_cache_reservations(int capacity){
    CACHE_RESERVATIONS *cache_reservations = malloc(sizeof(struct cache_reservations));
    cache_reservations->reservations_cache = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, delete_reservations);
    cache_reservations->reservations_queue = g_queue_new();
    cache_reservations->capacity = capacity;
    return cache_reservations;
}

Reservations *insert_cache_reservations(CACHE_RESERVATIONS *cache_reservations, Reservations *reservations){
    if(g_hash_table_contains(cache_reservations->reservations_cache, reservations->id_res)){
        g_queue_remove(cache_reservations->reservations_queue, reservations);
        g_queue_push_head(cache_reservations->reservations_queue, reservations);
        return reservations;
    }
    else{
        if(g_queue_get_length(cache_reservations->reservations_queue) == cache_reservations->capacity){
            Reservations *r = g_queue_pop_tail(cache_reservations->reservations_queue);
            g_hash_table_remove(cache_reservations->reservations_cache, r->id_res);
        }
        set_nights(reservations, calculate_days(reservations->begin_date, reservations->end_date));
        set_total_price(reservations, calculate_total_price(reservations));
        g_hash_table_insert(cache_reservations->reservations_cache, reservations->id_res, reservations);
        g_queue_push_head(cache_reservations->reservations_queue, reservations);
        return reservations;
    }
}

Reservations *cache_reservations_lookup(CACHE_RESERVATIONS *cache_reservations, char *id){
    Reservations *reservations = g_hash_table_lookup(cache_reservations->reservations_cache, id);
    if(reservations != NULL){
        g_queue_remove(cache_reservations->reservations_queue, reservations);
        g_queue_push_head(cache_reservations->reservations_queue, reservations);
    }
    return reservations;
}

Reservations *create_valid_reservations(char *line){
    Reservations *reservations = malloc(sizeof(Reservations));
    char *buffer;
    int i = 0;
    char *copy_line =strdup(line);

    Date begin = NULL, end = NULL;
    char *r = NULL;
    reservations->id_res = NULL;
    reservations->user_id = NULL;
    reservations->hotel_id = NULL;
    reservations->hotel_name = NULL;
    reservations->hotel_stars = 0;
    reservations->city_tax = 0;
    reservations->adress = NULL;
    reservations->begin_date = NULL;
    reservations->end_date = NULL;
    reservations->price_per_night = 0;
    reservations->includes_breakfast = NULL;
    reservations->room_details = NULL;
    reservations->rating = NULL;
    reservations->comments = NULL;
    reservations->nights = 0;
    reservations->price_res = 0.0;

    while((buffer = strsep(&line, ";")) != NULL){
        switch(i++){
            case 0:
                reservations->id_res = strdup(buffer);
                break;
            case 1:
                reservations->user_id = strdup(buffer);
                break;
            case 2:
                reservations->hotel_id = strdup(buffer);
                break;
            case 3:
                reservations->hotel_name = strdup(buffer);
                break;
            case 4:
                reservations->hotel_stars = verify_stars(buffer);
                break;
            case 5:
                reservations->city_tax = verify_maior_igual_que_zero(buffer);
                break;
            case 6:
                reservations->adress = strdup(buffer);
                break;
            case 7:
                begin = valid_date(buffer);
                reservations->begin_date = begin;
                break;
            case 8:
                end = valid_date(buffer);
                reservations->end_date = end;
                break;
            case 9:
                reservations->price_per_night = verify_maior_que_zero(buffer);
                break;
            case 10:
                reservations->includes_breakfast = verify_includes_breakfast(buffer);
                break;
            case 11:
                reservations->room_details = strdup(buffer);
                break;
            case 12:
                r = verify_rating(buffer);
                reservations->rating = r;
                break;
            case 13:
                if(strlen(buffer) == 0) reservations->comments = "";
                reservations->comments = strdup(buffer);
                break;
        }
    }
    free(copy_line);
    return reservations;
}

Reservations *copy_reservations(Reservations *res){
    Reservations *r = malloc(sizeof(Reservations));
    r->id_res = strdup(res->id_res);
    r->user_id = strdup(res->user_id);
    r->hotel_id = strdup(res->hotel_id);
    r->hotel_name = strdup(res->hotel_name);
    r->hotel_stars = res->hotel_stars;
    r->city_tax = res->city_tax;
    r->adress = strdup(res->adress);
    r->begin_date = copy_date(res->begin_date);
    r->end_date = copy_date(res->end_date);
    r->price_per_night = res->price_per_night;
    r->includes_breakfast = strdup(res->includes_breakfast);
    r->room_details = strdup(res->room_details);
    r->rating = strdup(res->rating);
    r->comments = strdup(res->comments);
    r->nights = res->nights;
    r->price_res = res->price_res;
    return r;
}

Reservations *create_reservations(char *line, CACHE_PASSENGERS *cache_passengers, CACHE_RESERVATIONS *cache_reservations, CACHE_USERS *cache_users){
    Reservations *reservations = malloc(sizeof(Reservations));
    char *buffer;
    int i = 0;
    int val = 1;
    char *copy_line =strdup(line);

    Date begin = NULL, end = NULL;
    char *r = NULL;
    reservations->id_res = NULL;
    reservations->user_id = NULL;
    reservations->hotel_id = NULL;
    reservations->hotel_name = NULL;
    reservations->hotel_stars = 0;
    reservations->city_tax = 0;
    reservations->adress = NULL;
    reservations->begin_date = NULL;
    reservations->end_date = NULL;
    reservations->price_per_night = 0;
    reservations->includes_breakfast = NULL;
    reservations->room_details = NULL;
    reservations->rating = NULL;
    reservations->comments = NULL;
    reservations->nights = 0;
    reservations->price_res = 0.0;

    while((buffer = strsep(&line, ";")) != NULL){
        switch(i++){
            case 0:
                if (strlen(buffer) == 0) val = 0;
                reservations->id_res = strdup(buffer);
                break;
            case 1:
                if (strlen(buffer) == 0) val = 0;
                reservations->user_id = strdup(buffer);
                Users* user = search_user(reservations->user_id, cache_passengers, cache_reservations, cache_users);
                if (user == NULL) val = 0;
                delete_users(user);
                break;
            case 2:
                if (strlen(buffer) == 0) val = 0;
                reservations->hotel_id = strdup(buffer);
                break;
            case 3:
                if (strlen(buffer) == 0) val = 0;
                reservations->hotel_name = strdup(buffer);
                break;
            case 4:
                reservations->hotel_stars = verify_stars(buffer);
                if (reservations->hotel_stars == 0) val = 0;
                break;
            case 5:
                reservations->city_tax = verify_maior_igual_que_zero(buffer);
                if (reservations->city_tax == 0) val = 0;
                break;
            case 6:
                if (strlen(buffer) == 0) val = 0;
                reservations->adress = strdup(buffer);
                break;
            case 7:
                begin = valid_date(buffer);
                reservations->begin_date = begin;
                if (reservations->begin_date == NULL) val = 0;
                break;
            case 8:
                end = valid_date(buffer);
                reservations->end_date = end;
                if (reservations->end_date == NULL) val = 0;
                if(most_recent_date(reservations->begin_date, reservations->end_date) == 1) val = 0;
                break;
            case 9:
                reservations->price_per_night = verify_maior_que_zero(buffer);
                if (reservations->price_per_night == 0) val = 0;
                break;
            case 10:
                reservations->includes_breakfast = verify_includes_breakfast(buffer);
                if (reservations->includes_breakfast == NULL) val = 0;
                break;
            case 11:
                reservations->room_details = strdup(buffer);
                break;
            case 12:
                r = verify_rating(buffer);
                reservations->rating = r;
                free(r);
                if(reservations->rating == NULL) val = 0;
                reservations->rating = strdup(buffer);
                break;
            case 13:
                if(strlen(buffer) == 0) reservations->comments = "";
                reservations->comments = strdup(buffer);
                break;
        }
    }
    
    if(val == 0){
        validate_csv_error(copy_line, "reservations");
        delete_reservations(reservations);
        free(copy_line);
        return NULL;
    }

    free(copy_line);
    return reservations;
}


int create_reservations_valid_file(char *file, CACHE_PASSENGERS *cache_passengers, CACHE_RESERVATIONS *cache_reservations, CACHE_USERS *cache_users){
    FILE *fp = fopen(file, "r");
    if(!fp) return 1;

    char buffer[1000000];
    char *buffer2 = NULL;  
    char *linha = "id;user_id;hotel_id;hotel_name;hotel_stars;city_tax;address;begin_date;end_date;price_per_night;includes_breakfast;room_details;rating;comment";
    validate_csv_error(linha, "reservations");

    clock_t start, end;
    double cpu_time_used;
    start = clock();

    
    FILE *fp2 = fopen("entrada/reservations_valid.csv", "w");
    if (!fp2) return -1;
    if(fgets(buffer, sizeof(buffer), fp) == NULL){
        perror("fgets failed");
        return -1;
    }    
    while(fgets(buffer, sizeof(buffer), fp)){
        buffer2 = strdup(buffer); 
        buffer2[strcspn(buffer2, "\n")] = '\0';
        Reservations *r = create_reservations(buffer2, cache_passengers, cache_reservations, cache_users);
        if(r) fprintf(fp2, "%s", buffer);
        free(buffer2);
        delete_reservations(r);
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time to parse reservations.csv: %f\n", cpu_time_used);
    fclose(fp);
    fclose(fp2);
    return 0;
}

double calculate_total_price(Reservations *reservations){
    int dias = get_nights(reservations);
    double custo_por_estadia = (double) reservations->price_per_night * (double) dias;
    double imposto = (custo_por_estadia/100) * (double) reservations->city_tax;
    double total = custo_por_estadia + imposto;
    return total;
}

char *reservation_to_string(Reservations *r){
    char *id_reser = get_id_reservations(r);
    char *user_id = get_user_id(r);
    char *hotel_id = get_hotel_id(r);
    char *hotel_name = get_hotel_name(r);
    int hotel_stars = get_hotel_stars(r);
    int city_tax = get_city_tax(r);
    char *adress = get_adress_reservations(r);
    Date begin_date = get_begin_date(r);
    Date end_date = get_end_date(r);
    int price_per_night = get_price_per_night(r);
    char *includes_breakfast = get_includes_breakfast(r);
    char *room_details = get_room_details(r);
    char *rating = get_rating(r);
    char *comments = get_comments(r);
    int nights = get_nights(r);
    double price_res = get_total_price(r);

    char *res = malloc(sizeof(char) * 1000);
    sprintf(res, "%s;%s;%s;%s;%d;%d;%s;%s;%s;%d;%s;%s;%s;%s;%d;%.3f", id_reser, user_id, hotel_id, hotel_name, 
    hotel_stars, city_tax, adress, date_to_string(begin_date), date_to_string(end_date), price_per_night, 
    includes_breakfast, room_details, rating, comments, nights, price_res);
    return res;
}

Reservations *search_reservation(CACHE_RESERVATIONS *cache_reservations, char *id_res){
    Reservations *reservations = cache_reservations_lookup(cache_reservations, id_res);
    if(reservations == NULL){
        FILE *fp = fopen("entrada/reservations_valid.csv", "r");
        if(!fp) return NULL;

        char buffer[1000000];
        int val = 0;

        while(fgets(buffer, sizeof(buffer), fp)){
            int aux = strchr(buffer, ';') - buffer;
            if(strncmp(buffer, id_res, aux) == 0){
                reservations = create_valid_reservations(buffer);
                reservations = insert_cache_reservations(cache_reservations, reservations);
                val = 1;
            }
        }
        fclose(fp);
        if(val == 0) return NULL;
    }
    return copy_reservations(reservations);
}

// ---------------- funcoes update users ----------------

// funcao que verifica se um user tem reserva e devolve o id da reserva
char *verify_user_has_reservation(char *user_id){
    FILE *fp = fopen("entrada/reservations_valid.csv", "r");
    if(!fp) return NULL;

    char buffer[1000000];
    char *buffer2 = NULL;  
    char *id_res = NULL;
    
    while(fgets(buffer, sizeof(buffer), fp)){
        buffer2 = strdup(buffer); 
        char *token;
        char *reservations[16];
        int i = 0;

        token = strtok(buffer2, ";");
        while (token != NULL) {
            reservations[i++] = token;
            token = strtok(NULL, ";");
        }
        if (strcmp(reservations[1], user_id)) { 
            id_res = strdup(reservations[0]);
            free(buffer2);
            fclose(fp);
            return id_res;
        }
        free(buffer2);
    }
    fclose(fp);
    return NULL;
}

// ---------------- queries ----------------

// query 1
char *display_reservation(char *id_res, CACHE_RESERVATIONS *cache_reservations){
    Reservations *reservations = search_reservation(cache_reservations, id_res);
    if(reservations == NULL) return NULL;
    char *hotel_id = get_hotel_id(reservations);
    char *hotel_name = get_hotel_name(reservations);
    int hotel_stars = get_hotel_stars(reservations);
    char *begin_date = date_to_string(get_begin_date(reservations));
    char *end_date = date_to_string(get_end_date(reservations));
    char *includes_breakfast = get_includes_breakfast(reservations);
    int nights = get_nights(reservations);
    double price_res = get_total_price(reservations);

    char *res = malloc(sizeof(char) * 1000);
    sprintf(res, "%s;%s;%d;%s;%s;%s;%d;%.3f", hotel_id, hotel_name, hotel_stars, begin_date, end_date, includes_breakfast, nights, price_res);
    free(begin_date);
    free(end_date);
    delete_reservations(reservations);
    return res;
}

// query 3
char *calculate_average_rating(char *hotel_id){
    FILE *fp = fopen("entrada/reservations_valid.csv", "r");
    if(!fp) return NULL;

    char buffer[1000000];
    int total = 0, count = 0;

    while(fgets(buffer, sizeof(buffer), fp)){
        char *token;
        char *reservations[16];
        int i = 0;

        token = strtok(buffer, ";");
        while (token != NULL) {
            reservations[i++] = token;
            token = strtok(NULL, ";");
        }
        if (strcmp(reservations[2], hotel_id) == 0) { 
            if (strcmp(reservations[12], "NULL") != 0) {
                total += atoi(reservations[12]);
                count++;
            }
        }
    }
    fclose(fp);

    if (count == 0) return NULL;

    double average = (double) total / (double) count;
    int size = snprintf(NULL, 0, "%.3f", average) + 1;
    char *averageRating = malloc(size);
    snprintf(averageRating, size, "%.3f", average);
    return averageRating;
}

// query 4
GList* list_reservations_hotelID(char* hotel_id){
    FILE *fp = fopen("entrada/reservations_valid.csv", "r");
    if(!fp) return NULL;

    char buffer[1000000];
    GList *list = NULL;

    while(fgets(buffer, sizeof(buffer), fp)){
        char *token;
        char *reservations[16];
        int i = 0;

        token = strtok(buffer, ";");
        while (token != NULL) {
            reservations[i++] = token;
            token = strtok(NULL, ";");
        }
        if (strcmp(reservations[2], hotel_id) == 0) { 
            Reservations *r = create_valid_reservations(buffer);
            list = g_list_prepend(list, r);
        }
    }
    fclose(fp);
    return list;
}

gint data_mais_recente(gconstpointer a, gconstpointer b){
    Reservations *reservations_a = (Reservations *) a;
    Reservations *reservations_b = (Reservations *) b;
    if (equal_dates(reservations_a->begin_date, reservations_b->begin_date) == 1) {
        return strcmp(reservations_a->id_res, reservations_b->id_res);
    }
    return most_recent_date(reservations_b->begin_date, reservations_a->begin_date);
}

GList *sort_reservations_data(char *hotel_id){
    GList *values = list_reservations_hotelID(hotel_id);
    if (values == NULL) {
        printf("erro");
    }
    return g_list_sort(values, data_mais_recente);
}

// query 8
int calculate_total_price_between_dates(Reservations *reservations, Date begin, Date end){
    int nights = 0, total = 0;
    if (between_date(reservations->begin_date, begin, end) == 1 && between_date(reservations->end_date, begin, end) == 1) {
        nights += calculate_days(reservations->begin_date, reservations->end_date);
        total = reservations->price_per_night * nights;
    } else if(between_date(reservations->begin_date, begin, end) == 1){
        nights += calculate_days(reservations->begin_date, end) + 1;
        total = reservations->price_per_night * nights;
    } else if (between_date(reservations->end_date, begin, end) == 1){
        nights += calculate_days(begin, reservations->end_date);
        total = reservations->price_per_night * nights;
    }
    return total;
}

char *calculate_total_revenue(char *hotel_id, Date begin, Date end) {
    FILE *fp = fopen("entrada/reservations_valid.csv", "r"); 
    if (!fp) return NULL;

    char buffer[1000000];
    char *buffer2 = NULL;
    int total = 0;

    while (fgets(buffer, sizeof(buffer), fp)) {
        buffer2 = strdup(buffer); 
        char *token;
        char *reservations[16];
        int i = 0;

        token = strtok(buffer2, ";");
        while (token != NULL) {
            reservations[i++] = token;
            token = strtok(NULL, ";");
        }
        if (strcmp(reservations[2], hotel_id) == 0) { 
            Reservations *r = create_valid_reservations(buffer);
            total += calculate_total_price_between_dates(r, begin, end);
            delete_reservations(r);
        }
        free(buffer2);
    }

    fclose(fp);

    int size = snprintf(NULL, 0, "%d", total) + 1;
    char *totalRevenue = malloc(size);
    snprintf(totalRevenue, size, "%d", total);
    return totalRevenue;
}




