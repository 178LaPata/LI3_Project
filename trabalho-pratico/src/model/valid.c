#include "../../includes/model/valid.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int verify_phoneNumber(char *token){
    if (strlen(token)!=9) return 0;
    char *val;
    int phone = (int) strtol(token, &val, 10);
    if(strcmp(val, "\0" == 0) & phone > 0) return phone;
    else return 0;
}

enum pay_method verify_payMethod(char *token){
    if (strcasecmp(token,"cash") == 0){
        return cash;
    }
    else if (strcasecmp(token,"card") == 0){
        return card;
    }
    else if (strcasecmp(token,"mbway") == 0){
        return mbway;
    }
    else if (strcasecmp(token,"paypal") == 0){
        return paypal;
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

int verify_email(char *email) {
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
        return 0; 
    }

    usernameLength = atPosition;
    domainLength = lastDotPosition - (atPosition + 1);
    tldLength = strlen(email) - (lastDotPosition + 1);

    if(usernameLength < 1 || domainLength < 1 || tldLength < 2) {
        return 0;
    }

    return 1;
}
