#include "../libs/drivers.h"
#include "../libs/date.h"

struct xd_drivers {
    char* line;
    int id;
    char* name;
    XD_DATE account_creation;
    char gender;
    char* car_class;
    char* license_plate;
    char* city;
    XD_DATE account_creation;
    char* account_status;
};

int get_drivers_id (XD_DRIVERS driver){
    return driver -> id;
}

char* get_drivers_name (XD_DRIVERS driver){
    return driver -> name;
}

XD_DATE get_drivers_birth_date (XD_DRIVERS driver){
    return driver -> account_creation;
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
    printf("%d/%d/%d;", driver -> account_creation -> day, driver -> account_creation -> month, driver -> account_creation -> year); 
    printf("%s;", driver -> gender);
    printf("%s;", driver -> car_class); 
    printf("%s;", driver -> license_plate);
    printf("%s;", driver -> city);
    printf("%d/%d/%d;", driver -> account_creation -> day, driver -> account_creation -> month, driver -> account_creation -> year); 
    printf("%s \n", driver -> account_status);
    return 1;
}

int write_drivers_infos (FILE *file, XD_DRIVERS driver){
    if(!driver)
        return 0;
    fprintf(file, "%d;", driver -> id);
    fprintf(file, "%s;", driver -> name);
    fprintf(file, "%d/%d/%d;", driver -> account_creation -> day, driver -> account_creation -> month, driver -> account_creation -> year); 
    fprintf(file, "%s;", driver -> gender); 
    fprintf(file, "%s;", driver -> car_class); 
    fprintf(file, "%s;", driver-> license_plate);
    fprintf(file, "%s;", driver-> city);
    fprintf(file, "%d/%d/%d;", driver -> account_creation -> day, driver -> account_creation -> month, driver -> account_creation -> year); 
    fprintf(file, "%s;", driver-> account_status);
    fputc('\n', file); 
    return 1;
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
    char* bufferbd;
    if((bufferbd = strsep(&line, "/\n")) != NULL){  
      
        driver -> birth_date -> day = atol(bufferbd);
    } 
    if((bufferbd = strsep(&line, "/\n")) != NULL){  
      
        driver -> birth_date -> month = atol(bufferbd);
    }
    if((bufferbd = strsep(&line, "/\n")) != NULL){  
      
        driver -> birth_date -> year = atol(bufferbd);
    }   
    return strlen(line) > 0;
}

int set_drivers_gender (XD_DRIVERS drivers, char* line){
    driver -> gender = strdup(line);
    return strlen(line) > 0;
}

int set_drivers_car_class (XD_DRIVERS driver, char* line){
    if(strcmp(line, "Basic"))
        driver -> car_class = "Basic";
    else if(strcmp(line, "Green"))
        driver -> car_class = "Green";
    else if(strcmp(line, "Premium"))
        driver -> car_class = "Premium";
    else return
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
    char* bufferac;
    if((bufferac = strsep(&line, "/\n")) != NULL){  
      
        driver -> account_creation -> day = atol(bufferac);
    } 
    if((bufferac = strsep(&line, "/\n")) != NULL){  
      
        driver -> account_creation -> month = atol(bufferac);
    }
    if((bufferac = strsep(&line, "/\n")) != NULL){  
      
        driver -> account_creation -> year = atol(bufferac);
    }   
    return strlen(line) > 0;
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
