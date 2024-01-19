#include "../includes/users.h"

struct users {
    char *id;
    char *name;
    char *email;
    char *phone_number;
    Date birth_date;
    char *sex; 
    char *passport;
    char *country_code;
    char *adress;
    Datetime account_creation;
    enum pay_method pay_method;
    enum account_status account_status;

    int flights_total;
    int reservations_total;
    double spent_total;
};
struct cache_users {
    GHashTable *users_cache;
    GQueue *users_queue;
    int capacity;
};

char *get_id(Users *users){
    return users->id;
}

char *get_name(Users *users){
    return users->name;
}

char *get_email(Users *users){
    return users->email;
}

char *get_phone_number(Users *users){
    return users->phone_number;
}

Date get_birth_date(Users *users){
    return users->birth_date;
}

char *get_sex(Users *users){
    return users->sex;
}

char *get_passport(Users *users){
    return users->passport;
}

char *get_country_code(Users *users){
    return users->country_code;
}

char *get_adress(Users *users){
    return users->adress;
}

Datetime get_account_creation(Users *users){
    return users->account_creation;
}

enum pay_method get_pay_method(Users *users){
    return users->pay_method;
}

enum account_status get_account_status(Users *users){
    return users->account_status;
}

int get_flights_total(Users *users){
    return users->flights_total;
}

int get_reservations_total(Users *users){
    return users->reservations_total;
}

double get_spent_total(Users *users){
    return users->spent_total;
}

void set_id(Users *users, char *id){
    users->id = strdup(id);
}

void set_name(Users *users, char *name){
    users->name = strdup(name);
}

void set_email(Users *users, char *email){
    users->email = strdup(email);
}

void set_phone_number(Users *users, char *phone_number){
    users->phone_number = strdup(phone_number);
}

void set_birth_date(Users *users, Date birth_date){
    users->birth_date = birth_date;
}

void set_sex(Users *users, char *sex){
    users->sex = sex;
}

void set_passport(Users *users, char *passport){
    users->passport = strdup(passport);
}

void set_country_code(Users *users, char *country_code){
    users->country_code = strdup(country_code);
}

void set_adress(Users *users, char *adress){
    users->adress = strdup(adress);
}

void set_account_creation(Users *users, Datetime account_creation){
    users->account_creation = account_creation;
}

void set_pay_method(Users *users, enum pay_method pay_method){
    users->pay_method = pay_method;
}

void set_account_status(Users *users, enum account_status account_status){
    users->account_status = account_status;
}

void set_flights_total(Users *users, int flights_total){
    users->flights_total = flights_total;
}

void set_reservations_total(Users *users, int reservations_total){
    users->reservations_total = reservations_total;
}

void set_spent_total(Users *users, double spent_total){
    users->spent_total = spent_total;
}

void delete_users(void *data){
    Users *users = (Users *) data;
    free(users->id);
    free(users->name);
    free(users->email);
    free_date(users->birth_date);
    free(users->sex);
    free(users->passport);
    free(users->country_code);
    free(users->adress);
    free_datetime(users->account_creation);
    free(users);
}

void delete_cache_users(CACHE_USERS *cache_users){
    g_hash_table_destroy(cache_users->users_cache);
    g_queue_free(cache_users->users_queue);
    free(cache_users);
}

CACHE_USERS *create_new_cache_users(int capacity){
    CACHE_USERS *cache_users = malloc(sizeof(struct cache_users));
    cache_users->users_cache = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, delete_users);
    cache_users->users_queue = g_queue_new();
    cache_users->capacity = capacity;
    return cache_users;
}

void insert_cache_users(CACHE_USERS *cache_users, Users *users){
    if(g_hash_table_contains(cache_users->users_cache, users->id)){
        g_queue_remove(cache_users->users_queue, users);
        g_queue_push_head(cache_users->users_queue, users);
    }
    else{
        if(g_queue_get_length(cache_users->users_queue) == cache_users->capacity){
            Users *u = g_queue_pop_tail(cache_users->users_queue);
            g_hash_table_remove(cache_users->users_cache, u->id);
        }
        g_hash_table_insert(cache_users->users_cache, users->id, users);
        g_queue_push_head(cache_users->users_queue, users);
    }
}

Users *cache_users_lookup(CACHE_USERS *cache_users, char *id){
    Users *users = g_hash_table_lookup(cache_users->users_cache, id);
    if(users != NULL){
        g_queue_remove(cache_users->users_queue, users);
        g_queue_push_head(cache_users->users_queue, users);
    }
    return users;
}

