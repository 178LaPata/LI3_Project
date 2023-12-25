#pragma once

#include <glib.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../../includes/model/flight.h"
#include "../../includes/model/date.h"
#include "../../includes/model/valid.h"
#include "../../includes/model/passengers.h"


/**
 * @brief Creates a new flight
 * @param line Line of the file
 * @return Returns a new flight
*/
Flights *create_flights(char *line);

/**
 * @brief Deletes a flight
 * @param data Flight to be deleted
*/
void delete_flights(void *data);

/**
 * @brief Inserts a flight in the hashtable
 * @param cat_flights Struct that stores the hashtable of flights
 * @param flights Flight to be inserted
*/
void insert_flights(CAT_FLIGHTS *cat_flights, Flights *flights);

/**
 * @brief Creates a new hashtable of flights
 * @param entry_files File path
 * @return Returns a new hashtable of flights
*/
CAT_FLIGHTS *create_cat_flights(char *entry_files);

/**
 * @brief Deletes a hashtable of flights
 * @param cat_flights Struct that stores the hashtable of flights
*/
void delete_cat_flights(CAT_FLIGHTS *cat_flights);

/**
 * @brief Updates the values of a flight
 * @param cat_flights Struct that stores the hashtable of flights
 * @param cat_passengers Struct that stores the hashtable of passengers
*/
void update_values_flights(CAT_FLIGHTS *cat_flights, CAT_PASSENGERS *cat_passengers);

/**
 * @brief Gets a flight
 * @param flights Struct that stores the information of a flight
 * @param id_flights Id of the flight
 * @return Returns a flight
*/
Flights *get_flights (CAT_FLIGHTS *flights, char *id_flights);

/**
 * @brief Creates a list of flights with a given origin
 * @param cat_flights Struct that stores the hashtable of flights
 * @param origin Origin of the flight
 * @param beginD Begin date of the flight
 * @param endD End date of the flight
 * @return Returns a list of flights
*/
GList* list_flights_origin(CAT_FLIGHTS *cat_flights, char *origin, Datetime beginD, Datetime endD);

/**
 * @brief Compares two flights by their schedule departure date
 * @param a Pointer to the first flight
 * @param b Pointer to the second flight
 * @return Returns 1 if the first flight is more recent than the second, 0 if not
*/
gint data_mais_recenteF(gconstpointer a, gconstpointer b);

/**
 * @brief Sorts a list of flights by their schedule departure date
 * @param cat_flights Struct that stores the hashtable of flights
 * @param origin Origin of the flight
 * @param beginD Begin date of the flight
 * @param endD End date of the flight
 * @return Returns a list of flights sorted by their schedule departure date
*/
GList *sort_flights_data(CAT_FLIGHTS *cat_flights, char *origin, Datetime beginD, Datetime endD);

/**
 * @brief Creates a list of flights of a given year
 * @param cat_flights Struct that stores the hashtable of flights
 * @param year Year of the flight
 * @return Returns a list of flights
*/
GList *list_flights_year(CAT_FLIGHTS *cat_flights, char *year);

/**
 * @brief Converts a hashtable to a list
 * @param list List of flights
 * @return Returns a list with the flights of a given origin and the number of passengers
*/
GList *convert_hash_to_list(GList *list);

/**
 * @brief Deletes the data from the struct ??
 * @param opc Struct that stores the origin and the number of passengers
*/
void free_origin_passenger_count(ORIGIN_PASSENGER_COUNT *opc);

/**
 * @brief Compares two flights by their number of passengers
 * @param a Pointer to the first flight
 * @param b Pointer to the second flight
 * @return Returns 1 if the first flight has more passengers than the second, 0 if not
*/
gint origin_with_more_passengers(gconstpointer a, gconstpointer b);

/**
 * @brief Sorts a list of flights by their number of passengers
 * @param cat_flights Struct that stores the hashtable of flights
 * @param year Year of the flight
 * @return Returns a list of flights sorted by their number of passengers
*/
GList *sort_flights_num_passengers(CAT_FLIGHTS *cat_flights, char *year);