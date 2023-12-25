#pragma once

#include <glib.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Struct that stores the information of a flight
*/
typedef struct flights Flights; 

/**
 * @brief Struct that stores the hashtable of flights ???
*/
typedef struct cat_flights CAT_FLIGHTS;

/**
 * @brief Struct that stores the information of an origin and the number of passengers
*/
typedef struct origin_passenger_count ORIGIN_PASSENGER_COUNT;  

#include "../../includes/model/date.h"

/**
 * @brief Gets the origin of a flight
 * @param opc Struct that stores the information of an origin and the number of passengers
 * @return Returns the origin of a flight
*/
char *get_origin_opc(ORIGIN_PASSENGER_COUNT *opc);

/**
 * @brief Gets the number of passengers of a flight
 * @param opc Struct that stores the information of an origin and the number of passengers
 * @return Returns the number of passengers of a flight
*/
int get_total_passengers_opc(ORIGIN_PASSENGER_COUNT *opc);

/**
 * @brief Gets the id of a flight
 * @param flights Struct that stores the information of a flight
 * @return Returns the id of a flight
*/
char *get_id_flights(Flights *flights);

/**
 * @brief Gets the airline of a flight
 * @param flights Struct that stores the information of a flight
 * @return Returns the airline of a flight
*/
char *get_airline(Flights *flights);

/**
 * @brief Gets the plane model of a flight
 * @param flights Struct that stores the information of a flight
 * @return Returns the plane model of a flight
*/
char *get_plane(Flights *flights);

/**
 * @brief Gets the number of seats of a flight
 * @param flights Struct that stores the information of a flight
 * @return Returns the number of seats of a flight
*/
int get_seats(Flights *flights);

/**
 * @brief Gets the origin of a flight
 * @param flights Struct that stores the information of a flight
 * @return Returns the origin of a flight
*/
char *get_origin(Flights *flights);

/**
 * @brief Gets the destination of a flight
 * @param flights Struct that stores the information of a flight
 * @return Returns the destination of a flight
*/
char *get_destination(Flights *flights);

/**
 * @brief Gets the scheduled departure date of a flight
 * @param flights Struct that stores the information of a flight
 * @return Returns the scheduled departure date of a flight
*/
Datetime get_schedule_departure_date(Flights *flights);

/**
 * @brief Gets the scheduled arrival date of a flight
 * @param flights Struct that stores the information of a flight
 * @return Returns the scheduled arrival date of a flight
*/
Datetime get_schedule_arrival_date(Flights *flights);

/**
 * @brief Gets the real departure date of a flight
 * @param flights Struct that stores the information of a flight
 * @return Returns the real departure date of a flight
*/
Datetime get_real_departure_date(Flights *flights);

/**
 * @brief Gets the real arrival date of a flight
 * @param flights Struct that stores the information of a flight
 * @return Returns the real arrival date of a flight
*/
Datetime get_real_arrival_date(Flights *flights);

/**
 * @brief Gets the pilot of a flight
 * @param flights Struct that stores the information of a flight
 * @return Returns the pilot of a flight
*/
char *get_pilot(Flights *flights);

/**
 * @brief Gets the copilot of a flight
 * @param flights Struct that stores the information of a flight
 * @return Returns the copilot of a flight
*/
char *get_copilot(Flights *flights);

/**
 * @brief Gets the notes of a flight
 * @param flights Struct that stores the information of a flight
 * @return Returns the notes of a flight
*/
char *get_notes(Flights *flights);

/**
 * @brief Gets the number of passengers of a flight
 * @param flights Struct that stores the information of a flight
 * @return Returns the number of passengers of a flight
*/
int get_num_passengers(Flights *flights);

/**
 * @brief Gets the delay of a flight
 * @param flights Struct that stores the information of a flight
 * @return Returns the delay of a flight
*/
int get_delay(Flights *flights);

/**
 * @brief Sets the id of a flight
 * @param flights Struct that stores the information of a flight
 * @param id_flights Id of a flight
*/
void set_id_flights(Flights *flights, char *id_flights);

/**
 * @brief Sets the airline of a flight
 * @param flights Struct that stores the information of a flight
 * @param airline Airline of a flight
*/
void set_airline(Flights *flights, char *airline);

/**
 * @brief Sets the plane model of a flight
 * @param flights Struct that stores the information of a flight
 * @param plane Plane model of a flight
*/
void set_plane(Flights *flights, char *plane);

/**
 * @brief Sets the number of seats of a flight
 * @param flights Struct that stores the information of a flight
 * @param seats Number of seats of a flight
*/
void set_seats(Flights *flights, int seats);

/**
 * @brief Sets the origin of a flight
 * @param flights Struct that stores the information of a flight
 * @param origin Origin of a flight
*/
void set_origin(Flights *flights, char *origin);

/**
 * @brief Sets the destination of a flight
 * @param flights Struct that stores the information of a flight
 * @param destination Destination of a flight
*/
void set_destination(Flights *flights, char *destination);

/**
 * @brief Sets the scheduled departure date of a flight
 * @param flights Struct that stores the information of a flight
 * @param schedule_departure_date Scheduled departure date of a flight
*/
void set_schedule_departure_date(Flights *flights, Datetime schedule_departure_date);

/**
 * @brief Sets the scheduled arrival date of a flight
 * @param flights Struct that stores the information of a flight
 * @param schedule_arrival_date Scheduled arrival date of a flight
*/
void set_schedule_arrival_date(Flights *flights, Datetime schedule_arrival_date);

/**
 * @brief Sets the real departure date of a flight
 * @param flights Struct that stores the information of a flight
 * @param real_departure_date Real departure date of a flight
*/
void set_real_departure_date(Flights *flights, Datetime real_departure_date);

/**
 * @brief Sets the real arrival date of a flight
 * @param flights Struct that stores the information of a flight
 * @param real_arrival_date Real arrival date of a flight
*/
void set_real_arrival_date(Flights *flights, Datetime real_arrival_date);

/**
 * @brief Sets the pilot of a flight
 * @param flights Struct that stores the information of a flight
 * @param pilot Pilot of a flight
*/
void set_pilot(Flights *flights, char *pilot);

/**
 * @brief Sets the copilot of a flight
 * @param flights Struct that stores the information of a flight
 * @param copilot Copilot of a flight
*/
void set_copilot(Flights *flights, char *copilot);

/**
 * @brief Sets the notes of a flight
 * @param flights Struct that stores the information of a flight
 * @param notes Notes of a flight
*/
void set_notes(Flights *flights, char *notes);

/**
 * @brief Sets the number of passengers of a flight
 * @param flights Struct that stores the information of a flight
 * @param num_passengers Number of passengers of a flight
*/
void set_num_passengers(Flights *flights, int num_passengers);

/**
 * @brief Sets the delay of a flight
 * @param flights Struct that stores the information of a flight
 * @param delay Delay of a flight
*/
void set_delay(Flights *flights, int delay);
