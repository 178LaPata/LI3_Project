#include "../../includes/model/catalog.h"
#include "../../includes/model/users.h"
#include "../../includes/model/flights.h"
#include "../../includes/model/reservations.h"
#include "../../includes/model/passengers.h"
#include "../../includes/model/date.h"
#include "../../includes/view/batchP.h"

#define BUFFER 64

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int run_batch(char *inputs_path, char *queries_path);
int run_queries(catalog *cat, char *queries_path);
int run_query(catalog *cat, char *queries_path, FILE *fp_output);
void query1(catalog *cat, char *query, FILE *fp);
void query3(catalog *cat, char *query, FILE *fp);
void query4(catalog *cat, char *query, FILE *fp);
void query5(catalog *cat, char *query, FILE *fp);
void query8(catalog *cat, char *query, FILE *fp);
