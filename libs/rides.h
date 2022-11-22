#pragma once
#include "../libs/date.h"

typedef struct xd_rides *XD_RIDES;

typedef struct xd_rides_ht XD_RIDES_HT;

int get_rides_id (XD_RIDES rides);

XD_DATE get_rides_date (XD_RIDES rides);

int get_rides_driver (XD_RIDES rides);

char* get_rides_user (XD_RIDES rides);

char* get_rides_city (XD_RIDES rides);

int get_rides_distance (XD_RIDES rides);

int get_rides_score_user (XD_RIDES rides);

int get_rides_score_driver (XD_RIDES rides);

double get_rides_tip (XD_RIDES rides);

char* get_rides_comment (XD_RIDES rides);

int print_rides_infos (XD_RIDES rides);

int write_rides_infos (FILE *file, XD_RIDES rides);

int set_rides_id (char* line, XD_RIDES rides);

int set_rides_date (XD_RIDES rides, char* line);

int set_rides_driver (XD_RIDES rides, char* line);

int set_rides_user (XD_RIDES rides, char* line);

int set_rides_city (XD_RIDES rides, char* line);

int set_rides_distance (XD_RIDES rides, char* line);

int set_rides_score_user (XD_RIDES rides, char* line);

int set_rides_score_driver (XD_RIDES rides, char* line);

int set_rides_tip (XD_RIDES rides, char* line);

int set_rides_comment (XD_RIDES rides, char* line);

XD_RIDES build_rides (char* line); 

XD_RIDES_HT* create_ridesHt(char* file_ent);




























