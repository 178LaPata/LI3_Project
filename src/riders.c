#include "../libs/riders.h"

struct xd_riders {
    int id;
    char *date;
    int driver;
    char *user;
    char *city;
    int distance;
    int score_user;
    int score_driver;
    float tip; // ??
    char *comment;
};

struct xd_riders_array {    // Estrutura para o array de utilizadores
    int max_size;           // Tamanho máximo de utilizadores que cabem no array
    int size;               // Número de utilizadores no array
    XD_RIDERS *array;       // Array de utilizadores
};



