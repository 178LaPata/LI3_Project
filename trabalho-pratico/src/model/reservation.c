#include "../../includes/model/reservation.h"

struct reservation {
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

    int nights;
    double total_price;
};

struct cat_reservation {
    GHashTable *reservation_hashtable;
};

char *get_id_reservation(const Reservation *reservation){
    return reservation->id_res;
}

char *get_user_id(const Reservation *reservation){
    return reservation->user_id;
}

char *get_hotel_id(const Reservation *reservation){
    return reservation->hotel_id;
}

char *get_hotel_name(const Reservation *reservation){
    return reservation->hotel_name;
}

int get_hotel_stars(const Reservation *reservation){
    return reservation->hotel_stars;
}

int get_city_tax(const Reservation *reservation){
    return reservation->city_tax;
}

char *get_adress_reservation(const Reservation *reservation){
    return reservation->adress;
}

Date get_begin_date(const Reservation *reservation){
    return reservation->begin_date;
}

Date get_end_date(const Reservation *reservation){
    return reservation->end_date;
}

int get_price_per_night(const Reservation *reservation){
    return reservation->price_per_night;
}

char *get_includes_breakfast(const Reservation *reservation){
    return reservation->includes_breakfast;
}

char *get_room_details(const Reservation *reservation){
    return reservation->room_details;
}

char *get_rating(const Reservation *reservation){
    return reservation->rating;
}

char *get_comments(const Reservation *reservation){
    return reservation->comments;
}

int get_nights(const Reservation *reservation){
    return reservation->nights;
}

double get_total_price(const Reservation *reservation){
    return reservation->total_price;
}

void set_id_reservation(Reservation *reservation, char *id_res){
    reservation->id_res = strdup(id_res);
}

void set_user_id(Reservation *reservation, char *user_id){
    reservation->user_id = strdup(user_id);
}

void set_hotel_id(Reservation *reservation, char *hotel_id){
    reservation->hotel_id = strdup(hotel_id);
}

void set_hotel_name(Reservation *reservation, char *hotel_name){
    reservation->hotel_name = strdup(hotel_name);
}

void set_hotel_stars(Reservation *reservation, int hotel_stars){
    reservation->hotel_stars = hotel_stars;
}

void set_city_tax(Reservation *reservation, int city_tax){
    reservation->city_tax = city_tax;
}

void set_adress_reservation(Reservation *reservation, char *adress){
    reservation->adress = strdup(adress);
}

void set_begin_date(Reservation *reservation, Date begin_date){
    reservation->begin_date = begin_date;
}

void set_end_date(Reservation *reservation, Date end_date){
    reservation->end_date = end_date;
}

void set_price_per_night(Reservation *reservation, int price_per_night){
    reservation->price_per_night = price_per_night;
}

void set_includes_breakfast(Reservation *reservation, char *includes_breakfast){
    reservation->includes_breakfast = strdup(includes_breakfast);
}

void set_room_details(Reservation *reservation, char *room_details){
    reservation->room_details = strdup(room_details);
}

void set_rating(Reservation *reservation, char *rating){
    reservation->rating = strdup(rating);
}

void set_comments(Reservation *reservation, char *comments){
    reservation->comments = strdup(comments);
}

void set_nights(Reservation *reservation, int nights){
    reservation->nights = nights;
}

void set_total_price(Reservation *reservation, double total_price){
    reservation->total_price = total_price;
}

Reservation *create_reservation(char *line, CAT_USERS *cat_users){
    Reservation *reservation = malloc(sizeof(Reservation));
    char *buffer;
    int i = 0;
    int val = 1;
    char *copy_line =strdup(line);
    Date begin = NULL, end = NULL;
    char *r = NULL;

    reservation->id_res = NULL;
    reservation->user_id = NULL;
    reservation->hotel_id = NULL;
    reservation->hotel_name = NULL;
    reservation->hotel_stars = 0;
    reservation->city_tax = 0;
    reservation->adress = NULL;
    reservation->begin_date = NULL;
    reservation->end_date = NULL;
    reservation->price_per_night = 0;
    reservation->includes_breakfast = NULL;
    reservation->room_details = NULL;
    reservation->rating = NULL;
    reservation->comments = NULL;
    reservation->nights = 0;
    reservation->total_price = 0.0;

    while((buffer = strsep(&line, ";")) != NULL){
        switch(i++){
            case 0:
                if (strlen(buffer) == 0) val = 0;
                reservation->id_res = strdup(buffer);
                break;
            case 1:
                if (strlen(buffer) == 0) val = 0;
                reservation->user_id = strdup(buffer);
                if(get_users(cat_users, reservation->user_id) == NULL) val = 0;
                break;
            case 2:
                if (strlen(buffer) == 0) val = 0;
                reservation->hotel_id = strdup(buffer);
                break;
            case 3:
                if (strlen(buffer) == 0) val = 0;
                reservation->hotel_name = strdup(buffer);
                break;
            case 4:
                reservation->hotel_stars = verify_stars(buffer);
                if (reservation->hotel_stars == 0) val = 0;
                break;
            case 5:
                reservation->city_tax = verify_maior_igual_que_zero(buffer);
                if (reservation->city_tax == 0) val = 0;
                break;
            case 6:
                if (strlen(buffer) == 0) val = 0;
                reservation->adress = strdup(buffer);
                break;
            case 7:
                begin = valid_date(buffer);
                reservation->begin_date = begin;
                if (reservation->begin_date == NULL) val = 0;
                break;
            case 8:
                end = valid_date(buffer);
                reservation->end_date = end;
                if (reservation->end_date == NULL) val = 0;
                if(most_recent_date(reservation->begin_date, reservation->end_date) == 1) val = 0;
                break;
            case 9:
                reservation->price_per_night = verify_maior_que_zero(buffer);
                if (reservation->price_per_night == 0) val = 0;
                break;
            case 10:
                reservation->includes_breakfast = verify_includes_breakfast(buffer);
                if (reservation->includes_breakfast == NULL) val = 0;
                break;
            case 11:
                reservation->room_details = strdup(buffer);
                break;
            case 12:
                r = verify_rating(buffer);
                reservation->rating = r;
                free(r);
                if(reservation->rating == NULL) val = 0;
                reservation->rating = strdup(buffer);
                break;
            case 13:
                if(strlen(buffer) == 0) reservation->comments = "";
                reservation->comments = strdup(buffer);
                break;
        }
    }
    
    if(val == 0){
        validate_csv_error(copy_line, "reservation");
        delete_reservation(reservation);
        free(copy_line);
        return NULL;
    }

    reservation->nights = 0;
    reservation->total_price = 0.0; 
    
    free(copy_line);
    return reservation;
}

void delete_reservation(void *data){
    Reservation *reservation = (Reservation *) data;
    free(reservation->id_res);
    free(reservation->user_id);
    free(reservation->hotel_id);
    free(reservation->hotel_name);
    free(reservation->adress);
    free(reservation->includes_breakfast);
    free(reservation->room_details);
    free(reservation->rating);
    free(reservation->comments);
    free_date(reservation->begin_date);
    free_date(reservation->end_date);
    free(reservation);
}