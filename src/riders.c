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
    float tip; 
    char* comment;
};

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

float get_riders_tip (XD_RIDERS rider){
    return rider -> tip;
}

int set_riders_id (XD_RIDERS rider, char* line){
    int op = atoi(line);
    user -> id = op;
    return (val>=0 && isNum(line));
}  

int set_riders_date (XD_RIDERS rider, char* line){

} 

int set_riders_driver (XD_RIDERS rider, char* line){
    int op = strtonum(line, &(rider -> driver));
    return (rider -> driver && op);
}

int set_riders_user (XD_RIDERS rider, char* line){
    int op = 
}