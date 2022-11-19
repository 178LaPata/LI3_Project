#include "../libs/users.h"
#include "../libs/date.h"

struct xd_users {
    char* line; 
    char* username;
    char* name;
    char gender;
    XD_DATE* birth_date;
    XD_DATE* account_creation;
    char* pay_method;
    char* account_status;
};

// GET
char* get_users_username (XD_USERS user){
    return user -> username;
}

char* get_users_name (XD_USERS user){
    return user -> name;
}

char* get_users_gender (XD_USERS user){
    return user -> gender;
} 

XD_DATE* get_users_birth_date (XD_USERS user){
    return user -> birth_date;
}

XD_DATE* get_users_account_creation (XD_USERS user){
    return user -> account_creation;
}

char* get_users_pay_method (XD_USERS user){
    return user -> pay_method;
}

char* get_users_account_status (XD_USERS user){
    return user -> account_status;
}

// SET
int set_users_username (XD_USERS user, char* line){
    user -> username = strdup(line);
    return strlen(line) > 0;
}

int set_users_name (XD_USERS user, char* line){
    user -> name = strdup(line);
    return strlen(line) > 0;
}

int set_users_gender (XD_USERS user, char* line){
    user -> gender = strdu(line);
    return strlen(line) > 0;
}

int set_users_birth_date (XD_USERS user, char* line){
    int ola = atoi(line);
    user -> date = ola;
    return (ola >= 0) && strlen(line) > 0;
}

int set_users_account_creation (XD_USERS user, char* line){
    int 
}




// nao sei se preciso
int print_user_info (GH_USER usr) // Function used to print a user's information
{
    if(!usr) 
        return 0;

    printf("%d;", usr->id);
    printf("%s;", usr->login);
    printf("%s;", type_to_str(usr->type));
    print_date(usr);
    printf("%d;", usr->followers);
    print_follower_list(usr);
    printf("%d;", usr->following);
    print_following_list(usr);
    printf("%d;", usr->public_gists);
    printf("%d \n", usr->public_repos);
    return 1;
}

int write_user_info (FILE *file, GH_USER usr)
{
    if(!usr) 
        return 0;

    fprintf(file, "%d;", usr->id);
    fprintf(file, "%s;", usr->login);
    fprintf(file, "%s;", type_to_str(usr->type));
    write_date(file, usr);
    fprintf(file, "%d;", usr->followers);
    write_follower_list(file, usr);
    fprintf(file, "%d;", usr->following);
    write_following_list(file, usr);
    fprintf(file, "%d;", usr->public_gists);
    fprintf(file, "%d", usr->public_repos);
    fputc('\n', file);
    return 1;
}
