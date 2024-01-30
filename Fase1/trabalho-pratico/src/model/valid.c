#include "../../includes/model/valid.h"

enum pay_method verify_payMethod(char *token){
    if (strcasecmp(token,"debit_card") == 0) return debit_card;
    else if (strcasecmp(token,"credit_card") == 0) return credit_card;
    else if (strcasecmp(token,"cash") == 0) return cash;
    else return noPayMethod;
}

enum account_status verify_accountStatus (char* token){
    if (strcasecmp(token,"active") == 0) return Active;
    else if (strcasecmp(token,"inactive") == 0) return Inactive;
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

    if(atCount != 1 || dotCount < 1 || atPosition < 1 || lastDotPosition < atPosition+2 || lastDotPosition == strlen(email)-1) return NULL; 
    
    usernameLength = atPosition;
    domainLength = lastDotPosition - (atPosition + 1);
    tldLength = strlen(email) - (lastDotPosition + 1);

    if(usernameLength < 1 || domainLength < 1 || tldLength < 2) return NULL;

    char *validEmail = malloc(strlen(email) + 1);
    strcpy(validEmail, email);

    return validEmail;
}

char *verify_passport(char *passport) {
    int len = strlen(passport);
    if (!isalpha(passport[0]) || !isalpha(passport[1])) return NULL;
    for (int i = 2; i < len; i++) {
        if (!isdigit(passport[i])) return NULL;
    }
    return strdup(passport); 
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

int verify_stars(char *stars){
    int i;
    int len = strlen(stars);
    int k = atoi(stars);
    for (i = 0; i < len; i++){
        if (!isdigit(stars[i])) return 0;
    }
    if (k < 0 || k > 5) return 0;
    return atoi(stars);

}

int verify_maior_que_zero(char *number){
    int i;
    int len = strlen(number);
    for (i = 0; i < len; i++){
        if (!isdigit(number[i])) return 0;
    }
    if (atoi(number) < 0) return 0;
    return atoi(number);
}

int verify_maior_igual_que_zero(char *number){
    int i;
    int len = strlen(number);
    for (i = 0; i < len; i++){
        if (!isdigit(number[i])) return 0;
    }
    if (atoi(number) <= 0) return 0;
    return atoi(number);
}

char *verify_includes_breakfast(char *includes_breakfast) {
    for(int i = 0; includes_breakfast[i]; i++){
        includes_breakfast[i] = tolower(includes_breakfast[i]);
    }
    if (strcmp(includes_breakfast, "f") == 0 || strcmp(includes_breakfast, "false") == 0 || 
        strcmp(includes_breakfast, "0") == 0 || strcmp(includes_breakfast, "") == 0) {
        return strdup("False");
    } else if (strcmp(includes_breakfast, "t") == 0 || strcmp(includes_breakfast, "true") == 0 || 
               strcmp(includes_breakfast, "1") == 0) {
        return strdup("True");
    } else {
        return NULL; 
    }
}

char *verify_rating(char *rating){
    int i;
    int len = strlen(rating);
    if(strlen(rating) == 0) rating = "";
    for (i = 0; i < len; i++){
        if (!isdigit(rating[i])) return NULL;
    }
    if (atoi(rating) < 0 || atoi(rating) > 5) return NULL;
    return strdup(rating);
}

// verifica se a string apenas contem numeros
int verify_only_numbers(char *str){
    int i;
    int len = strlen(str);
    for (i = 0; i < len; i++){
        if (!isdigit(str[i])) return 0;
    }
    return 1;
}

// funcao que escreve para o ficheiro as entradas invalidas do csv 
void validate_csv_error(char *line, char *file_name){
    char file[BUFFER];
    sprintf(file, "./Resultados/%s_errors.csv", file_name);
    FILE *fp_errors = fopen(file, "a");
    if(fp_errors != NULL) {
        fprintf(fp_errors, "%s\n", line);
        fclose(fp_errors);
    } else {
        printf("Error opening file %s\n", file);
    }
}
