#include "../../includes/model/catalog.h"
#include "../../includes/model/users.h"
#include "../../includes/model/flights.h"
#include "../../includes/model/reservations.h"
#include "../../includes/model/passengers.h"
#include "../../includes/model/date.h"

void batch_print_query1_user(Users *u, FILE *fp);
void batch_print_query1_flights(Flights *fli, FILE *fp);
void batch_print_query1_reservations(Reservations *r, FILE *fp);

void batch_print_query3(double total, FILE *fp);
