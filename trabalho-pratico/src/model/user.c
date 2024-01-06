#include "../../includes/model/user.h"

struct user {
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

char *get_id(const User *user){
    return user->id;
}

char *get_name(const User *user){
    return user->name;
}

char *get_email(const User *user){
    return user->email;
}

char *get_phone_number(const User *user){
    return user->phone_number;
}

Date get_birth_date(const User *user){
    return user->birth_date;
}

char *get_sex(const User *user){
    return user->sex;
}

char *get_passport(const User *user){
    return user->passport;
}

char *get_country_code(const User *user){
    return user->country_code;
}

char *get_adress(const User *user){
    return user->adress;
}

Datetime get_account_creation(const User *user){
    return user->account_creation;
}

enum pay_method get_pay_method(const User *user){
    return user->pay_method;
}

enum account_status get_account_status(const User *user){
    return user->account_status;
}

int get_flights_total(v *user){
    return user->flights_total;
}

int get_reservations_total(const User *user){
    return user->reservations_total;
}

double get_spent_total(const User *user){
    return user->spent_total;
}

void set_id(User *user, char *id){
    user->id = strdup(id);
}

void set_name(User *user, char *name){
    user->name = strdup(name);
}

void set_email(User *user, char *email){
    user->email = strdup(email);
}

void set_phone_number(User *user, char *phone_number){
    user->phone_number = strdup(phone_number);
}

void set_birth_date(User *user, Date birth_date){
    user->birth_date = birth_date;
}

void set_sex(User *user, char *sex){
    user->sex = sex;
}

void set_passport(User *user, char *passport){
    user->passport = strdup(passport);
}

void set_country_code(User *user, char *country_code){
    user->country_code = strdup(country_code);
}

void set_adress(User *user, char *adress){
    user->adress = strdup(adress);
}

void set_account_creation(User *user, Datetime account_creation){
    user->account_creation = account_creation;
}

void set_pay_method(User *user, enum pay_method pay_method){
    user->pay_method = pay_method;
}

void set_account_status(User *user, enum account_status account_status){
    user->account_status = account_status;
}

void set_flights_total(User *user, int flights_total){
    user->flights_total = flights_total;
}

void set_reservations_total(User *user, int reservations_total){
    user->reservations_total = reservations_total;
}

void set_spent_total(User *user, double spent_total){
    user->spent_total = spent_total;
}

User *create_user(char *line){
    User *user = malloc(sizeof(User));
    char *buffer;
    int i = 0;
    int val = 1;
    char *copy_line = strdup(line);

    Date bd = NULL;
    Datetime ac = NULL;
    user->id = NULL;
    user->name = NULL;
    user->email = NULL;
    user->phone_number = NULL;
    user->birth_date = NULL;
    user->sex = NULL;
    user->passport = NULL;
    user->country_code = NULL;
    user->adress = NULL;
    user->account_creation = NULL;
    user->pay_method = noPayMethod;
    user->account_status = NoStatus;
    user->flights_total = 0;
    user->reservations_total = 0;
    user->spent_total = 0.0;


    while((buffer = strsep(&line, ";")) != NULL){
        switch(i++){
            case 0:
                if (strlen(buffer) == 0) val = 0;
                user->id = strdup(buffer);
                break;
            case 1:
                if (strlen(buffer) == 0) val = 0;
                user->name = strdup(buffer);
                break;
            case 2:
                if (strlen(buffer) == 0) val = 0;
                user->email = verify_email(buffer);
                if(user->email == NULL) val = 0;
                break;
            case 3:
                if (strlen(buffer) == 0) val = 0;
                char *ph= verify_phone_number(buffer);
                user->phone_number = ph;
                free(ph);
                break;
            case 4:
                if(strlen(buffer) == 0) val = 0;
                bd = valid_date(buffer);
                user->birth_date = bd; 
                if(user->birth_date == NULL) val = 0;
                break;
            case 5:
                if (strlen(buffer) == 0) val = 0;
                user->sex = strdup(buffer);
                if (tolower(buffer[0]) != 'm' && tolower(buffer[0]) != 'f') val = 0;
                break;
            case 6:
                user->passport = verify_passport(buffer);
                if (user->passport == NULL) val = 0;
                break;
            case 7:
                if (strlen(buffer) != 2 || !isalpha(buffer[0]) || !isalpha(buffer[1])) val = 0; 
                user->country_code = strdup(buffer);
                break;
            case 8:
                if(strlen(buffer) == 0) val = 0;
                user->adress = strdup(buffer);
                break;
            case 9:
                ac = valid_date_time(buffer);
                user->account_creation = ac;  
                if(user->account_creation == NULL) val = 0;
                if(most_recent(user->account_creation, user->birth_date) == 0) val = 0;
                break;
            case 10:
                user->pay_method = verify_payMethod(buffer); 
                if(user->pay_method == noPayMethod) val = 0;
                break;
            case 11:
                user->account_status = verify_accountStatus(buffer);
                if(user->account_status == NoStatus) val = 0;
                break;
        }
    }

    if(val == 0){
        validate_csv_error(copy_line, "user");
        delete_user(user);
        free(copy_line);
        return NULL;
    }

    user->flights_total = 0;
    user->reservations_total = 0;
    user->spent_total = 0.0;

    free(copy_line);
    return user;
}

void delete_user(void *data){
    User *user = (User *) data;
    free(user->id);
    free(user->name);
    free(user->email);
    free_date(user->birth_date);
    free(user->sex);
    free(user->passport);
    free(user->country_code);
    free(user->adress);
    free_datetime(user->account_creation);
    free(user);
}