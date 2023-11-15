#include "../../includes/model/users.h"

// estrutura dos users
struct users {
    char *id;
    char *name;
    char *email;
    char *phone_number;
    date birth_date;
    char *sex; 
    char *passport;
    char *country_code;
    char *adress;
    datetime account_creation;
    enum pay_method pay_method;
    enum account_status account_status;

    int flights_total;
    int reservations_total;
    double spent_total;
};

// estrutura da hashtable dos users
struct cat_users {
    GHashTable *users_hashtable;
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

date get_birth_date(Users *users){
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

datetime get_account_creation(Users *users){
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

void set_birth_date(Users *users, date birth_date){
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

void set_account_creation(Users *users, datetime account_creation){
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

// cria um user a partir de uma linha do ficheiro e verifica se os dados sao validos
Users *create_users(char *line){
    Users *users = malloc(sizeof(Users));
    char *buffer;
    int i = 0;
    int val = 1;
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
                users->email = verify_email(buffer);
                if (strlen(buffer) == 0) val = 0;
                break;
            case 3:
                if (strlen(buffer) == 0) val = 0;
                users->phone_number = verify_phone_number(buffer);
                break;
            case 4:
                if(strlen(buffer) == 0) val = 0;
                users->birth_date = valid_date(buffer); 
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
                users->account_creation = valid_date_time(buffer);
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
        delete_users(users);
        return NULL;
   }

   users->flights_total = 0;
   users->reservations_total = 0;
   users->spent_total = 0.0;

   return users;
}

// da free a um user e as variaveis 
void delete_users(void *data){
    Users *users = (Users *) data;
    free(users->id);
    free(users->name);
    free(users->email);
    free(users->birth_date);
    free(users->sex);
    free(users->passport);
    free(users->country_code);
    free(users->adress);
    free(users->account_creation);
    free(users);
}

// insere um user na hashtable
void insert_users(CAT_USERS *cat_users, Users *users){
    g_hash_table_insert(cat_users->users_hashtable, users->id, users);
}

// cria e preenche a hashtable dos users
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
    cat_users->users_hashtable = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, delete_users);


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

        Users *u = create_users(line);
        if (u != NULL){
            insert_users(cat_users, u);
        } 
    }

    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Time to parse users.csv: %f\n", cpu_time_used);

    printf("Number of users: %d\n", g_hash_table_size(cat_users->users_hashtable));
    free(line);
    fclose(fp);

    return cat_users;
}
    
// da free a hashtable dos users
void delete_cat_users(CAT_USERS *cat_users){
    g_hash_table_destroy(cat_users->users_hashtable);
    free(cat_users);
}

// da update as variaveis dos users (variaveis que nao estao no ficheiro)
void update_values_users(CAT_USERS *cat_users, CAT_PASSENGERS *cat_passengers, CAT_RESERVATIONS *cat_reservations){
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init (&iter, cat_users->users_hashtable);
    while (g_hash_table_iter_next (&iter, &key, &value)){
        Users *user = (Users *) value;
        set_flights_total(user, calculate_total_flights(cat_passengers, user->id));
        set_reservations_total(user, calculate_total_reservations(cat_reservations, user->id));
        set_spent_total(user, calculate_total_spent(cat_reservations, user->id));
    }
}

// retorna um user a partir do id
Users *get_users(CAT_USERS *cat_users, char *id){
    return g_hash_table_lookup(cat_users->users_hashtable, id);
}
