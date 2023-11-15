#include "../../includes/model/reservations.h"

// estrutura das reservations
struct reservations {
    char *id;
    char *user_id;
    char *hotel_id;
    char *hotel_name;
    int hotel_stars;
    int city_tax;
    char *adress;
    date begin_date;
    date end_date;
    int price_per_night;
    char *includes_breakfast;
    char *room_details;
    char *rating;
    char *comments;

    int nights;
    double total_price;
};

// estrutura da hashtable das reservations
struct cat_reservations {
    GHashTable *reservations_hashtable;
};

char *get_id_reservations(Reservations *reservations){
    return reservations->id;
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

date get_begin_date(Reservations *reservations){
    return reservations->begin_date;
}

date get_end_date(Reservations *reservations){
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
    return reservations->total_price;
}

void set_id_reservations(Reservations *reservations, char *id){
    reservations->id = strdup(id);
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

void set_begin_date(Reservations *reservations, date begin_date){
    reservations->begin_date = begin_date;
}

void set_end_date(Reservations *reservations, date end_date){
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

void set_total_price(Reservations *reservations, double total_price){
    reservations->total_price = total_price;
}

// cria uma reservations a partir de uma linha do ficheiro e verifica se os dados sao validos
Reservations *create_reservations(char *line){
    Reservations *reservations = malloc(sizeof(Reservations));
    char *buffer;
    int i = 0;
    int val = 1;
    while((buffer = strsep(&line, ";")) != NULL){
        switch(i++){
            case 0:
                if (strlen(buffer) == 0) val = 0;
                reservations->id = strdup(buffer);
                break;
            case 1:
                if (strlen(buffer) == 0) val = 0;
                reservations->user_id = strdup(buffer);
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
                reservations->city_tax = verify_maior_que_zero(buffer);
                if (reservations->city_tax == 0) val = 0;
                break;
            case 6:
                if (strlen(buffer) == 0) val = 0;
                reservations->adress = strdup(buffer);
                break;
            case 7:
                reservations->begin_date = valid_date(buffer);
                if (reservations->begin_date == NULL) val = 0;
                break;
            case 8:
                reservations->end_date = valid_date(buffer);
                if (reservations->end_date == NULL) val = 0;
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
                if(strlen(buffer) == 0) reservations->rating = " ";
                reservations->rating = verify_rating(buffer);
                if(reservations->rating == NULL) val = 0;
                reservations->rating = strdup(buffer);
                break;
            case 13:
                if(strlen(buffer) == 0) reservations->comments = " ";
                reservations->comments = strdup(buffer);
                break;
        }
    }
    
    if(val == 0){
        delete_reservations(reservations);
        return NULL;
    }

    reservations->nights = 0;
    reservations->total_price = 0.0; 
    

    return reservations;
}

// da free a uma reservations e as variaveis
void delete_reservations(void *data){
    Reservations *reservations = (Reservations *) data;
    free(reservations->id);
    free(reservations->user_id);
    free(reservations->hotel_id);
    free(reservations->hotel_name);
    free(reservations->adress);
    free(reservations->includes_breakfast);
    free(reservations->room_details);
    free(reservations->rating);
    free(reservations->comments);
    free(reservations);
}

// insere uma reservations na hashtable
void insert_reservations(CAT_RESERVATIONS *cat_reservations, Reservations *reservations){
    g_hash_table_insert(cat_reservations->reservations_hashtable, reservations->id, reservations);
}

// cria a hashtable das reservations
CAT_RESERVATIONS *create_cat_reservations(char *entry_files){
    
    FILE *fp;
    char open[50];
    strcpy(open, entry_files);
    fp = fopen(open, "r");
    if (!fp) {
        perror("Error opening file");
        return NULL;
    }

    CAT_RESERVATIONS *cat_reservations = malloc(sizeof(CAT_RESERVATIONS));
    cat_reservations->reservations_hashtable = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, delete_reservations);

    char *line = NULL;
    size_t len = 0;

    clock_t start, end;
    double cpu_time_used;

    int first_line = 1; 

    start = clock();
    while (getline(&line, &len, fp) > 0) {
        if (first_line) {
            first_line = 0;
            continue;
        }
        line[strcspn(line, "\n")] = 0;
        Reservations *r = create_reservations(line);
        if (r != NULL) insert_reservations(cat_reservations, r);
    }

    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time to parse reservations.csv: %f\n", cpu_time_used);

    printf("Number of reservations: %d\n", g_hash_table_size(cat_reservations->reservations_hashtable));

    free(line);
    fclose(fp);

    return cat_reservations;
}

// da free a uma hashtable das reservations
void delete_cat_reservations(CAT_RESERVATIONS *cat_reservations){
    g_hash_table_destroy(cat_reservations->reservations_hashtable);
    free(cat_reservations);
}

void update_values_reservations(CAT_RESERVATIONS *cat_reservations){
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, cat_reservations->reservations_hashtable);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        Reservations *reservations = (Reservations *) value;
        set_nights(reservations, calculate_days(reservations->begin_date, reservations->end_date));
        set_total_price(reservations, calculate_total_price(reservations));
    }
}

int calculate_total_reservations(CAT_RESERVATIONS *cat_reservations, char *user){
    int total_reservations = 0;
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, cat_reservations->reservations_hashtable);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        Reservations *reservations = (Reservations *) value;
        if (strcmp(reservations->user_id, user) == 0) total_reservations++;
    }
    return total_reservations;
}

double calculate_total_price(Reservations *reservations){
    int dias = get_nights(reservations);
    double custo_por_estadia = (double) reservations->price_per_night * (double) dias;
    double imposto = (custo_por_estadia/100) * (double) reservations->city_tax;
    double total = custo_por_estadia + imposto;
    return total;
}

double calculate_total_spent(CAT_RESERVATIONS *cat_reservations, char *user){
    double total_gasto = 0.0;
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, cat_reservations->reservations_hashtable);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        Reservations *reservations = (Reservations *) value;
        if (strcmp(reservations->user_id, user) == 0) {
            total_gasto += get_total_price(reservations);
        }
    }
    return total_gasto;
}

Reservations *get_reservations(CAT_RESERVATIONS *cat_reservations, char *id){
    return g_hash_table_lookup(cat_reservations->reservations_hashtable, id);
}

double calculate_average_rating(CAT_RESERVATIONS *cat_reservations, char *hotel_id){
    int rating = 0;
    int count = 0;
    double total = 0.0;
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, cat_reservations->reservations_hashtable);
    while(g_hash_table_iter_next(&iter, &key, &value)){
        Reservations *reservations = (Reservations *) value;
        if(strcmp(reservations->hotel_id, hotel_id) == 0){
            rating += reservations->hotel_stars;
            count++;
        }
    }
    total = (double) rating/(double) count;
    return total;
}

//double query8_aux(CAT_RESERVATIONS *reservations, char *hotel_id, date begin, date end){
//    double total = 0.0;
//    GHashTableIter iter;
//    gpointer key, value;
//    g_hash_table_iter_init(&iter, reservations->reservations_hashtable);
//    while (g_hash_table_iter_next(&iter, &key, &value)) {
//        Reservations *reservations = (Reservations *) value;
//        if (strcmp(reservations->hotel_id, hotel_id) == 0) {
//            int nights = get_nights(reservations);
//            printf("noites: %d\n", nights);
//            if (compare_dates(reservations->begin_date, begin) >= 0 && compare_dates(reservations->end_date, end) <= 0) {
//                total += (double) reservations->price_per_night * (double) nights;
//                printf("total: %.3f/n", total);
//            }
//        }
//    }
//    return total;
//}