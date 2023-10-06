#include "valid.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// verificacao basica de um numero de telefone
// TODO: sq add mais restricoes ??
int verify_phoneNumber(char *token){
    if (strlen(token)!=9) return 0;
    char *val;
    int phone = (int) strtol(token, &val, 10);
    if(strcmp(val, "\0" == 0) & phone > 0) return phone;
    else return 0;
}

int verify_total_seats(char *token){

}

int verify_passport(char *token){

}

int verify_countryCode(char *token){

}

enum pay_method verify_payMethod(char *token){
    if (strcasecmp(token,"cash") == 0){
        return Cash;
    }
    else if (strcasecmp(token,"card") == 0){
        return Card;
    }
    else return NoMethod;
}

enum account_status verify_accountStatus (char* token){
    if (strcasecmp(token,"active") == 0){
        return Active;
    }
    else if (strcasecmp(token,"inactive") == 0){
        return Inactive;
    }
    else return NoStatus;
}