#include "../libs/queries.h"

int query1 (XD_USER_HT* user1, XD_DRIVERS_HT* driver1, XD_RIDES_HT rides1, char* path){

    if (isdigit(path) == 0){
        FILE *f = fopen(path, "W");
        if(!f) return -1;

        fprintf(f, get_user_name, get_user_gender, get_age(get_user_birth_date), get_users_aval_med(get_rides_score_user), );
        fclose(f);
        return 0;
    }
    else if (isdigit(path) == 1){
        FILE *f = fopen(path, "W");
        if(!f) return -1;

        fprintf(f, get_user_name, get_user_gender, get_age(get_user_birth_date));
        fclose(f);
        return 0;        
    }
}


/*
Fazer funçoes get
    USERS
        idade -- na date
        avaliacao_media 
        numero_viagens -- nas rides
        total_gasto

    DRIVERS
        idade
        avaliacao_media
        numero_viagens -- nas rides
        total_auferido -- total gasto

*/