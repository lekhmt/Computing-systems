#include <stdio.h>
#include "person.h"

int main(int argc, char* argv[]){

    if (argc != 3){
        fprintf(stderr, "Недостаточно аргументов\n");
        return 1;
    }
    FILE* in = fopen(argv[1], "r");
    if (in == NULL){
        fprintf(stderr, "Проблема с файлом \"%s\"\n", argv[1]);
        return 1;
    }
    FILE* out = fopen(argv[2], "w");
    if (out == NULL){
        fclose(in);
        fprintf(stderr, "Проблема с файлом \"%s\"\n", argv[2]);
        return 2;
    }

    Person p;
    while (fscanf(in, "%[^:]:%[^:]:%[^:]:%d:%d:%d:%d:%d", p.name, p.surname, p.patronymic,
                  &p.m, &p.ph, &p.r, &p.pa, &p.hostel) == 8){
        if (fwrite(&p, sizeof(Person), 1, out) != 1){
            fprintf(stderr, "Проблема с записью в файл \"%s\"\n", argv[2]);
            return 2;
        }
    }

    if (ferror(in) || ferror(out)){
        fprintf(stderr, "Неизвестная ошибка \n");
        return 3;
    }

    fclose(in); fclose(out);
    return 0;

}

