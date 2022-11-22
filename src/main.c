#include "../libs/users.h"
#include "../libs/drivers.h"
#include "../libs/rides.h"
#include "../libs/date.h"

int main (int argc, char* agrs[]){
    XD_USER_HT* op1 = create_userHt("users.csv");
    XD_DRIVERS_HT* op2 = create_driverHt ("drivers.csv");   
    XD_RIDES_HT* op3 = create_ridesHt ("rides.csv"); 
}
