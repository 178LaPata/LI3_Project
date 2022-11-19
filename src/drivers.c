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
    XD_DATE* account_creation;
    char* account_status;
};

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

XD_DATE* get_drivers_account_creation (XD_DRIVERS driver){
    return driver -> account_creation;
}


