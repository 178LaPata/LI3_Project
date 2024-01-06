#pragma once

#include "../../includes/model/catalog.h"
#include "../../includes/model/users.h"
#include "../../includes/model/flights.h"
#include "../../includes/model/reservations.h"
#include "../../includes/model/passengers.h"
#include "../../includes/model/date.h"

void batch_print_query1_user(User *u, FILE *fp);
void batch_print_query1F_user(User *u, FILE *fp, int i);
void batch_print_query1_flights(Flight *fli, FILE *fp);
void batch_print_query1F_flights(Flight *fli, FILE *fp, int i);
void batch_print_query1_reservations(Reservation *r, FILE *fp);
void batch_print_query1F_reservations(Reservation *r, FILE *fp, int i);
void batch_print_query3(double total, FILE *fp);
void batch_print_query3F(double total, FILE *fp, int i);
void batch_print_query4(Reservation *r, FILE *fp);
void batch_print_query4F(Reservation *r, FILE *fp, int i);
void batch_print_query5(Flight *fli, FILE *fp);
void batch_print_query5F(Flight *fli, FILE *fp, int i);
void batch_print_query6(ORIGIN_PASSENGER_COUNT *opc, FILE *fp);
void batch_print_query6F(ORIGIN_PASSENGER_COUNT *opc, FILE *fp, int i);
void batch_print_query8(int total, FILE *fp);
void batch_print_query8F(int total, FILE *fp, int i);
void batch_print_query9(User *u, FILE *fp);
void batch_print_query9F(User *u, FILE *fp, int i);