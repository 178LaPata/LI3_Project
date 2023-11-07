#pragma once

typedef struct passengers Passengers;

typedef struct cat_passengers CAT_PASSENGERS;

typedef struct list_passengers List_Passengers;

CAT_PASSENGERS *create_cat_passengers(char *entry_files);

List_Passengers *create_passenger_list(Passengers* passengers);

void insert_passenger_list(List_Passengers *list_passengers, Passengers *passengers);

void delete_passenger_list(void *data);

void delete_cat_passengers(CAT_PASSENGERS *cat_passengers);

int calculate_total_flights(CAT_PASSENGERS *cat_passengers, char *id);