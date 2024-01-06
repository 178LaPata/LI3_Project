#include "../../includes/model/users.h"

struct cat_users {
    GHashTable *users_hashtable;
};

void insert_user(CAT_USERS *cat_users, User *user){
    g_hash_table_insert(cat_users->users_hashtable, user->id, user);
}

CAT_USERS *create_cat_users(char *entry_files){

    FILE *fp;
    char open[50];
    strcpy(open, entry_files);
    fp = fopen(open, "r");
    if (!fp) {
        perror("Error opening users.csv");
        return NULL;
    }


    CAT_USERS *cat_users = malloc(sizeof(struct cat_users));
    cat_users->users_hashtable = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, delete_user);

    char *linha = "id;name;email;phone_number;birth_date;sex;passport;country_code;address;account_creation;pay_method;account_status";
    validate_csv_error(linha, "users");

    char *line = NULL;
    size_t len = 0;

    clock_t start, end;
    double cpu_time_used;

    int first_line = 1;

    start = clock();

    while (getline(&line, &len, fp) > 0) {
        if (first_line) {
            first_line = 0;
            continue;
        }
        line[strcspn(line, "\n")] = 0;

        User *u = create_user(line);
        if (u != NULL) insert_user(cat_users, u);
    }

    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Time to parse users.csv: %f\n", cpu_time_used);

    free(line);
    fclose(fp);

    return cat_users;
}
    
// da free a hashtable dos users
void delete_cat_users(CAT_USERS *cat_users){
    g_hash_table_destroy(cat_users->users_hashtable);
    free(cat_users);
}

// retorna um user a partir do id
Users *get_users(CAT_USERS *cat_users, char *id){
    return g_hash_table_lookup(cat_users->users_hashtable, id);
}

void add_flights_total(User *user, int value){
    user->flights_total += value;
}

// funcao que adiciona um valor ao total de reservas de um user
void add_reservations_total(User *user, int value){
    user->reservations_total += value;
}

void add_spent_total(User *user, double value){
    user->spent_total += value;
}

// funcao que cria uma lista com os users em que o prefixo passado corresponde ao prefixo do id e a conta nao esta inativa
GList *list_users_prefixo(CAT_USERS *cat_users, char *prefix){
    GHashTableIter iter;
    gpointer key, value;
    GList *list = NULL;

    g_hash_table_iter_init(&iter, cat_users->users_hashtable);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        User *user = (User *) value;
        if(strncmp(get_name(user), prefix, strlen(prefix)) == 0 && get_account_status(user) != 2)
            list = g_list_prepend(list, user);
    }
    return list;
}

// funcao que compara dois users por nome e id
gint ordena_id(gconstpointer a, gconstpointer b){
    User *u1 = (User *) a;
    User *u2 = (User *) b;
    if(strcoll(get_name(u1), get_name(u2)) == 0)
        return strcoll(get_id(u1), get_id(u2));
    else
        return strcoll(get_name(u1), get_name(u2));
}

// funcao que cria uma lista com os users ordenados por id
GList *sort_users_id(CAT_USERS *cat_users, char *prefix){
    GList *list = list_users_prefixo(cat_users, prefix);
    list = g_list_sort(list, ordena_id);
    return list;
}