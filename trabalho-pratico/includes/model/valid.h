#ifndef VALID_H
#define VALID_H

enum pay_method{
    debit_card,
    credit_card,
    cash,
    noPayMethod
};

enum account_status{
    NoStatus,
    Active,
    Inactive
};

enum pay_method verify_payMethod(char *token);
enum account_status verify_accountStatus (char* token);
char *verify_email(char *email);
char *verify_passport(char *passport);
char *verify_phone_number(char *phone_number);


#endif // VALID_H