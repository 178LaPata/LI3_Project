#include "../../includes/model/catalog.h"

void query1_users(catalog *cat, char *id){
    Users *user = query1_users_aux(cat->cat_users, id);
    if (user == NULL){
        printf("Utilizador não encontrado.\n\n");
        return;
    }

    if (get_account_status(user) == 0){
        printf("Conta desativada.\n\n");
        return;
    }

    int idade = calculate_age(get_birth_date(user));
    printf("Nome: %s\n", get_name(user));
    printf("Sexo: %s\n",get_sex(user));
    printf("Idade: %d\n", idade);
    printf("Código do País: %s\n", get_country_code(user));
    printf("Passaporte: %s\n", get_passport(user));
    printf("Número de Voos: %d\n", get_flights_total(user));
    printf("Número de Reservas: %d\n", get_reservations_total(user));
    printf("Total Gasto: %.3f\n\n", get_spent_total(user));
}

void query1_flights(catalog *cat, int id){
    Flights *flight = query1_flights_aux(cat->cat_flights, id);
    if (flight == NULL){
        printf("Voo não encontrado.\n\n");
        return;
    }

    printf("Companhia: %s\n", get_company(flight));
    printf("Avião: %s\n", get_plane(flight));
    printf("Origem: %s\n", get_origin(flight));
    printf("Destino: %s\n", get_destination(flight));
    datetime schedule_departure_date = get_schedule_departure_date(flight);
    printf("Data Estimada de Partida: ");
    printDateTime(schedule_departure_date);
    datetime schedule_arrival_date = get_schedule_arrival_date(flight);
    printf("Data Estimada de Chegada: ");
    printDateTime(schedule_arrival_date);
    printf("Passageiros: %d\n", get_num_passengers(flight));
    printf("Tempo de atraso: %d\n\n", get_delay(flight));
}

void query1_reservations(catalog *cat, char *id){
    Reservations *reservation = query1_reservations_aux(cat->cat_reservations, id);
    if (reservation == NULL){
        printf("Reserva não encontrada.\n\n");
        return;
    }

    printf("ID do hotel: %s\n", get_hotel_id(reservation));
    printf("Nome do hotel: %s\n", get_hotel_name(reservation));
    printf("Estrelas do hotel: %d\n", get_hotel_stars(reservation));
    date begin_date = get_begin_date(reservation);
    printf("Data de início: ");
    printDate(begin_date);
    date end_date = get_end_date(reservation);
    printf("Data de fim: ");
    printDate(end_date);
    printf("Pequeno-almoço: %s\n", get_includes_breakfast(reservation));
    printf("Numero de noites: %d\n", get_nights(reservation));
    printf("Preco total: %.3f\n\n", get_total_price(reservation));

}

void query3(catalog *cat, char *hotel_id){
    double total = 0.0;
    total = query3_aux(cat->cat_reservations, hotel_id);
    // escreve o double com apenas 3 casas decimais
    printf("Avaliação Média: %.3f\n\n", total);
}

/*
Q8 Apresentar a receita total de um hotel entre duas datas (inclusive), a partir do seu identificador.
As receitas de um hotel devem considerar apenas o preço por noite (price_per_night) de todas as
reservas com noites entre as duas datas. E.g., caso um hotel tenha apenas uma reserva de 100€/noite
de 2023/10/01 a 2023/10/10, e quisermos saber as receitas entre 2023/10/01 a 2023/10/02, deverá ser
retornado 200€ (duas noites). Por outro lado, caso a reserva seja entre 2023/10/01 a 2023/09/02,
deverá ser retornado 100€ (uma noite).
*/
void query8(catalog *cat, char *hotel_id, date begin, date end){
    double total = 0.0;
    total = query8_aux(cat->cat_reservations, hotel_id, begin, end);
    printf("Receita total: %.3f\n\n", total);
}

// funcao que da parse as queries
void parse_queries(char *line, catalog *cat, int output_num){

    int i = (int) strtol(strsep(&line, " "), (char **) NULL, 10);

    switch (i){
        case 1:
            char *id = strsep(&line, " ");
            break;
    }

}

int run_batch(char **input_file) {

    catalog *cat = create_catalog(input_file[1]);

    FILE *file_query;
    file_query = fopen(input_file[2], "r");
    
    if(file_query == NULL){
        perror("Erro:");
        exit(1);
    }
    char line[100];
    int buffer_size = 100;
    int num = 0;

    while(fgets(line, buffer_size, file_query)){
        char *query, *n_query, *query_arg, *arg1, *arg2, *arg3;
        query = strdup(line);
        n_query = strsep(&query, " ");
        query_arg = strsep(&query, "\n");
        //unsigned i;
        num++;
        switch (n_query[0]){
            case '1':
                query1_users(cat, query_arg);
                //query1_flights(cat, atoi(query_arg));
                //query1_reservations(cat, query_arg);
                break;
            case '2':
                //query2(cat, query_arg);
                break;
            case '3':
                query3(cat, query_arg);
                break;
            case '4':
                break;
            case '5':
                break;
            case '6':
                break;
            case '7':
                break;
            case '8':
                query8(cat, query_arg, arg1, arg2);
                break;            
            default:
                break;
        }
    }

    delete_catalog(cat);
    return 0;
}

