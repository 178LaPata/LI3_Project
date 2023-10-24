#include "../../includes/model/users.h"
#include "../../includes/model/flights.h"
#include "../../includes/model/reservations.h"
#include "../../includes/model/passengers.h"
#include "../../includes/model/output.h"

typedef struct catalog catalog;

catalog *create_catalog(char *entry_files);
void delete_catalog(catalog *cat);

// queries
char *q01_users(char *id, catalog *cat);


int runBatch(char **input_file);