#include "../../includes/model/reservations.h"

struct cat_reservations {
    GHashTable *reservations_hashtable;
};

// insere uma reservations na hashtable
void insert_reservation(CAT_RESERVATIONS *cat_reservations, Reservation *reservation){
    g_hash_table_insert(cat_reservations->reservations_hashtable, reservation->id_res, reservations);
}

// cria a hashtable das reservations
CAT_RESERVATIONS *create_cat_reservations(char *entry_files, CAT_USERS *cat_users){
    
    FILE *fp;
    char open[50];
    strcpy(open, entry_files);
    fp = fopen(open, "r");
    if (!fp) {
        perror("Error opening file");
        return NULL;
    }

    CAT_RESERVATIONS *cat_reservations = malloc(sizeof(CAT_RESERVATIONS));
    cat_reservations->reservations_hashtable = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, delete_reservation);
    
    char *linha = "id;user_id;hotel_id;hotel_name;hotel_stars;city_tax;address;begin_date;end_date;price_per_night;includes_breakfast;room_details;rating;comment";
    validate_csv_error(linha, "reservations");

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
        Reservation *r = create_reservation(line, cat_users);
        if (r != NULL){
            insert_reservation(cat_reservations, r);
        }

    }

    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time to parse reservations.csv: %f\n", cpu_time_used);

    free(line);
    fclose(fp);

    return cat_reservations;
}

void delete_cat_reservations(CAT_RESERVATIONS *cat_reservations){
    g_hash_table_destroy(cat_reservations->reservations_hashtable);
    free(cat_reservations);
}

GHashTable *get_reservations_hashtable(CAT_RESERVATIONS *cat_reservations){
    return cat_reservations->reservations_hashtable;
}

char *reservations_to_line(Reservation *reservation){
    char *line = malloc(sizeof(char) * 1000);
    sprintf(line, "%s;%s;%s;%s;%d;%d;%s;%s;%s;%d;%s;%s;%s;%s", get_id_reservation(reservation), 
            get_user_id(reservation), get_hotel_id(reservation), get_hotel_name(reservation), 
            get_hotel_stars(reservation), get_city_tax(reservation), get_adress_reservation(reservation), 
            date_to_string(get_begin_date(reservation)), date_to_string(get_end_date(reservation)), 
            get_price_per_night(reservation), get_includes_breakfast(reservation), 
            get_room_details(reservation), get_rating(reservation), get_comments(reservation));
    return line;
}

void update_values_reservations(CAT_RESERVATIONS *cat_reservations){
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, cat_reservations->reservations_hashtable);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        Reservation *reservation = (Reservation *) value;
        set_nights(reservation, calculate_days(reservation->begin_date, reservation->end_date));
        set_total_price(reservation, calculate_total_price(reservation));
    }
}

double calculate_total_price(Reservation *reservation){
    int dias = get_nights(reservation);
    double custo_por_estadia = (double) reservation->price_per_night * (double) dias;
    double imposto = (custo_por_estadia/100) * (double) reservation->city_tax;
    double total = custo_por_estadia + imposto;
    return total;
}

Reservations *get_reservations(CAT_RESERVATIONS *cat_reservations, char *id){
    return g_hash_table_lookup(cat_reservations->reservations_hashtable, id);
}

double calculate_average_rating(CAT_RESERVATIONS *cat_reservations, char *hotel_id){
    int ratingT = 0;
    int count = 0;
    double totalR = 0.0, total = 0.0;
    int r = 0;
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, cat_reservations->reservations_hashtable);
    while(g_hash_table_iter_next(&iter, &key, &value)){
        Reservation *reservation = (Reservation *) value;
        if(strcmp(reservation->hotel_id, hotel_id) == 0){
            r = atoi(reservation->rating);
            ratingT += r;
            count++;
        }

    }
    totalR = (double) ratingT;
    total = totalR / (double) count;
    return total;
}

GList* list_reservations_hotelID(CAT_RESERVATIONS *cat_reservations, char* hotel_id){
    GHashTableIter iter;
    gpointer key, value;
  
    GList* list = NULL;

    g_hash_table_iter_init (&iter,cat_reservations->reservations_hashtable);
    while (g_hash_table_iter_next (&iter, &key, &value)){
        Reservation *r = (Reservation *) value;
        if(strcmp(get_hotel_id(r), hotel_id)==0){
            list = g_list_append(list,r);
        }
    }
    return list;
}

gint data_mais_recente(gconstpointer a, gconstpointer b){
    Reservation *reservation_a = (Reservation *) a;
    Reservation *reservation_b = (Reservation *) b;
    if (equal_dates(reservation_a->begin_date, reservation_b->begin_date) == 1) {
        return strcmp(reservation_a->id_res, reservation_b->id_res);
    }
    return most_recent_date(reservations_b->begin_date, reservations_a->begin_date);
}

GList *sort_reservations_data(CAT_RESERVATIONS *cat_reservations, char *hotel_id){
    GList *values = list_reservations_hotelID(cat_reservations, hotel_id);
    if (values == NULL) {
        printf("erro");
    }
    return g_list_sort(values, data_mais_recente);
}

int calculate_total_price_between_dates(Reservation *reservation, Date begin, Date end){
    int nights = 0, total = 0;
    if (between_date(reservation->begin_date, begin, end) == 1 && between_date(reservation->end_date, begin, end) == 1) {
        nights += calculate_days(reservation->begin_date, reservation->end_date);
        total = reservation->price_per_night * nights;
    } else if(between_date(reservation->begin_date, begin, end) == 1){
        nights += calculate_days(reservation->begin_date, end) + 1;
        total = reservation->price_per_night * nights;
    } else if (between_date(reservation->end_date, begin, end) == 1){
        nights += calculate_days(begin, reservation->end_date);
        total = reservation->price_per_night * nights;
    }
    return total;
}

int calcular_receita_total(CAT_RESERVATIONS *cat_reservations, char *hotel_id, Date begin, Date end){
    GHashTableIter iter;
    gpointer key, value;
    int totalReceita = 0;

    g_hash_table_iter_init(&iter, cat_reservations->reservations_hashtable);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        Reservation *reservation = (Reservation *) value;
        if(strcmp(hotel_id, reservation->hotel_id) == 0){
            int total = calculate_total_price_between_dates(reservation, begin, end);
            totalReceita += total;
        }
    }
    return totalReceita;
}