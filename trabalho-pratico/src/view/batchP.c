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

void batch_print_query1F_user(Users *u, FILE *fp){
    int ac = get_account_status(u);
    if(u != NULL){
        if(ac != 2){
            fprintf(fp, "Name: %s\n", get_name(u));
            fprintf(fp, "Sex: %s\n", get_sex(u));
            fprintf(fp, "Age: %d\n", calculate_age(get_birth_date(u)));
            fprintf(fp, "Country Code: %s\n", get_country_code(u));
            fprintf(fp, "Passport: %s\n", get_passport(u));
            fprintf(fp, "Flights Total: %d\n", get_flights_total(u));
            fprintf(fp, "Reservations Total: %d\n", get_reservations_total(u));
            fprintf(fp, "Spent Total: %.3f\n", get_spent_total(u));
        }
    }
}

void batch_print_query1_flights(Flights *fli, FILE *fp){
    if(fli != NULL)
        fprintf(fp, "%s;%s;%s;%s;%s;%s;%d;%d\n", get_company(fli), get_plane(fli), 
                    get_origin(fli), get_destination(fli), datetime_to_string(get_schedule_departure_date(fli)), 
                    datetime_to_string(get_schedule_arrival_date(fli)), get_num_passengers(fli), get_delay(fli));
}

void batch_print_query1F_flights(Flights *fli, FILE *fp){
    if(fli != NULL){
        fprintf(fp, "Company: %s\n", get_company(fli));
        fprintf(fp, "Plane: %s\n", get_plane(fli));
        fprintf(fp, "Origin: %s\n", get_origin(fli));
        fprintf(fp, "Destination: %s\n", get_destination(fli));
        fprintf(fp, "Schedule Departure Date: %s\n", datetime_to_string(get_schedule_departure_date(fli)));
        fprintf(fp, "Schedule Arrival Date: %s\n", datetime_to_string(get_schedule_arrival_date(fli)));
        fprintf(fp, "Number of Passengers: %d\n", get_num_passengers(fli));
        fprintf(fp, "Delay: %d\n", get_delay(fli));
    }
}

void batch_print_query1_reservations(Reservations *r, FILE *fp){
    if(r != NULL){
        fprintf(fp, "%s;%s;%d;%s;%s;%s;%d;%.3f\n", get_hotel_id(r), get_hotel_name(r), 
                    get_hotel_stars(r), date_to_string(get_begin_date(r)), date_to_string(get_end_date(r)), 
                    get_includes_breakfast(r), get_nights(r), get_total_price(r));
    }
}

void batch_print_query1F_reservations(Reservations *r, FILE *fp){
    if(r != NULL){
        fprintf(fp, "Hotel ID: %s\n", get_hotel_id(r));
        fprintf(fp, "Hotel Name: %s\n", get_hotel_name(r));
        fprintf(fp, "Hotel Stars: %d\n", get_hotel_stars(r));
        fprintf(fp, "Begin Date: %s\n", date_to_string(get_begin_date(r)));
        fprintf(fp, "End Date: %s\n", date_to_string(get_end_date(r)));
        fprintf(fp, "Includes Breakfast: %s\n", get_includes_breakfast(r));
        fprintf(fp, "Nights: %d\n", get_nights(r));
        fprintf(fp, "Total Price: %.3f\n", get_total_price(r));
    }
}

void batch_print_query3(double total, FILE *fp){
    fprintf(fp, "%.3f\n", total);
}

void batch_print_query3F(double total, FILE *fp){
    fprintf(fp, "Average Rating: %.3f\n", total);
}


void batch_print_query4(Reservations *r, FILE *fp){
    if(r != NULL){
        fprintf(fp, "%s;%s;%s;%s;%s;%.3f\n", get_id_reservations(r), date_to_string(get_begin_date(r)), date_to_string(get_end_date(r)), 
                get_user_id(r), get_rating(r), get_total_price(r));
    }
}

void batch_print_query4F(Reservations *r, FILE *fp){
    if(r != NULL){
        fprintf(fp, "ID: %s\n", get_id_reservations(r));
        fprintf(fp, "Begin Date: %s\n", date_to_string(get_begin_date(r)));
        fprintf(fp, "End Date: %s\n", date_to_string(get_end_date(r)));
        fprintf(fp, "User ID: %s\n", get_user_id(r));
        fprintf(fp, "Rating: %s\n", get_rating(r));
        fprintf(fp, "Total Price: %.3f\n", get_total_price(r));
    }
}

void batch_print_query5(Flights *fli, FILE *fp){
    if(fli != NULL){
        fprintf(fp, "%s;%s;%s;%s;%s\n", get_id_flights(fli), datetime_to_string(get_schedule_departure_date(fli)), 
                get_destination(fli), get_company(fli), get_plane(fli));
    }  
}

void batch_print_query5F(Flights *fli, FILE *fp){
    if(fli != NULL){
        fprintf(fp, "ID: %s\n", get_id_flights(fli));
        fprintf(fp, "Schedule Departure Date: %s\n", datetime_to_string(get_schedule_departure_date(fli)));
        fprintf(fp, "Destination: %s\n", get_destination(fli));
        fprintf(fp, "Company: %s\n", get_company(fli));
        fprintf(fp, "Plane: %s\n", get_plane(fli));
    }  
}

void batch_print_query8(int total, FILE *fp){
    fprintf(fp, "%d\n", total);
}