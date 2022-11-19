#include "../libs/riders.h"
#include "../libs/date.h"

struct xd_riders {
    char* line;
    int id;
    XD_DATE* date;
    int driver;
    char* user;
    char* city;
    int distance;
    int score_user;
    int score_driver;
    double tip; 
    char* comment;
};

struct xd_riders_array {
    int max_size;
    int size;
    XD_RIDERS *array;
};

int get_riders_array_max_size (XD_RIDERS_ARRAY array){
    return array -> max_size;
}
int get_riders_array_size (XD_RIDERS_ARRAY array){
    return array -> size;
}

XD_RIDERS* get_riders_array (XD_RIDERS_ARRAY array){
    return array -> array;
}

XD_RIDERS get_riders_index (XD_RIDERS_ARRAY array, int k){
    if (k >= array -> size) return NULL;
    return array -> array[k];
}

int get_riders_id (XD_RIDERS rider){
    return rider -> id;
}

char* get_riders_date (XD_RIDERS rider){
    return rider -> date;
}

int get_riders_driver (XD_RIDERS rider){
    return rider -> driver;    
}

char* get_riders_user (XD_RIDERS rider){
    return rider -> user;
}

char* get_riders_city (XD_RIDERS rider){
    return rider -> city;
}

int get_riders_distance (XD_RIDERS rider){
    return rider -> distance;
}

int get_riders_score_user (XD_RIDERS rider){
    return rider -> score_user;
}

int get_riders_score_driver (XD_RIDERS rider){
    return rider -> score_driver;
}

double get_riders_tip (XD_RIDERS rider){
    return rider -> tip;
}

int set_riders_id (XD_RIDERS rider, char* line){
    int op = atoi(line);
    user -> id = op;
    return (val>=0 && isNum(line));
}  

int set_riders_date (XD_RIDERS rider, char* line){
    int ola = atoi(line);
    rider -> date = ola;
    return (ola >= 0) && strlen(line) > 0;
} 

int set_riders_driver (XD_RIDERS rider, char* line){
    int op = strtonum(line, &(rider -> driver));
    return (rider -> driver && op);
}

int set_riders_user (XD_RIDERS user, char* line){
    int op = strtonum(line, &(rider -> user));
    return (rider -> user && op);
}

