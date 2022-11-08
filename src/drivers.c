#include "../libs/drivers.h"

struct xd_drivers {
    int id;
    char *name;
    char *gender;
    char *birth_date;
    char *gender;
    char *car_class;
    char *license_plate;
    char *city;
    char *account_creation;
    char *account_status;
};

struct xd_drivers_array {   // Estrutura para o array de utilizadores
    int max_size;           // Tamanho máximo de utilizadores que cabem no array
    int size;               // Número de utilizadores no array
    XD_DRIVERS *array;      // Array de utilizadores
};

