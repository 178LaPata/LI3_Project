#include "../includes/catalog.h"

int main(int argc, char** argv){

    if (argc<4) return 0;

    run_tests(argv[1], argv[2], argv[3]);

    return 0;
}