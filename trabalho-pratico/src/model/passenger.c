#include "../../includes/model/passenger.h"

struct passenger {
    char *flight_id;
    char *user_id;
};

Passenger *create_passenger(char *line, CAT_USERS *cat_users, CAT_FLIGHTS *cat_flights){
    Passenger *passenger = malloc(sizeof(Passenger));
    char *buffer;
    int i = 0;
    int val = 1;
    char *copy_line = strdup(line);

    passenger->flight_id = NULL;
    passenger->user_id = NULL;
    
    while((buffer = strsep(&line, ";")) != NULL){
        switch(i++){
            case 0:
                if (strlen(buffer) == 0) val = 0;
                passenger->flight_id = strdup(buffer);
                if(get_flights(cat_flights, passenger->flight_id) == NULL) val = 0;
                break;
            case 1:
                if (strlen(buffer) == 0) val = 0;
                passenger->user_id = strdup(buffer);
                if(get_users(cat_users, passenger->user_id) == NULL) val = 0;
                break;
        }
    }
    if (val == 0){
        validate_csv_error(copy_line, "passenger");
        delete_passenger(passenger);
        free(copy_line);
        return NULL;
    }
    
    free(copy_line);
    return passenger;
}

void delete_passenger(void *data){
    Passenger *passenger = (Passenger *) data;
    free(passenger->flight_id);
    free(passenger->user_id);
    free(passenger);
}