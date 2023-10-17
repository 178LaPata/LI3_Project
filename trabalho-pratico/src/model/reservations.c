#include "../../includes/model/reservations.h"
#include "../../includes/model/date.h"

#include <glib.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct reservations {
    int id;
    int user_id;
    int hotel_id;
    char *hotel_name;
    int hotel_stars;
    int city_tax;
    char *adress;
    date begin_date;
    date end_date;
    int price_per_night;
    char *includes_breakfast;
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
    free(reservations->includes_breakfast);
    free(reservations->room_details);
    free(reservations->comments);
    free(reservations);
}

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
                if (strlen(buffer) == 0) val = 0;
                    reservations->user_id = (int) strtol(buffer, (char **) NULL, 10);
                    break;
            case 2:
                if (strlen(buffer) == 0) val = 0;
                    reservations->hotel_id = (int) strtol(buffer, (char **) NULL, 10);
                    break;
            case 3:
                if (strlen(buffer) == 0) val = 0;
                    reservations->hotel_name = strdup(buffer);
                    break;
            case 4:
                //reservations->hotel_stars = verify_hotel_stars(buffer);
                if (reservations->hotel_stars == 0) val = 0;
                break;
            case 5:
                //reservations->city_tax = verify_city_tax(buffer);
                if (reservations->city_tax == 0) val = 0;
                break;
            case 6:
                if (strlen(buffer) == 0) val = 0;
                    reservations->adress = strdup(buffer);
                    break;
            case 7:
                reservations->begin_date = valid_date(buffer);
                if (reservations->begin_date == 0) val = 0;
                break;
            case 8:
                reservations->end_date = valid_date(buffer);
                if (reservations->end_date == 0) val = 0;
                break;
            case 9:
                if (strlen(buffer) == 0){
                    reservations->price_per_night = (int) strtol(buffer, (char **) NULL, 10);
                    break;
                }
            case 10:
                if (strlen(buffer) == 0) val = 0;
                    //reservations->includes_breakfast = verify_includesBreakfast(buffer);
                    break;
            case 11:
                if (strlen(buffer) == 0) val = 0;
                    reservations->room_details = strdup(buffer);
                    break;
            case 12:
                //reservations->rating = verify_rating(buffer);
                if (reservations->rating == 0) val = 0;
                break;
            case 13:
                if (strlen(buffer) == 0) val = 0;
                    reservations->comments = strdup(buffer);
                    break;
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

void insert_reservations(Reservations *reservations, CAT_RESERVATIONS *cat_reservations){
    g_hash_table_insert(cat_reservations->reservations_hashtable, &reservations->id, reservations);
}

CAT_RESERVATIONS *create_cat_reservations(char *entry_files){
    
    FILE *fp;
    char open[50];
    strcpy(open, entry_files);
    fp = fopen(strcat(open, "../../dataset/reservations.csv"), "r");
    if (!fp) {
        perror("Error opening file");
        return NULL;
    }

    CAT_RESERVATIONS *cat_reservations = malloc(sizeof(CAT_RESERVATIONS));
    cat_reservations->reservations_hashtable = g_hash_table_new_full(g_int_hash, g_int_equal, NULL, delete_reservations);

    char *line = NULL;
    size_t len = 0;

    clock_t start, end;
    double cpu_time_used;

    start = clock();
    while (getline(&line, &len, fp) != -1) {
        Reservations *reservations = create_reservations(line);
        if(reservations != NULL) insert_reservations(reservations, cat_reservations);
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