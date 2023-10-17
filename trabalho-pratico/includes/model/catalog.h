typedef struct catalog *Catalog;

Catalog *create_Catalog(char *entry_files);
void delete_Catalog(Catalog *c);