#include "../../includes/view/batchP.h"

void batch_print_query1_user(Users *u, FILE *fp){
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

//void batch_print_query1F_user(Users *u, FILE *fp){}

void batch_print_query1_flights(Flights *fli, FILE *fp){
    if(fli != NULL)
        fprintf(fp, "%s;%s;%s;%s;%s;%s;%d;%d\n", get_company(fli), get_plane(fli), 
                    get_origin(fli), get_destination(fli), datetime_to_string(get_schedule_departure_date(fli)), 
                    datetime_to_string(get_schedule_arrival_date(fli)), get_num_passengers(fli), get_delay(fli));
}

void batch_print_query1_reservations(Reservations *r, FILE *fp){
    if(r != NULL){
        fprintf(fp, "%s;%s;%d;%s;%s;%s;%d;%.3f\n", get_hotel_id(r), get_hotel_name(r), 
                    get_hotel_stars(r), date_to_string(get_begin_date(r)), date_to_string(get_end_date(r)), 
                    get_includes_breakfast(r), get_nights(r), get_total_price(r));
    }
}

void batch_print_query3(double total, FILE *fp){
    fprintf(fp, "%.3f\n", total);
}

void batch_print_query4(Reservations *r, FILE *fp){
    if(r != NULL){
        fprintf(fp, "%s;%s;%s;%s;%s;%.3f\n", get_id_reservations(r), date_to_string(get_begin_date(r)), date_to_string(get_end_date(r)), 
                get_user_id(r), get_rating(r), get_total_price(r));
    }
}

void batch_print_query5(Flights *fli, FILE *fp){
    if(fli != NULL){
        fprintf(fp, "%s;%s;%s;%s;%s\n", get_id_flights(fli), datetime_to_string(get_schedule_departure_date(fli)), 
                get_destination(fli), get_company(fli), get_plane(fli));
    }  
}

void batch_print_query8(int total, FILE *fp){
    fprintf(fp, "%d\n", total);
}