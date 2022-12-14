#include "../libs/rides.h"
#include "../libs/date.h"
#include "../libs/users.h"
#include "../libs/drivers.h"

#include <glib.h>

struct xd_rides {
    char* line;
    int id;
    XD_DATE date;
    int driver;
    char* user;
    char* city;
    int distance;
    int score_user;
    int score_driver;
    double tip; 
    char* comment;
};

struct xd_rides_ht{
    GHashTable* xd_rides_hash;
};

int get_rides_id (XD_RIDES rides){
    return rides -> id;
}

XD_DATE get_rides_date (XD_RIDES rides){
    return rides -> date;
}

int get_rides_driver (XD_RIDES rides){
    return rides -> driver;    
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
/*
// Funçoes query1
 
double get_users_aval_med (XD_RIDES_HT* rides1){
    GHashTableIter iter;
    gpointer key, value;

    int op1;
    
    g_hash_table_iter_init (&iter, XD_USER_HT);
    while (g_hash_table_iter_next (&iter, &key, &value)){
        //if (value = )
        
    }
    
}

int get_users_num_viagens_city (XD_RIDES_HT* rides2, )
    GHashTableIter iter;
    gpointer key, value;
  
    g_hash_table_iter_init (&iter, XD_RIDES_HT);
    while (g_hash_table_iter_next (&iter, &key, &value)){
        XD_RIDES rides = (XD_RIDES) value;
        if (){


        }
}


int get_users_num_viagens_date (XD_RIDES_HT* rides3)
    GHashTableIter iter;
    gpointer key, value;
  
    g_hash_table_iter_init (&iter, XD_RIDES_HT);
    while (g_hash_table_iter_next (&iter, &key, &value)){
        XD_RIDES rides = (XD_RIDES) value;
       
*/

// Função usada para dar print das informações das rides
int print_rides_infos (XD_RIDES rides){
    if(!rides)
        return 0;
    printf("%d;", rides -> id);
    printf("%d/%d/%d;", get_date_day(rides -> date), get_date_month(rides -> date), get_date_year(rides -> date)); 
    printf("%d;", rides -> driver);
    printf("%s;", rides -> user);
    printf("%s;", rides -> city); 
    printf("%d;", rides -> distance);
    printf("%d;", rides -> score_user);
    printf("%d;", rides -> score_driver);
    printf("%f;", rides -> tip);
    printf("%s \n", rides -> comment);

    return 1;
}
// Função usada para dar write das informações das rides
int write_rides_infos (FILE *file, XD_RIDES rides){
    if(!rides)
        return 0;
    fprintf(file, "%d;", rides -> id);
    fprintf(file, "%d/%d/%d;", get_date_day(rides -> date), get_date_month(rides -> date), get_date_year(rides -> date)); 
    fprintf(file, "%d;", rides -> driver);
    fprintf(file, "%s;", rides -> user); 
    fprintf(file, "%s;", rides -> city); 
    fprintf(file, "%d;", rides-> distance);
    fprintf(file, "%d;", rides-> score_user);
    fprintf(file, "%d;", rides-> score_driver);
    fprintf(file, "%f;", rides-> tip);
    fprintf(file, "%s;", rides-> comment);
    fputc('\n', file); 
    return 1;
}

// Funçao utilizada para definir o id das rides
int set_rides_id (char* line, XD_RIDES rides){
    int op = atoi(line);
    rides -> id = op;
    return (strlen(line) > 0); 
}  

// Funçao utilizada para definir a data da ride
int set_rides_date (XD_RIDES rides, char* line){
    char* bufferridesbd1;
    char* bufferridesbd2;
    char* bufferridesbd3;
    if((bufferridesbd1 = strsep(&line, "/\n")) == NULL){  
        return -1;
    } 
    if((bufferridesbd2 = strsep(&line, "/\n")) == NULL){  
        return -1;
    }
    if((bufferridesbd3 = strsep(&line, "/\n")) == NULL){  
        return -1;
    }   
    set_date(rides -> date, bufferridesbd1, bufferridesbd2, bufferridesbd3);
    return strlen(line) > 0;
}

// Funçao utilizada para preencher o driver das rides
int set_rides_driver (XD_RIDES rides, char* line){
    rides -> driver = atoi(line);
    return (strlen(line) > 0);
}

// Funçao utilizada para preencher o user das rides
int set_rides_user (XD_RIDES rides, char* line){
    rides -> user = strdup(line);
    return strlen(line) > 0;
}

// Funçao utilizada para preencher a city das rides
int set_rides_city (XD_RIDES rides, char* line){
    rides -> city = strdup(line);
    return strlen(line) > 0;
}

// Funçao utilizada para preencher a distance das rides
int set_rides_distance (XD_RIDES rides, char* line){
    rides -> distance = atoi(line);
    return strlen(line) > 0;
}

// Funçao utilizada para preencher o score do user das rides
int set_rides_score_user (XD_RIDES rides, char* line){
    rides -> score_user = atoi(line);
    return strlen(line) > 0;
}

// Funçao utilizada para preencher o score do driver das rides
int set_rides_score_driver (XD_RIDES rides, char* line){
    rides -> score_driver = atoi(line);
    return strlen(line) > 0;
}

// Funçao utilizada para preencher a tip das rides
int set_rides_tip (XD_RIDES rides, char* line){
    rides -> tip = atoi(line);
    return strlen(line) > 0;
}

// Funçao utilizada para preencher o comentario das rides
int set_rides_comment (XD_RIDES rides, char* line){
    rides -> comment = strdup(line);
    return strlen(line) > 0;
}

// Funçao utilizada para construir rides
XD_RIDES build_rides (char* line){ 
    XD_RIDES rides = malloc(sizeof(struct xd_rides));
    int i = 0;
    int val = 1;
    char* buffer;

    rides -> line = strdup(line);
    while ((buffer = strsep(&line, ";\n")) != NULL){
        switch (i++){
            case 0: 
                val = set_rides_id(buffer, rides);
                break;
            case 1:
                val = set_rides_date(rides, buffer);
                break;
            case 2:
                val = set_rides_driver (rides, buffer);
                break;
            case 3: 
                val = set_rides_user (rides, buffer);
                break;
            case 4:
                val = set_rides_city(rides, buffer);
                break;
            case 5:
                val = set_rides_distance(rides, buffer);
                break;
            case 6:
                val = set_rides_score_user(rides, buffer);
                break;
            case 7:
                val =set_rides_score_driver(rides, buffer);
                break;
            case 8: 
                val = set_rides_tip(rides, buffer);
                break;
            case 9: 
                val = set_rides_comment(rides, buffer);
                break;
            default:
                val = 1;
                break;
        }
    return rides;
}
}

// Funçao usada para criar a hash table das rides
XD_RIDES_HT* create_ridesHt(char* file_ent){
  FILE *f;
  char open[50];

  f = fopen("rides.csv", "r");

  if (!f){
    perror("Erro");
    return NULL;
  }

  XD_RIDES_HT* new = malloc (sizeof(struct xd_rides_ht));
  new -> xd_rides_hash = g_hash_table_new(g_int_hash, g_int_equal);

  char line[1000];
  int buffer_size = 1000;

  while(fgets(line, buffer_size, f)) {
      XD_RIDES rides = build_rides(strdup(line));
      if (rides != NULL) g_hash_table_insert(new -> xd_rides_hash, rides -> id, rides);
      printf("%s\n", line);
}
  fclose(f);
  return new;
}