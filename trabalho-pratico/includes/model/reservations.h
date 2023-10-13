typedef struct reservations Reservations;

typedef struct cat_reservations CAT_RESERVATIONS;

CAT_RESERVATIONS *create_cat_reservations(char *entry_files);
void delete_cat_reservations(CAT_RESERVATIONS *cat_reservations);
