#pragma once

#include <glib.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct flight Flight; 
typedef struct origin_passenger_count ORIGIN_PASSENGER_COUNT;  

#include "../../includes/model/date.h"
#include "../../includes/model/valid.h"

char *get_id_flight(const Flight *flight);
char *get_airline(const Flight *flight);
char *get_plane(const Flight *flight);
int get_seats(const Flight *flight);
char *get_origin(const Flight *flight);
char *get_destination(const Flight *flight);
Datetime get_schedule_departure_date(const Flight *flight);
Datetime get_schedule_arrival_date(const Flight *flight);
Datetime get_real_departure_date(const Flight *flight);
Datetime get_real_arrival_date(const Flight *flight);
char *get_pilot(const Flight *flight);
char *get_copilot(const Flight *flight);
char *get_notes(const Flight *flight);
int get_num_passengers(const Flight *flight);
int get_delay(const Flight *flight);
char *get_origin_opc(const ORIGIN_PASSENGER_COUNT *opc);
int get_total_passengers_opc(const ORIGIN_PASSENGER_COUNT *opc);

void set_id_flight(Flight *flight, char *id_flight);
void set_airline(Flight *flight, char *airline);
void set_plane(Flight *flight, char *plane);
void set_seats(Flight *flight, int seats);
void set_origin(Flight *flight, char *origin);
void set_destination(Flight *flight, char *destination);
void set_schedule_departure_date(Flight *flight, Datetime schedule_departure_date);
void set_schedule_arrival_date(Flight *flight, Datetime schedule_arrival_date);
void set_real_departure_date(Flight *flight, Datetime real_departure_date);
void set_real_arrival_date(Flight *flight, Datetime real_arrival_date);
void set_pilot(Flight *flight, char *pilot);
void set_copilot(Flight *flight, char *copilot);
void set_notes(Flight *flight, char *notes);
void set_num_passengers(Flight *flight, int num_passengers);
void set_delay(Flight *flight, int delay);

Flight *create_flight(char *line);
void delete_flight(void *data);