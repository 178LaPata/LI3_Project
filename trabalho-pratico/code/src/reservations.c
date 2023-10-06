#include "reservations.h"
#include "date.h"

#include <glib.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct reservations {
    int id;
    int user_id;
    int hotel_id;
    char *hotel_name
    int hotel_stars;
    int city_tax;
    char *adress;
    Date begin_date;
    Date end_date;
    int price_per_night;
    bool includes_breakfast;
    char *room_details;
    int rating;
    char *comments;
};

struct cat_reservations {
    GHashTable *reservations_hashtable;
};

void delete_reservations(void *data){
    Reservations *reservations = (Reservations *) data;
    free(reservations->hotel_name);
    free(reservations->adress);
    free(reservations->room_details);
    free(reservations->comments);
    free(reservations);
}


// TODO: analisar cases
Reservations *create_reservations(char *line){
    Reservations *reservations = malloc(sizeof(Reservations));
    char *buffer;
    int i = 0;
    int val = 1;
    while((buffer = strsep(&line, ";")) != NULL){
        switch(i++){
            case 0:
                if (strlen(buffer) == 0) val = 0;
                reservations->id = (int) strtol(buffer, (char **) NULL, 10);
                break;
            case 1:
                if (strlen(buffer) == 0){
                    reservations->user_id = (int) strtol(buffer, (char **) NULL, 10);
                    break;
                }
            case 2:
                if (strlen(buffer) == 0){
                    reservations->hotel_id = (int) strtol(buffer, (char **) NULL, 10);
                    break;
                }
            case 3:
                if (strlen(buffer) == 0){
                    reservations->hotel_name = strdup(buffer);
                    break;
                }
            case 4:
                if (strlen(buffer) == 0){
                    reservations->hotel_stars = (int) strtol(buffer, (char **) NULL, 10);
                    break;
                }
            case 5:
                if (strlen(buffer) == 0){
                    reservations->city_tax = (int) strtol(buffer, (char **) NULL, 10);
                    break;
                }
            case 6:
                if (strlen(buffer) == 0){
                    reservations->adress = strdup(buffer);
                    break;
                }
            case 7:
                if (strlen(buffer) == 0){
                    reservations->begin_date = valid_date(buffer);
                    break;
                }
            case 8:
                if (strlen(buffer) == 0){
                    reservations->end_date = valid_date(buffer);
                    break;
                }
            case 9:
                if (strlen(buffer) == 0){
                    reservations->price_per_night = (int) strtol(buffer, (char **) NULL, 10);
                    break;
                }
            case 10:
                if (strlen(buffer) == 0){
                    reservations->includes_breakfast = verify_includesBreakfast(buffer);
                    break;
                }
            case 11:
                if (strlen(buffer) == 0){
                    reservations->room_details = strdup(buffer);
                    break;
                }
            case 12:
                if (strlen(buffer) == 0){
                    reservations->rating = (int) strtol(buffer, (char **) NULL, 10);
                    break;
            case 13:
                if (strlen(buffer) == 0){
                    reservations->comments = strdup(buffer);
                    break;
                }
            default:
                val = 0;
                break;
        }
    }
    if(val == 0){
        delete_reservations(reservations);
        return NULL;
    }
    return reservations;

    }
}
