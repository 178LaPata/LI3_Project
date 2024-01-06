#include "../../includes/view/output.h"

void batch_print_query1_user(User *u, FILE *fp){
    int ac = get_account_status(u);
    if(u != NULL){
        if(ac != 2){
            int idade = calculate_age(get_birth_date(u));
            fprintf(fp, "%s;%s;%d;%s;%s;%d;%d;%.3f\n", get_name(u), get_sex(u), idade, 
                    get_country_code(u),get_passport(u),get_flights_total(u),
                    get_reservations_total(u), get_spent_total(u));
        }
    }
}

void batch_print_query1F_user(User *u, FILE *fp, int i){
    int ac = get_account_status(u);
    if(u != NULL){
        if(ac != 2){
            fprintf(fp, "--- %d ---\n", i);
            fprintf(fp, "name: %s\n", get_name(u));
            fprintf(fp, "sex: %s\n", get_sex(u));
            fprintf(fp, "age: %d\n", calculate_age(get_birth_date(u)));
            fprintf(fp, "country_code: %s\n", get_country_code(u));
            fprintf(fp, "passport: %s\n", get_passport(u));
            fprintf(fp, "number_of_flights: %d\n", get_flights_total(u));
            fprintf(fp, "number_of_reservations: %d\n", get_reservations_total(u));
            fprintf(fp, "total_spent: %.3f\n", get_spent_total(u));
        }
    }
}

void batch_print_query1_flights(Flight *fli, FILE *fp){
    if(fli != NULL){
        char *departure = datetime_to_string(get_schedule_departure_date(fli));
        char *arrival = datetime_to_string(get_schedule_arrival_date(fli));
        fprintf(fp, "%s;%s;%s;%s;%s;%s;%d;%d\n", get_airline(fli), get_plane(fli), 
                    get_origin(fli), get_destination(fli), departure, 
                    arrival, get_num_passengers(fli), get_delay(fli));
        free(departure);
        free(arrival);
    }
}

void batch_print_query1F_flights(Flight *fli, FILE *fp, int i){
    if(fli != NULL){
        char *departure = datetime_to_string(get_schedule_departure_date(fli));
        char *arrival = datetime_to_string(get_schedule_arrival_date(fli));
        fprintf(fp, "--- %d ---\n", i);
        fprintf(fp, "airline: %s\n", get_airline(fli));
        fprintf(fp, "plane_model: %s\n", get_plane(fli));
        fprintf(fp, "origin: %s\n", get_origin(fli));
        fprintf(fp, "destination: %s\n", get_destination(fli));
        fprintf(fp, "schedule_departure_date: %s\n", departure);
        fprintf(fp, "schedule_arrival_date: %s\n", arrival);
        fprintf(fp, "passengers: %d\n", get_num_passengers(fli));
        fprintf(fp, "delay: %d\n", get_delay(fli));
        free(departure);
        free(arrival);
    }
}

void batch_print_query1_reservations(Reservation *r, FILE *fp){
    if(r != NULL){
        char *begindate = date_to_string(get_begin_date(r));
        char *enddate = date_to_string(get_end_date(r));
        fprintf(fp, "%s;%s;%d;%s;%s;%s;%d;%.3f\n", get_hotel_id(r), get_hotel_name(r), 
                    get_hotel_stars(r), begindate, enddate, 
                    get_includes_breakfast(r), get_nights(r), get_total_price(r));
        free(begindate);
        free(enddate);
    }
}

void batch_print_query1F_reservations(Reservation *r, FILE *fp, int i){
    if(r != NULL){
        char *begindate = date_to_string(get_begin_date(r));
        char *enddate = date_to_string(get_end_date(r));
        fprintf(fp, "--- %d ---\n", i);
        fprintf(fp, "hotel_id: %s\n", get_hotel_id(r));
        fprintf(fp, "hotel_name: %s\n", get_hotel_name(r));
        fprintf(fp, "hotel_stars: %d\n", get_hotel_stars(r));
        fprintf(fp, "begin_date: %s\n", begindate);
        fprintf(fp, "end_date: %s\n", enddate);
        fprintf(fp, "includes_breakfast: %s\n", get_includes_breakfast(r));
        fprintf(fp, "nights: %d\n", get_nights(r));
        fprintf(fp, "total_price: %.3f\n", get_total_price(r));
        free(begindate);
        free(enddate);
    }
}

