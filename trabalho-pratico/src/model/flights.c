#include "../../includes/model/flights.h"
#include "../../includes/model/date.h"

#include <glib.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct flights {
    int id;
    char *airline;
    char *plane_model;
    int total_seats;
    char *origin;
    char *destination;
    datetime schedule_departure_date;  
    datetime schedule_arrival_date;  
    datetime real_departure_date;  
    datetime real_arrival_date;  
    char *pilot;
    char *copilot;
    char *notes;
};

struct cat_flights {
    GHashTable *flights_hashtable;
};

void delete_flights(void *data){
    Flights *flights = (Flights *) data;
    free(flights->airline);
    free(flights->plane_model);
    free(flights->origin);
    free(flights->destination);
    free(flights->pilot);
    free(flights->copilot);
    free(flights->notes);
    free(flights);
}

Flights *create_flights(char *line){
    Flights *flights = malloc(sizeof(Flights));
    char *buffer;
    int i = 0;
    int val = 1;
    while((buffer = strsep(&line, ";")) != NULL){
        switch(i++){
            case 0:
                if (strlen(buffer) == 0) val = 0;
                flights->id = (int) strtol(buffer, (char **) NULL, 10);
                break;
            case 1:
                if (strlen(buffer) == 0) val = 0;
                flights->airline = strdup(buffer);
                break;
            case 2:
                if (strlen(buffer) == 0) val = 0;
                flights->plane_model = strdup(buffer);
                break; 
            case 3: 
                if (strlen(buffer) == 0) val = 0;
                flights->total_seats = atoi(buffer);
                break;
            case 4:
                if (strlen(buffer) == 0) val = 0;
                flights->origin = strdup(buffer);
                break;
            case 5:
                if (strlen(buffer) == 0) val = 0;
                flights->destination = strdup(buffer);
                break;
            case 6:
                if(strlen(buffer) == 0) val = 0;
                flights->schedule_departure_date = valid_date_time(buffer);
                if (flights->schedule_departure_date == NULL) val = 0;
                break;
            case 7:
                if(strlen(buffer) == 0) val = 0;
                flights->schedule_arrival_date = valid_date_time(buffer);
                if (flights->schedule_arrival_date == NULL) val = 0;
                break;
            case 8:
                if(strlen(buffer) == 0) val = 0;
                flights->real_departure_date = valid_date_time(buffer);
                if (flights->real_departure_date == NULL) val = 0;
                break;
            case 9:
                if(strlen(buffer) == 0) val = 0;
                flights->real_arrival_date = valid_date_time(buffer);
                if (flights->real_arrival_date == NULL) val = 0;
                break;
            case 10:
                if (strlen(buffer) == 0) val = 0;
                flights->pilot = strdup(buffer);
                break;
            case 11:
                if (strlen(buffer) == 0) val = 0;
                flights->copilot = strdup(buffer);
                break;
            case 12:
                flights->notes = strdup(buffer);
                break;
        } 
    }
    if(val == 0){
        delete_flights(flights);
        return NULL;
    }
    return flights;
}

void insert_flights(CAT_FLIGHTS *cat_flights, Flights *flights){
    g_hash_table_insert(cat_flights->flights_hashtable, &flights->id, flights);
}

CAT_FLIGHTS *create_cat_flights(char *entry_files){

    FILE *fp;
    char open[50];
    strcpy(open, entry_files);
    fp = fopen(open, "r");
    if (!fp) {
        perror("Error opening flights.csv");
        return NULL;
    }    

    CAT_FLIGHTS *cat_flights = malloc(sizeof(CAT_FLIGHTS));
    cat_flights->flights_hashtable = g_hash_table_new_full(g_int_hash, g_int_equal, NULL, delete_flights);

    char *line = NULL;
    size_t len = 0;
    
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    while (getline(&line, &len, fp) > 0){
        line[strcspn(line, "\n")] = 0;
        Flights *flights = create_flights(line);
        if(flights != NULL) insert_flights(cat_flights, flights);
    }
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time to parse flights.csv: %f\n", cpu_time_used);

    printf("Number of flights: %d\n", g_hash_table_size(cat_flights->flights_hashtable));

    free(line);
    fclose(fp);

    return cat_flights;
}

void delete_cat_flights(CAT_FLIGHTS *cat_flights){
    g_hash_table_destroy(cat_flights->flights_hashtable);
    free(cat_flights);
}