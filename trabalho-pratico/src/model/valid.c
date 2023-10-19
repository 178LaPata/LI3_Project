#include "../../includes/model/valid.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

enum pay_method verify_payMethod(char *token){
    if (strcasecmp(token,"debit_card") == 0){
        return debit_card;
    }
    else if (strcasecmp(token,"credit_card") == 0){
        return credit_card;
    }
    else if (strcasecmp(token,"cash") == 0){
        return cash;
    }
    else return noPayMethod;
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

char *verify_email(char *email) { 
    int i, atCount = 0, dotCount = 0;
    int usernameLength = 0, domainLength = 0, tldLength = 0;
    int lastDotPosition = -1, atPosition = -1;

    for(i = 0; i < strlen(email); i++) {
        if(email[i] == '@') {
            atCount++;
            atPosition = i;
        }
        else if(email[i] == '.') {
            dotCount++;
            lastDotPosition = i;
        }
    }

    if(atCount != 1 || dotCount < 1 || atPosition < 1 || lastDotPosition < atPosition+2 || lastDotPosition == strlen(email)-1) {
        return NULL; // Retorna NULL para indicar que o email é inválido
    }

    usernameLength = atPosition;
    domainLength = lastDotPosition - (atPosition + 1);
    tldLength = strlen(email) - (lastDotPosition + 1);

    if(usernameLength < 1 || domainLength < 1 || tldLength < 2) {
        return NULL; // Retorna NULL para indicar que o email é inválido
    }

    // Aloca memória para a string do email e a copia
    char *validEmail = malloc(strlen(email) + 1);
    strcpy(validEmail, email);

    return validEmail; // Retorna o email válido
}

char *verify_passport(char *passport) {
    int len = strlen(passport);
    if (!isalpha(passport[0]) || !isalpha(passport[1])) return NULL; // Os dois primeiros caracteres devem ser letras
    for (int i = 2; i < len; i++) {
        if (!isdigit(passport[i])) return NULL; // Os restantes caracteres devem ser dígitos
    }
    return strdup(passport); // Retorna uma cópia válida do passaporte
}

char *verify_phone_number(char *phone_number){
    int i;
    int len = strlen(phone_number);
    if (len < 9) return NULL;
    for (i = 0; i < len; i++){
        if (!isdigit(phone_number[i])) return NULL;
    }
    return strdup(phone_number);

}