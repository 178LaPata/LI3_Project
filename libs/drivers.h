#ifndef DRIVERS
#define DRIVERS

typedef struct xd_drivers *XD_DRIVERS;
 

int get_drivers_id (XD_DRIVERS driver);

int get_drivers_id (XD_DRIVERS driver);

XD_DATE get_drivers_birth_date (XD_DRIVERS driver);

char get_drivers_gender (XD_DRIVERS driver);

char* get_drivers_car_class (XD_DRIVERS driver);

char* get_drivers_license_plate (XD_DRIVERS driver);

char* get_drivers_city (XD_DRIVERS driver);

XD_DATE get_drivers_account_creation (XD_DRIVERS driver);

int print_drivers_infos (XD_DRIVERS driver);

int write_drivers_infos (FILE *file, XD_DRIVERS driver);

int set_drivers_id (char*line , XD_DRIVERS driver);

int set_drivers_name (XD_DRIVERS driver, char* line);

int set_drivers_birth_date (XD_DRIVERS driver, char* line);

int set_drivers_gender (XD_DRIVERS drivers, char* line);

int set_drivers_car_class (XD_DRIVERS driver, char* line);

int set_drivers_license_plate (XD_DRIVERS driver, char* line);

int set_drivers_city (XD_DRIVERS driver, char* line);

int set_drivers_account_creation (XD_DRIVERS driver, char* line);

int valid_drivers_account (char* status);

int set_drivers_account_status (XD_DRIVERS driver, char status);

XD_DRIVERS build_drivers (char* line); 



















