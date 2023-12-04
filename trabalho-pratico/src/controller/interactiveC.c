#include "../../includes/controller/interactiveC.h"

int run_interactive(){

    printf("Indique o caminho para a pasta onde se encontram os ficheiros de entrada!\n");    
    char path[20];
    fgets(path, 20, stdin);
    path[strcspn(path, "\n")] = 0;

    catalog *cat = create_catalog(path);



    return 0;
}