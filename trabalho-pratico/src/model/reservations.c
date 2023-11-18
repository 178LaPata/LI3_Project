#include "../../includes/model/reservations.h"

// estrutura das reservations
struct reservations {
    char *id_res;
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
    char *copy_line =strdup(line);

    while((buffer = strsep(&line, ";")) != NULL){
        switch(i++){
            case 0:
                if (strlen(buffer) == 0) val = 0;
                reservations->id_res = strdup(buffer);
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
                reservations->city_tax = verify_maior_igual_que_zero(buffer);
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
                reservations->rating = verify_rating(buffer);
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

    reservations->nights = 0;
    reservations->total_price = 0.0; 
    
    free(copy_line);
    return reservations;
}

// da free a uma reservations e as variaveis
void delete_reservations(void *data){
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
    free(reservations);
}

// insere uma reservations na hashtable
void insert_reservations(CAT_RESERVATIONS *cat_reservations, Reservations *reservations){
    g_hash_table_insert(cat_reservations->reservations_hashtable, reservations->id_res, reservations);
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
        if (r != NULL){
            insert_reservations(cat_reservations, r);
        }

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

GHashTable *get_reservations_hashtable(CAT_RESERVATIONS *cat_reservations){
    return cat_reservations->reservations_hashtable;
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

double calculate_total_price(Reservations *reservations){
    int dias = get_nights(reservations);
    double custo_por_estadia = (double) reservations->price_per_night * (double) dias;
    double imposto = (custo_por_estadia/100) * (double) reservations->city_tax;
    double total = custo_por_estadia + imposto;
    return total;
}

Reservations *get_reservations(CAT_RESERVATIONS *cat_reservations, char *id){
    return g_hash_table_lookup(cat_reservations->reservations_hashtable, id);
}

// esta a dar mal
double calculate_average_rating(CAT_RESERVATIONS *cat_reservations, char *hotel_id){
    int ratingT = 0;
    int count = 0;
    double totalR = 0.0, total = 0.0;
    int r = 0;
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, cat_reservations->reservations_hashtable);
    while(g_hash_table_iter_next(&iter, &key, &value)){
        Reservations *reservations = (Reservations *) value;
        if(strcmp(reservations->hotel_id, hotel_id) == 0){
            r = atoi(reservations->rating);
            ratingT += r;
            count++;
        }

    }
    totalR = (double) ratingT;
    total = totalR / (double) count;
    return total;
}

// funcao que retorna uma lista com as reservas de um hotel
GList* list_reservations_hotelID(CAT_RESERVATIONS *cat_reservations, char* hotel_id){
    GHashTableIter iter;
    gpointer key, value;
  
    GList* list = NULL;

    g_hash_table_iter_init (&iter,cat_reservations->reservations_hashtable);
    while (g_hash_table_iter_next (&iter, &key, &value)){
        Reservations *r = (Reservations *) value;
        if(strcmp(get_hotel_id(r), hotel_id)==0){
            list = g_list_append(list,r);
        }
    }
    return list;
}

// funcao auxiliar para ordenar as reservas por data de início da mais recente para a mais antiga
gint data_mais_recente(gconstpointer a, gconstpointer b){
    Reservations *reservations_a = (Reservations *) a;
    Reservations *reservations_b = (Reservations *) b;
    if (equal_dates(reservations_a->begin_date, reservations_b->begin_date) == 1) {
        return strcmp(reservations_a->id_res, reservations_b->id_res);
    }
    return most_recent_date(reservations_b->begin_date, reservations_a->begin_date);
}

// funcao que ordena as reservas por data de início (da mais recente para a mais antiga)
GList *sort_reservations_data(CAT_RESERVATIONS *cat_reservations, char *hotel_id){
    GList *values = list_reservations_hotelID(cat_reservations, hotel_id);
    if (values == NULL) {
        printf("erro");
    }
    return g_list_sort(values, data_mais_recente);
}

// esta a calcular mal, prov nao e assim que se faz
int calcular_receita_total(CAT_RESERVATIONS *cat_reservations, char *hotel_id, date begin, date end){
    GHashTableIter iter;
    gpointer key, value;
    int totalReceita = 0;
    int total = 0;
    int custo_por_estadia = 0;
    int imposto = 0;
    int nights = 0;
    g_hash_table_iter_init(&iter, cat_reservations->reservations_hashtable);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        Reservations *reservations = (Reservations *) value;
        if(strcmp(hotel_id, reservations->hotel_id) == 0){
            if (between_date(reservations->begin_date, begin, end) == 1) {
                nights = calculate_days(reservations->begin_date, end);
                custo_por_estadia = reservations->price_per_night * nights;
                imposto = (custo_por_estadia/100) * reservations->city_tax;
                total += custo_por_estadia + imposto;
            } else if (between_date(reservations->end_date, begin, end) == 1 ){
                nights = calculate_days(begin, reservations->end_date);
                custo_por_estadia = reservations->price_per_night * nights;
                imposto = (custo_por_estadia/100) * reservations->city_tax;
                total += custo_por_estadia + imposto;
            } else if (between_date(reservations->begin_date, begin, end) == 1 && between_date(reservations->end_date, begin, end) == 1) {
                nights = calculate_days(begin, end);
                custo_por_estadia = reservations->price_per_night * nights;
                imposto = (custo_por_estadia/100) * reservations->city_tax;
                total += custo_por_estadia + imposto;
            }
        }
        totalReceita += total;
    }
    return totalReceita;
}
