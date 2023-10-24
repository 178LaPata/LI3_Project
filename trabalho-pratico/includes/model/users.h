typedef struct users Users;

typedef struct cat_users CAT_USERS;

CAT_USERS *create_cat_users(char *entry_files);
void delete_cat_users(CAT_USERS *cat_users);
void update_users(CAT_USERS *cat_users, char *id, int flights, int reservations, int spent);
char *users_profile(CAT_USERS *cat_users, char *id);