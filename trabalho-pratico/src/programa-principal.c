#include "../includes/controller/queries.h"

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

int main(int argc, char** argv){
    if (argc == 3){
        setlocale(LC_COLLATE, "en_US.UTF-8");
        run_batch(argv[1], argv[2]);
    } else if (argc == 1){
        run_interativo();
    }
    return 0;
}
