#include "../includes/users.h"

// estrutura dos users
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

void valid_user_to_file(Users *u, char *filename){
    char file[BUFFER];
    sprintf(file, "./Entrada/%s_valid.csv", filename);
    FILE *fp_guardar = fopen(file, "a");
    if(fp_guardar != NULL) {
        fprintf(fp_guardar, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%d;%d;%.3f\n",
                u->id, u->name, u->email, u->phone_number,
                date_to_string(u->birth_date), u->sex, u->passport,
                u->country_code, u->adress, datetime_to_string(u->account_creation),
                payMethod_to_string(u->pay_method), accountStatus_to_string(u->account_status),
                u->flights_total, u->reservations_total, u->spent_total);
        fclose(fp_guardar);
    } else {
        printf("Error opening file %s\n", file);
    }
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

    valid_user_to_file(users, "users"); // escreve um user aka escreve tambem as variaveis que acrescentei
    write_valids_to_file(copy_line, "users"); // este nao, escreve a linha que leu do csv
    
    free(copy_line);
    return users;
}














// da free a um user e as variaveis 
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

        Users *u = create_users(line);
        if (u != NULL) insert_users(cat_users, u);
        //delete_users(u);
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

char *display_user(CAT_USERS *user, char *id_user){
    Users *u = g_hash_table_lookup(user->users_hashtable, id_user);
    if(u == NULL || u->account_status == Inactive) return NULL;

    char *name = get_name(u);
    char *sex = get_sex(u);
    char *age = get_age(u);
    char *country_code = get_country_code(u);
    char *passport = get_passport(u);
    int flights_total = get_flights_total(u);
    int reservations_total = get_reservations_total(u);
    double spent_total = get_spent_total(u);

    char *display = malloc(sizeof(snprintf(NULL, 0, "%s;%s;%d;%s;%s;%d;%d;%.3f\n", name, sex, age, country_code, passport, flights_total, reservations_total, spent_total)) + 1);
    snprintf(display, 100, "%s;%s;%d;%s;%s;%d;%d;%.3f\n", name, sex, age, country_code, passport, flights_total, reservations_total, spent_total);
    return display;
}


void add_flights_total(Users *users, int value){
    users->flights_total += value;
}

// funcao que adiciona um valor ao total de reservas de um user
void add_reservations_total(Users *users, int value){
    users->reservations_total += value;
}

void add_spent_total(Users *users, double value){
    users->spent_total += value;
}

// funcao que cria uma lista com os users em que o prefixo passado corresponde ao prefixo do id e a conta nao esta inativa
GList *list_users_prefixo(CAT_USERS *cat_users, char *prefix){
    GHashTableIter iter;
    gpointer key, value;
    GList *list = NULL;

    g_hash_table_iter_init(&iter, cat_users->users_hashtable);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        Users *users = (Users *) value;
        if(strncmp(get_name(users), prefix, strlen(prefix)) == 0 && get_account_status(users) != 2)
            list = g_list_prepend(list, users);
    }
    return list;
}

// funcao que compara dois users por nome e id
gint ordena_id(gconstpointer a, gconstpointer b){
    Users *u1 = (Users *) a;
    Users *u2 = (Users *) b;
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