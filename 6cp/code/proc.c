#include <stdio.h>

int main(int argc, char* argv[]){

    if (argc != 3){
        fprintf(stderr, "Not enough arguments!\n");
        return 1;
    }
    FILE* in = fopen(argv[1], "r");
    if (in == NULL){
        fprintf(stderr, "Something wrong with %s\n", argv[1]);
        return 1;
    }
    FILE* out = fopen(argv[2], "w");
    if (out == NULL){
        fclose(in);
        fprintf(stderr, "Something wrong with %s\n", argv[2]);
    }

    

}