void batch_print_query3(double total, FILE *fp){
    fprintf(fp, "%.3f\n", total);
}

void batch_print_query3F(double total, FILE *fp, int i){
    fprintf(fp, "--- %d ---\n", i);
    fprintf(fp, "rating: %.3f\n", total);
}


void batch_print_query4(Reservation *r, FILE *fp){
    if(r != NULL){
        char *begindate = date_to_string(get_begin_date(r));
        char *enddate = date_to_string(get_end_date(r));
        fprintf(fp, "%s;%s;%s;%s;%s;%.3f\n", get_id_reservations(r), begindate, enddate, 
                get_user_id(r), get_rating(r), get_total_price(r));
        free(begindate);
        free(enddate);
    }
}

void batch_print_query4F(Reservation *r, FILE *fp, int i){
    if(r != NULL){
        char *begindate = date_to_string(get_begin_date(r));
        char *enddate = date_to_string(get_end_date(r));
        fprintf(fp, "--- %d ---\n", i);
        fprintf(fp, "id: %s\n", get_id_reservations(r));
        fprintf(fp, "begin_date: %s\n", begindate);
        fprintf(fp, "end_date: %s\n", enddate);
        fprintf(fp, "user_id: %s\n", get_user_id(r));
        fprintf(fp, "rating: %s\n", get_rating(r));
        fprintf(fp, "total_price: %.3f\n", get_total_price(r));
        free(begindate);
        free(enddate);
    }
}

void batch_print_query5(Flight *fli, FILE *fp){
    if(fli != NULL){
        char *begindate = datetime_to_string(get_schedule_departure_date(fli));
        fprintf(fp, "%s;%s;%s;%s;%s\n", get_id_flights(fli), begindate, 
                get_destination(fli), get_airline(fli), get_plane(fli));
        free(begindate);
    }  
}

void batch_print_query5F(Flight *fli, FILE *fp, int i){
    if(fli != NULL){
        char *begindate = datetime_to_string(get_schedule_departure_date(fli));
        fprintf(fp, "--- %d ---\n", i);
        fprintf(fp, "id: %s\n", get_id_flights(fli));
        fprintf(fp, "schedule_departure_date: %s\n", begindate);
        fprintf(fp, "destination: %s\n", get_destination(fli));
        fprintf(fp, "airline: %s\n", get_airline(fli));
        fprintf(fp, "plane_model: %s\n", get_plane(fli));
        free(begindate);
    }  
}

void batch_print_query6(ORIGIN_PASSENGER_COUNT *opc, FILE *fp){
    if(opc != NULL) fprintf(fp, "%s;%d\n", get_origin_opc(opc), get_total_passengers_opc(opc));
}

void batch_print_query6F(ORIGIN_PASSENGER_COUNT *opc, FILE *fp, int i){
    if(opc != NULL){
        fprintf(fp, "--- %d ---\n", i);
        fprintf(fp, "origin: %s\n", get_origin_opc(opc));
        fprintf(fp, "passengers: %d\n", get_total_passengers_opc(opc));
    }
}

void batch_print_query8(int total, FILE *fp){
    fprintf(fp, "%d\n", total);
}

void batch_print_query8F(int total, FILE *fp, int i){
    fprintf(fp, "--- %d ---\n", i);
    fprintf(fp, "revenue: %d\n", total);
}

void batch_print_query9(User *u, FILE *fp){
    int ac = get_account_status(u);
    if(u != NULL){
        if(ac != 2){
            fprintf(fp, "%s;%s\n", get_id(u), get_name(u));
        }
    }
}

void batch_print_query9F(User *u, FILE *fp, int i){
    if(u != NULL){
        fprintf(fp, "--- %d ---\n", i);
        fprintf(fp, "id: %s\n", get_id(u));
        fprintf(fp, "name: %s\n", get_name(u));
    }
}

