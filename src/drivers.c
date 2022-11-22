#include "../libs/drivers.h"
#include "../libs/date.h"

#include <glib.h>

struct xd_drivers {
    char* line;
    int id;
    char* name;
    XD_DATE birth_date;
    char gender;
    char* car_class;
    char* license_plate;
    char* city;
    XD_DATE account_creation;
    char* account_status;
};
struct xd_drivers_ht{
    GHashTable* xd_drivers_hash;
};

int get_drivers_id (XD_DRIVERS driver){
    return driver -> id;
}

char* get_drivers_name (XD_DRIVERS driver){
    return driver -> name;
}

XD_DATE get_drivers_birth_date (XD_DRIVERS driver){
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

XD_DATE get_drivers_account_creation (XD_DRIVERS driver){
    return driver -> account_creation;
}

int print_drivers_infos (XD_DRIVERS driver){
    if(!driver)
        return 0;
    printf("%d;", driver -> id);
    printf("%s;", driver -> name);
    printf("%d/%d/%d;", get_date_day(driver -> birth_date), get_date_month(driver -> birth_date), get_date_year(driver -> birth_date)); 
    printf("%c;", driver -> gender);
    printf("%s;", driver -> car_class); 
    printf("%s;", driver -> license_plate);
    printf("%s;", driver -> city);
    printf("%d/%d/%d;", get_date_day(driver -> account_creation), get_date_month(driver -> account_creation), get_date_year(driver -> account_creation)); 
    printf("%s \n", driver -> account_status);
    return 1;
}

int write_drivers_infos (FILE *file, XD_DRIVERS driver){
    if(!driver)
        return 0;
    fprintf(file, "%d;", driver -> id);
    fprintf(file, "%s;", driver -> name);
    fprintf(file, "%d/%d/%d;", get_date_day(driver -> birth_date), get_date_month(driver -> birth_date), get_date_year(driver -> birth_date)); 
    fprintf(file, "%c;", driver -> gender); 
    fprintf(file, "%s;", driver -> car_class); 
    fprintf(file, "%s;", driver-> license_plate);
    fprintf(file, "%s;", driver-> city);
    fprintf(file, "%d/%d/%d;", get_date_day(driver -> account_creation), get_date_month(driver -> account_creation), get_date_year(driver -> account_creation)); 
    fprintf(file, "%s;", driver-> account_status);
    fputc('\n', file); 
    return 1;
}

int set_drivers_id (char* line, XD_DRIVERS driver){
    int ola = atoi(line);  
    driver -> id = ola;
    return (strlen(line) > 0); 
}

int set_drivers_name (XD_DRIVERS driver, char* line){
    driver -> name = strdup(line);
    return strlen(line) > 0;
}

int set_drivers_birth_date (XD_DRIVERS driver, char* line){
    char* bufferdriversbd1;
    char* bufferdriversbd2;
    char* bufferdriversbd3;
    if((bufferdriversbd1 = strsep(&line, "/\n")) == NULL){  
        return -1;
    } 
    if((bufferdriversbd2 = strsep(&line, "/\n")) == NULL){  
        return -1;
    }
    if((bufferdriversbd3 = strsep(&line, "/\n")) == NULL){  
        return -1;
    }   
    set_date(driver -> birth_date, bufferdriversbd1, bufferdriversbd2, bufferdriversbd3);
    return strlen(line) > 0;
}

int set_drivers_gender (XD_DRIVERS driver, char* line){
    driver -> gender = line[0];
    return strlen(line) > 0;
}

int set_drivers_car_class (XD_DRIVERS driver, char* line){
    if(strcmp(line, "Basic"))
        driver -> car_class = "Basic";
    else if(strcmp(line, "Green"))
        driver -> car_class = "Green";
    else if(strcmp(line, "Premium"))
        driver -> car_class = "Premium";
    else return -1;
    return 0;
}
int set_drivers_license_plate (XD_DRIVERS driver, char* line){
    driver -> license_plate = strdup(line);
    return strlen(line) > 0;
}

int set_drivers_city (XD_DRIVERS driver, char* line){
    driver -> city = strdup(line);
    return strlen(line) > 0;
}

int set_drivers_account_creation (XD_DRIVERS driver, char* line){
    char* bufferdriversac1;
    char* bufferadriversc2;
    char* bufferdriversac3;
    if((bufferdriversac1 = strsep(&line, "/\n")) == NULL){  
        return -1;
    } 
    if((bufferadriversc2 = strsep(&line, "/\n")) == NULL){  
        return -1;
    }
    if((bufferdriversac3 = strsep(&line, "/\n")) == NULL){  
        return -1;
    }   
    return strlen(line) > 0;
}

int valid_drivers_account (char* status){
    if ((status == "active") || (status == "inactive")) return 1;
    else return 0;
}

int set_drivers_account_status (XD_DRIVERS driver, char* status){
    if (valid_drivers_account(status)){

      driver -> account_status = status;  

      return 0; // sucesso
    } 
    else return 1; // falhanco
}

XD_DRIVERS build_drivers (char* line){ 
    XD_DRIVERS driver = malloc(sizeof(struct xd_drivers));
    int i = 0;
    int val = 1;
    char* buffer;
    while ((buffer = strsep(&line, ";\n")) != NULL){
        switch (i++){
            case 0: 
                val = set_drivers_id(buffer, driver);
                break;
            case 1:
                val = set_drivers_name(driver, buffer);
                break;
            case 2:
                val = set_drivers_birth_date(driver, buffer);
                break;
            case 3: 
                val = set_drivers_gender(driver, buffer);
                break;
            case 4:
                val = set_drivers_car_class(driver, buffer);
                break;
            case 5:
                val = set_drivers_license_plate(driver, buffer);
                break;
            case 6:
                val = set_drivers_city(driver, buffer);
                break;
            case 7:
                val =set_drivers_account_creation(driver, buffer);
                break;
            case 8: 
                val = set_drivers_account_status(driver, buffer);
                break;
            default:
                val = 1;
                break;
        }
    return driver;
}
}

XD_DRIVERS_HT* create_driverHt(char* file_ent){
    FILE *f;
    char open[50];

    f = fopen("drivers.csv", "r");

    if (!f){
        perror("Error");
        return NULL;
    }

    XD_DRIVERS_HT* new = malloc (sizeof(struct xd_drivers_ht));
    new -> xd_drivers_hash = g_hash_table_new(g_int_hash, g_int_equal);

    char line[1000];
    int buffer_size = 1000;

    while(fgets(line, buffer_size, f)) {
        XD_DRIVERS driver = build_drivers(strdup(line));
        if (driver != NULL) g_hash_table_insert(new -> xd_drivers_hash, driver -> id, driver);
        printf("%s\n", line);
    }
    fclose(f);
    return new;
}

