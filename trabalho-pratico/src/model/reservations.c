#include "../../includes/model/reservations.h"
#include "../../includes/model/date.h"
#include "../../includes/model/valid.h"

#include <glib.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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
};

struct cat_reservations {
    GHashTable *reservations_hashtable;
};

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

Reservations *create_reservations(char *line){
    Reservations *reservations = malloc(sizeof(Reservations));
    char *buffer;
    int i = 0;
    int val = 1;

    if(strstr(line, "id;user_id;hotel_id;hotel_name;hotel_stars;city_tax;address;begin_date;end_date;price_per_night;includes_breakfast;room_details;rating;comment") != NULL) return NULL;

    while((buffer = strsep(&line, ";")) != NULL){
        switch(i++){
            case 0:
                if (strlen(buffer) == 0) val = 0;
                reservations->id = strdup(buffer);
                printf("ola\n");
                break;
            case 1:
                if (strlen(buffer) == 0) val = 0;
                reservations->user_id = strdup(buffer);
                printf("ola2\n");
                break;
            case 2:
                if (strlen(buffer) == 0) val = 0;
                reservations->hotel_id = strdup(buffer);
                printf("ola3\n");
                break;
            case 3:
                if (strlen(buffer) == 0) val = 0;
                reservations->hotel_name = strdup(buffer);
                printf("ola4\n");
                break;
            case 4:
                reservations->hotel_stars = verify_stars(buffer);
                if (reservations->hotel_stars == 0) val = 0;
                printf("ola5\n");
                break;
            case 5:
                reservations->city_tax = verify_maior_que_zero(buffer);
                if (reservations->city_tax == 0) val = 0;
                printf("ola6\n");
                break;
            case 6:
                if (strlen(buffer) <= 0) val = 0;
                reservations->adress = strdup(buffer);
                printf("ola7\n");
                break;
            case 7:
                reservations->begin_date = valid_date(buffer);
                if (reservations->begin_date == NULL) val = 0;
                printf("ola8\n");
                break;
            case 8:
                reservations->end_date = valid_date(buffer);
                if (reservations->end_date == NULL) val = 0;
                printf("ola9\n");
                break;
            case 9:
                reservations->price_per_night = verify_maior_que_zero(buffer);
                if (reservations->price_per_night == 0) val = 0;
                printf("ola10\n");
                break;
            case 10:
                reservations->includes_breakfast = verify_includes_breakfast(buffer);
                if (reservations->includes_breakfast == NULL) val = 0;
                printf("ola11\n");
                break;
            case 11:
                reservations->room_details = strdup(buffer);
                printf("ola12\n");
                break;
            case 12:
                if(strlen(buffer) == 0) reservations->rating = "no rating";
                reservations->rating = verify_rating(buffer);
                if(reservations->rating == NULL) val = 0;
                reservations->rating = strdup(buffer);
                printf("ola13\n");
                break;
            case 13:
                reservations->comments = strdup(buffer);
                printf("ola14\n");
                break;
        }
    }
    printf("deu bem\n");
    if(val == 0){
        delete_reservations(reservations);
        return NULL;
    }
    return reservations;
}

void insert_reservations(CAT_RESERVATIONS *cat_reservations, Reservations *reservations){
    g_hash_table_insert(cat_reservations->reservations_hashtable, reservations->id, reservations);
}

CAT_RESERVATIONS *create_cat_reservations(char *entry_files){
    
    FILE *fp;
    char open[50];
    strcpy(open, entry_files);
    fp = fopen(open, "r");
    if (!fp) {
        perror("Error opening file");
        return NULL;
    }
    printf("File opened\n");
    CAT_RESERVATIONS *cat_reservations = malloc(sizeof(CAT_RESERVATIONS));
    cat_reservations->reservations_hashtable = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, delete_reservations);

    char *line = NULL;
    size_t len = 0;

    clock_t start, end;
    double cpu_time_used;

    start = clock();
    printf("Start clock\n");
    while (getline(&line, &len, fp) > 0) {
        line[strcspn(line, "\n")] = 0;
        //printf("line %s\n", line);
        Reservations *r = create_reservations(line);
        //if (r != NULL) printf("Reservations id %s\n", r->id);
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

void delete_cat_reservations(CAT_RESERVATIONS *cat_reservations){
    g_hash_table_destroy(cat_reservations->reservations_hashtable);
    free(cat_reservations);
}