Users *create_users(char *line){
    Users *users = malloc(sizeof(Users));
    char *buffer;
    int i = 0;
    int val = 1;
    char *copy_line = strdup(line);

    Date bd = NULL;
    Datetime ac = NULL;
    users->id = NULL;
    users->name = NULL;
    users->email = NULL;
    users->phone_number = NULL;
    users->birth_date = NULL;
    users->sex = NULL;
    users->passport = NULL;
    users->country_code = NULL;
    users->adress = NULL;
    users->account_creation = NULL;
    users->pay_method = noPayMethod;
    users->account_status = NoStatus;
    users->flights_total = 0;
    users->reservations_total = 0;
    users->spent_total = 0.0;

    while((buffer = strsep(&line, ";")) != NULL){
        switch(i++){
            case 0:
                if (strlen(buffer) == 0) val = 0;
                users->id = strdup(buffer);
                break;
            case 1:
                if (strlen(buffer) == 0) val = 0;
                users->name = strdup(buffer);
                break;
            case 2:
                if (strlen(buffer) == 0) val = 0;
                users->email = verify_email(buffer);
                if(users->email == NULL) val = 0;
                break;
            case 3:
                if (strlen(buffer) == 0) val = 0;
                char *ph= verify_phone_number(buffer);
                users->phone_number = ph;
                free(ph);
                break;
            case 4:
                if(strlen(buffer) == 0) val = 0;
                bd = valid_date(buffer);
                users->birth_date = bd; 
                if(users->birth_date == NULL) val = 0;
                break;
            case 5:
                if (strlen(buffer) == 0) val = 0;
                users->sex = strdup(buffer);
                if (tolower(buffer[0]) != 'm' && tolower(buffer[0]) != 'f') val = 0;
                break;
            case 6:
                users->passport = verify_passport(buffer);
                if (users->passport == NULL) val = 0;
                break;
            case 7:
                if (strlen(buffer) != 2 || !isalpha(buffer[0]) || !isalpha(buffer[1])) val = 0; 
                users->country_code = strdup(buffer);
                break;
            case 8:
                if(strlen(buffer) == 0) val = 0;
                users->adress = strdup(buffer);
                break;
            case 9:
                ac = valid_date_time(buffer);
                users->account_creation = ac;  
                if(users->account_creation == NULL) val = 0;
                if(most_recent(users->account_creation, users->birth_date) == 0) val = 0;
                break;
            case 10:
                users->pay_method = verify_payMethod(buffer); 
                if(users->pay_method == noPayMethod) val = 0;
                break;
            case 11:
                users->account_status = verify_accountStatus(buffer);
                if(users->account_status == NoStatus) val = 0;
                break;
        }
    }

    if(val == 0){
        validate_csv_error(copy_line, "users");
        delete_users(users);
        free(copy_line);
        return NULL;
    }

    users->flights_total = 0;
    users->reservations_total = 0;
    users->spent_total = 0.0;

    free(copy_line);
    return users;
}

