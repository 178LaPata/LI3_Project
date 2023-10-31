typedef struct passengers Passengers;

typedef struct cat_passengers CAT_PASSENGERS;

CAT_PASSENGERS *create_cat_passengers(char *entry_files);
void delete_cat_passengers(CAT_PASSENGERS *cat_passengers);

int calculate_total_flights(CAT_PASSENGERS *cat_passengers, char *id);