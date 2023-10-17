#ifndef VALID_H
#define VALID_H

enum pay_method{
    cash,
    card,
    mbway,
    paypal,
    noPayMethod
};

enum account_status{
    NoStatus,
    Active,
    Inactive
};

int verify_phoneNumber(char *token);
enum pay_method verify_payMethod(char *token);
enum account_status verify_accountStatus (char* token);
int verify_email(char *email);


#endif // VALID_H