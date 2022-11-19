#include "../libs/drivers.h"
#include "../libs/date.h"

struct xd_drivers {
    char* line;
    int id;
    char* name;
    XD_DATE* birth_date;
    char gender;
    char* car_class;
    char* license_plate;
    char* city;
    struct tm account_creation;
    char* account_status;
};

struct xd_drivers_array {
    int max_size;
    int size;
    XD_DRIVERS *array;
};

int get_drivers_array_max_size (XD_DRIVERS_ARRAY array){
    return array -> max_size;
}
int get_drivers_array_size (XD_DRIVERS_ARRAY array){
    return array -> size;
}

XD_DRIVERS* get_drivers_array (XD_DRIVERS_ARRAY array){
    return array -> array;
}

XD_DRIVERS get_drivers_index (XD_DRIVERS_ARRAY array, int k){
    if (k >= array -> size) return NULL;
    return array -> array[k];
}

int get_drivers_id (XD_DRIVERS driver){
    return driver -> id;
}

char* get_drivers_name (XD_DRIVERS driver){
    return driver -> name;
}

XD_DATE* get_drivers_birth_date (XD_DRIVERS driver){
    return driver -> birth_date;
}

char get_drivers_gender (XD_DRIVERS driver){
    return driver -> gender;
}

char* get_drivers_car_class (XD_DRIVERS driver){
    return driver -> car_class;
}

char* get_drivers_license_plate (XD_DRIVERS driver){
    return driver -> license_plate;
}

char* get_drivers_city (XD_DRIVERS driver){
    return driver -> city;
}

struct tm get_drivers_account_creation (XD_DRIVERS driver){
    return driver -> account_creation;
}

int set_drivers_id (char*line , XD_DRIVERS driver){
    int ola = atoi(line);  
    driver -> id = ola;
    return (ola >= 0 && isNum(line)); 
}

int set_drivers_name (XD_DRIVERS driver, char* line){
    driver -> name = strdup(line);
    return strlen(line) > 0;
}

int set_drivers_birth_date (XD_DRIVERS driver, char* line){
    int ola = atoi(line);
    driver -> birth_date = ola;
    return (ola >= 0) && strlen(line) > 0;
}

int valid_drivers_gender (char sexo){
    if ((sexo == 'F') || (sexo == 'M')) return 1;
    else return 0;
}

int set_drivers_gender (XD_DRIVERS driver, char sexo){
    if (valid_drivers_gender(sexo)) driver -> gender = sexo;
}

int set_drivers_car_class (XD_DRIVERS driver, char* line){
    driver -> car_class = strdu(line);
    return strlen(line) > 0;
}

int set_drivers_license_plate (XD_DRIVERS driver, char* line){
    driver -> license_plate = strdu(line);
    return strlen(line) > 0;
}

int set_drivers_city (XD_DRIVERS driver, char* line){
    driver -> city = strdu(line);
    return strlen(line) > 0;
}

int set_drivers_account_creation (XD_DRIVERS driver, char* line){
    if (strlen(line)<19) return 0;    

    sscanf(line, "%d-%d-%d %d:%d:%d", &driver->account_creation.tm_year, &driver->account_creation.tm_mon, &driver->account_creation.tm_mday, &driver->account_creation.tm_hour, &driver->account_creation.tm_min, &driver->account_creation.tm_sec);
    driver->account_creation.tm_year -= 1900;
    driver->account_creation.tm_mon -= 1;
    driver->account_creation.tm_isdst = 1;
    driver->account_creation.tm_wday = 3;
    driver->account_creation.tm_yday = (driver->account_creation.tm_mon * 30) + driver->account_creation.tm_mday;

    return (line[4]!='/') && (is_valid_date(driver->account_creation));
}

int valid_drivers_account (char* status){
    if ((status == "active") || (sexo == "inactive")) return 1;
    else return 0;
}

int set_drivers_account_status (XD_DRIVERS driver, char status){
    if (valid_drivers_account(status)) driver -> account_status = status;
}

XD_DRIVERS build_drivers (char* line){ 
    XD_DRIVERS driver = malloc(sizeof(struct xd_driver));
    int i = 0;
    int val = 1;
    char* buffer;

    driver -> line = strdup(line);
    while ((buffer = strsep(&line, ";\n")) 1= NULL){
        switch (i++){
            case 0: 
                val = set_drivers_id(buffer, driver);
                break;
            case 1:
                val = set_drivers_name(buffer, driver);
                break;
            case 2:
                val = set_drivers_birth_date(buffer, driver);
                break;
            case 3: 
                val = set_drivers_gender(buffer, driver);
                break;
            case 4:
                val = set_drivers_car_class(buffer, driver);
                break;
            case 5:
                val = set_drivers_license_plate(buffer, driver);
                break;
            case 6:
                val = set_drivers_city(buffer, driver);
                break;
            case 7:
                val =set_drivers_account_creation(buffer, driver);
                break;
            case 8: 
                val = set_drivers_account_status(buffer, driver);
                break;
            default:
                val = 1;
                break;
        }
        if (!= val){
            free(driver);
            return NULL;
        }
    }
    free(line);
    return NULL;
}
