#include "../includes/controller/queries.h"

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

int main(int argc, char** argv){
    if (argc<3) return 0;
    setlocale(LC_COLLATE, "en_US.UTF-8");
    run_testes(argv);
    return 0;
}