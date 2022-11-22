#include "../libs/users.h"
#include "../libs/drivers.h"
#include "../libs/rides.h"
#include "../libs/date.h"
#include "../libs/queries.h"

int main (int argc, char* agrs[]){

    FILE *file_query = fopen(agrs[2], "r");

    if(file_query){
        perror("ERRO");
    }

    char linha[100];

    while(fgets(linha, 100, file_query)){
        char *dupl = strdup(&linha), *nmr_query = strsep(linha, " "), *argumentos;

        argumentos = strsep(dupl, "\n");

        switch (nmr_query[0]){
        case '1':
            printf("Query1\n");
            //chamar a funcao da query1
            query1(create_userHt(user)1, create_driverHt(driver));
            break;
        
        default:
            break;
        }
    }

    fclose(file_query);

    XD_USER_HT* op1 = create_userHt("users.csv");
    XD_DRIVERS_HT* op2 = create_driverHt ("drivers.csv");   
    XD_RIDES_HT* op3 = create_ridesHt ("rides.csv"); 
}


