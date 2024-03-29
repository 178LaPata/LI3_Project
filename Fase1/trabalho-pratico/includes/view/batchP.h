#pragma once

#include "../../includes/model/catalog.h"
#include "../../includes/model/users.h"
#include "../../includes/model/flights.h"
#include "../../includes/model/reservations.h"
#include "../../includes/model/passengers.h"
#include "../../includes/model/date.h"

void batch_print_query1_user(Users *u, FILE *fp);
void batch_print_query1F_user(Users *u, FILE *fp, int i);
void batch_print_query1_flights(Flights *fli, FILE *fp);
void batch_print_query1F_flights(Flights *fli, FILE *fp, int i);
void batch_print_query1_reservations(Reservations *r, FILE *fp);
void batch_print_query1F_reservations(Reservations *r, FILE *fp, int i);
void batch_print_query3(double total, FILE *fp);
void batch_print_query3F(double total, FILE *fp, int i);
void batch_print_query4(Reservations *r, FILE *fp);
void batch_print_query4F(Reservations *r, FILE *fp, int i);
void batch_print_query5(Flights *fli, FILE *fp);
void batch_print_query5F(Flights *fli, FILE *fp, int i);
void batch_print_query6(ORIGIN_PASSENGER_COUNT *opc, FILE *fp);
void batch_print_query6F(ORIGIN_PASSENGER_COUNT *opc, FILE *fp, int i);
void batch_print_query8(int total, FILE *fp);
void batch_print_query8F(int total, FILE *fp, int i);
void batch_print_query9(Users *u, FILE *fp);
void batch_print_query9F(Users *u, FILE *fp, int i);