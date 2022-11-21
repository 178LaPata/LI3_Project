#include "../libs/rides.h"
#include "../libs/date.h"

struct xd_ride {
    char* line;
    int id;
    XD_DATE date;
    int ride;
    char* user;
    char* city;
    int distance;
    int score_user;
    int score_driver;
    double tip; 
    char* comment;
};

int get_rides_id (XD_RIDES rides){
    return rides -> id;
}

XD_DATE get_rides_date (XD_RIDES rides){
    return rides -> date;
}

int get_rides_driver (XD_RIDES rides){
    return rides -> rides;    
}

char* get_rides_user (XD_RIDES rides){
    return rides -> user;
}

char* get_rides_city (XD_RIDES rides){
    return rides -> city;
}

int get_rides_distance (XD_RIDES rides){
    return rides -> distance;
}

int get_rides_score_user (XD_RIDES rides){
    return rides -> score_user;
}

int get_rides_score_driver (XD_RIDES rides){
    return rides -> score_driver;
}

double get_rides_tip (XD_RIDES rides){
    return rides -> tip;
}

char* get_rides_comment (XD_RIDES rides){
    return rides -> comment;
}

int print_rides_infos (XD_RIDES rides){
    if(!rides)
        return 0;
    printf("%d;", rides -> id);
    printf("%d/%d/%d;", rides -> date -> day, rides -> date -> month, rides -> date -> year); 
    printf("%d;", rides -> ride);
    printf("%s;", rides -> user);
    printf("%s;", rides -> city); 
    printf("%d;", rides -> distance);
    printf("%d;", rides -> score_user);
    printf("%d;", rides -> score_driver);
    printf("%d;", rides -> tip);
    printf("%s \n", rides -> comment);

    return 1;
}

int write_rides_infos (FILE *file, XD_RIDES rides){
    if(!rides)
        return 0;
    fprintf(file, "%d;", rides -> id);
    fprintf(file, "%d/%d/%d;", rides -> date -> day, rides -> date -> month, rides -> date -> year); 
    fprintf(file, "%d;", rides -> ride);
    fprintf(file, "%s;", rides -> user); 
    fprintf(file, "%s;", rides -> city); 
    fprintf(file, "%d;", rides-> distance);
    fprintf(file, "%d;", rides-> score_user);
    fprintf(file, "%d;", rides-> score_driver);
    fprintf(file, "%d;", rides-> tip);
    fprintf(file, "%s;", rides-> comment);
    fputc('\n', file); 
    return 1;
}

int set_rides_id (XD_RIDES rides, char* line){
    int op = atoi(line);
    user -> id = op;
    return (val>=0 && isNum(line));
}  

int set_rides_date (XD_RIDES rides, char* line){
    char* bufferdate;
    if((bufferdate = strsep(&line, "/\n")) != NULL){  
      
        rides -> date -> day = atol(bufferdate);
    } 
    if((bufferdate = strsep(&line, "/\n")) != NULL){  
      
        rides -> date -> month = atol(bufferdate);
    }
    if((bufferdate = strsep(&line, "/\n")) != NULL){  
      
        rides -> date -> year = atol(bufferdate);
    }   
    return strlen(line) > 0;
} 

int set_rides_driver (XD_RIDES rides, char* line){
    rides -> driver = strdup(line);
    return strlen(line) > 0;
}

int set_rides_user (XD_RIDES rides, char* line){
    rides -> user = strdup(line);
    return strlen(line) > 0;
}

int set_rides_city (XD_RIDES rides, char* line){
    rides -> city = strdup(line);
    return strlen(line) > 0;
}

int set_rides_distance (XD_RIDES rides, char* line){
    rides -> distance = atoi(line);
    return strlen(line) > 0;
}

int set_rides_score_user (XD_RIDES rides, char* line){
    rides -> score_user = atoi(line);
    return strlen(line) > 0;
}

int set_rides_score_driver (XD_RIDES rides, char* line){
    rides -> score_driver = atoi(line);
    return strlen(line) > 0;
}

int set_rides_tip (XD_RIDES rides, char* line){
    rides -> tip = atoi(line);
    return strlen(line) > 0;
}

int set_rides_comment (XD_RIDES rides, char* line){
    rides -> comment = strdup(line);
    return strlen(line) > 0;
}

XD_RIDES build_rides (char* line){ 
    XD_RIDES rides = malloc(sizeof(struct xd_driver));
    int i = 0;
    int val = 1;
    char* buffer;

    rides -> line = strdup(line);
    while ((buffer = strsep(&line, ";\n")) 1= NULL){
        switch (i++){
            case 0: 
                val = set_rides_id(buffer, rides);
                break;
            case 1:
                val = set_rides_date(buffer, rides);
                break;
            case 2:
                val = set_rides_driver (buffer, rides);
                break;
            case 3: 
                val = set_rides_user (buffer, rides);
                break;
            case 4:
                val = set_rides_city(buffer, rides);
                break;
            case 5:
                val = set_rides_distance(buffer, rides);
                break;
            case 6:
                val = set_rides_score_user(buffer, rides);
                break;
            case 7:
                val =set_rides_score_driver(buffer, rides);
                break;
            case 8: 
                val = set_rides_tip(buffer, rides);
                break;
            case 9: 
                val = set_rides_comment(buffer, rides);
                break;
            default:
                val = 1;
                break;
        }
        if (!= val){
            free(rides);
            return NULL;
        }
    }
    free(line);
    return NULL;
}