int create_users_valid_file(char *file){
    FILE *fp = fopen(file, "r");
    if(!fp) return 1;

    char buffer[1000000];
    char *buffer2 = NULL;  
    char *linha = "id;name;email;phone_number;birth_date;sex;passport;country_code;address;account_creation;pay_method;account_status";
    validate_csv_error(linha, "users");

    clock_t start, end;
    double cpu_time_used;
    start = clock();

    FILE *fp2 = fopen("entrada/users_valid.csv", "w");
    if (!fp2) return -1;
    
    while(fgets(buffer, 1000000, fp)){
        buffer2 = strdup(buffer); 
        Users *u = create_users(buffer2);
        if(u != NULL || get_account_status(u) != 2) {
            int i = verify_user_reservation(u->id);
            if(i == 1){
                add_reservations_total(u, 1);
                add_spent_total(u, calculate_total_price_user(u->id));
                add_flights_total(u, verify_passenger(u->id));
            }
            char *buffer3 = user_to_string(u);
            fprintf(fp2, "%s\n", buffer3);
            free(buffer3);
            delete_users(u);
        }
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time to parse users.csv: %f\n", cpu_time_used);
    fclose(fp);
    fclose(fp2);    
    return 0;
}

int create_users_aux_file(){
    FILE *fp2 = fopen("entrada/users_valid.csv", "r");
    if(!fp2) return 1;

    char buffer[1000000];
    char *buffer2 = NULL;
    char *id = NULL;  
    char *name = NULL;
    FILE *fp3 = fopen("entrada/users_name.csv", "w");
    if (!fp3) return -1;

    while(fgets(buffer, 1000000, fp2)){
        buffer2 = strdup(buffer);
        id = strsep(&buffer2, ";");
        name = strsep(&buffer2, ";");
        fprintf(fp3, "%s;%s\n", id, name);
    }
    
    fclose(fp2);
    fclose(fp3);
    sort_users_by_name("entrada/users_name.csv");
    return 0;
}

char *user_to_string(Users *user){
    char *id = get_id(user);
    char *name = get_name(user);
    char *email = get_email(user);
    char *phone_number = get_phone_number(user);
    char *birth_date = date_to_string(get_birth_date(user));
    char *sex = get_sex(user);
    char *passport = get_passport(user);
    char *country_code = get_country_code(user);
    char *adress = get_adress(user);
    char *account_creation = datetime_to_string(get_account_creation(user));
    char *pay_method = payMethod_to_string(get_pay_method(user));
    char *account_status = accountStatus_to_string(get_account_status(user));
    int flights_total = get_flights_total(user);
    int reservations_total = get_reservations_total(user);
    double spent_total = get_spent_total(user);

    char *res = malloc(sizeof(char) * 1000);
    sprintf(res, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%d;%d;%.3f", id, name, email, phone_number, birth_date, sex,
            passport, country_code, adress, account_creation, pay_method, account_status, flights_total, reservations_total, spent_total);
    return res; 
}

void add_flights_total(Users *users, int value){
    users->flights_total += value;
}

void add_reservations_total(Users *users, int value){
    users->reservations_total += value;
}

void add_spent_total(Users *users, double value){
    users->spent_total += value;
}

int compare_users(const void *a, const void *b) {
    Users *u1 = (Users *) a;
    Users *u2 = (Users *) b;
    int namecomp = strcmp(u1->name, u2->name);
    if (namecomp == 0) return strcmp(u1->id, u2->id);
    return namecomp;
}

int sort_users_by_name(char *file) {
    FILE *fp = fopen(file, "r");
    FILE *fp2 = fopen("entrada/users_name_sorted.csv", "w");
    if (!fp || !fp2) return -1;

    char buffer[1000000];
    char *buffer2 = NULL;
    Users *users = NULL;
    size_t n = 0;

    while(fgets(buffer, sizeof(buffer), fp)) {
        buffer2 = strdup(buffer);
        users = malloc(sizeof(Users));
        char *id = strsep(&buffer2, ";");
        char *name = strsep(&buffer2, ";");
        users[n].id = strdup(id);
        users[n].name = strdup(name);
        n++;
    }

    qsort(users, n, sizeof(Users), compare_users);

    for(int i = 0; i < n; i++) {
        fprintf(fp2, "%s;%s\n", users[i].id, users[i].name);
        free(users[i].id);
        free(users[i].name);
    }
    free(users);
    fclose(fp);
    fclose(fp2);
    return 0;
}

// verifica se o user existe no ficheiro dos validos
int verify_user(char *id){
    FILE *fp = fopen("entrada/users_valid.csv", "r");
    if(!fp) return 1;

    char buffer[1000000];
    char *buffer2 = NULL;  
    char *id2 = NULL;
    int val = 0;

    while(fgets(buffer, 1000000, fp)){
        buffer2 = strdup(buffer); 
        id2 = strsep(&buffer2, ";");
        if(strcmp(id, id2) == 0) val = 1;
    }

    fclose(fp);
    return val;
}

Users *search_user(CACHE_USERS *cache_users, char *id){
    Users *users = cache_users_lookup(cache_users, id);
    if(users == NULL){
        FILE *fp = fopen("entrada/users_valid.csv", "r");
        if(!fp) return NULL;

        char buffer[1000000];
        char *buffer2 = NULL;  
        char *id2 = NULL;
        int val = 0;

        while(fgets(buffer, 1000000, fp)){
            buffer2 = strdup(buffer); 
            id2 = strsep(&buffer2, ";");
            if(strcmp(id, id2) == 0) {
                users = create_users(buffer);
                insert_cache_users(cache_users, users);
                val = 1;
            }
        }

        fclose(fp);
        if(val == 0) return NULL;
    }
    return users;
}