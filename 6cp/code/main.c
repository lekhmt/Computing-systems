#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "person.h"

//переменные для хранения значений средних баллов
unsigned int avr_m = 0, avrh_m = 0;
unsigned int avr_p = 0, avrh_p = 0;
unsigned int avr_r = 0, avrh_r = 0;
unsigned int avr = 0, avrh = 0;
int cnt = 0; int h_cnt = 0;

//вызов справки
void help(){
    fprintf(stdout, "Использование: ./<PROGRAM_NAME> <INPUT> [KEYS]\nПри вызове без ключей выводит список"
                    "студентов с баллами по всем предметам выше средних.\nИспользование ключей:\n"
                    "   -m --- сравнивать средний балл по математике.\n   -p --- сравнивать средний балл по физике.\n   "
                    "-r --- сравнивать средний балл по русскому языку.\n   -h --- учитывать только студентов с местом"
                    " в общежитии.\n");
}

//вывод ошибки использоваия ключей
void key_error(char c){
    fprintf(stderr, "Неверный ключ \"%c\"\n", c);
    help();
}

//функция, определяющая выводить ли переданный объект в таблице
bool check(Person* p, unsigned int set_int){
    bool res = true;
    if ((set_int & (1<<3)) != 0){
        if ((set_int & (1<<0)) != 0){
            res &= (p->m > avrh_m) ? 1 : 0;
        }
        if ((set_int & (1<<1)) != 0){
            res &= (p->ph > avrh_p) ? 1 : 0;
        }
        if ((set_int & (1<<2)) != 0){
            res &= (p->r > avrh_r) ? 1 : 0;
        }
    } else {
        if ((set_int & (1<<0)) != 0){
            res &= (p->m > avr_m) ? 1 : 0;
        }
        if ((set_int & (1<<1)) != 0){
            res &= (p->ph > avr_p) ? 1 : 0;
        }
        if ((set_int & (1<<2)) != 0){
            res &= (p->r > avr_r) ? 1 : 0;
        }
    }
    return res;
}


//функция печати строки таблицы
void print(Person* p){

    int name_len = 35; //длина поля имени
    int score_len = 7; //длина полей баллов

    //костыли для вывода строки таблицы
    int l1 = name_len - (int) strlen(p->name) / 2 - (int) strlen(p->surname) / 2;
    int m = (p->m == 100) ? 3 : 2;
    int ph = (p->ph == 100) ? 3 : 2;
    int r = (p->r == 100) ? 3 : 2;
    int l2 = score_len - 3 - m;
    int l3 = score_len - 3 - ph;
    int l4 = score_len - 3 - r;

    if (strcmp(p->patronymic, "-") != 0){
        l1 -= (int) strlen(p->patronymic) / 2 + 1;
        printf("%s %s %s%*c|  M%d%*c| Ф%d%*c| P%d%*c| C%d", p->name, p->surname, p->patronymic, l1, ' ',
                p->m, l2, ' ', p->ph, l3, ' ', p->r, l4, ' ', p->m + p->ph + p->r);
    } else {
        printf("%s %s%*c|  M%d%*c| Ф%d%*c| P%d%*c| C%d", p->name, p->surname, l1, ' ',
                p->m, l2, ' ', p->ph, l3, ' ', p->r, l4, ' ', p->m + p->ph + p->r);
    }

}

int main(int argc, char *argv[]){

    if (argc == 1){
        fprintf(stderr, "Недостаточно аргументов\n");
        help();
        return 1;
    }

    FILE* in = fopen(argv[1], "r");
    if (in == NULL){
        fprintf(stderr, "Проблема с файлом \"%s\"\n", argv[1]);
        return 1;
    }

    unsigned int set_int = 0; //множество ключей

    //заполнение множества ключей
    for (int i = 2; i < argc; ++i){
        if (argv[i][0] != '-' || strlen(argv[i]) <= 1){
            key_error(argv[i][0]);
            return 2;
        }
        for (int j = 1; j < strlen(argv[i]); ++j){
            switch (argv[i][j]) {
                case 'm':
                    set_int |= 1<<0;
                    break;
                case 'p':
                    set_int |= 1<<1;
                    break;
                case 'r':
                    set_int |= 1<<2;
                    break;
                case 'h':
                    set_int |= 1<<3;
                    break;
                default:
                    key_error(argv[i][j]);
                    return 2;
            }
        }
    }

    //если был передан только ключ -h или ключи вообще не были переданы - учитывать все предметы
    if (set_int == 8){
        set_int = 15;
    } else if (set_int == 0){
        set_int = 7;
    }

    Person p;

    //обработка файла src.bin
    while (fread(&p, sizeof(p), 1, in)){
        ++cnt;
        avr_m += p.m;
        avr_p += p.ph;
        avr_r += p.r;
        avr = avr + p.m + p.ph + p.r;
        if (p.hostel == 1){
            avrh_m += p.m;
            avrh_p += p.ph;
            avrh_r += p.r;
            avrh = avrh + p.m + p.ph + p.r;
            ++h_cnt;
        }
    }

    //возврат в начало входного файла
    rewind(in);

    //подсчёт средних значений
    avr_m /= cnt;
    avr_p /= cnt;
    avr_r /= cnt;
    avr /= cnt;
    avrh_m = (h_cnt == 0) ? 0 : avrh_m / h_cnt;
    avrh_p = (h_cnt == 0) ? 0 : avrh_p / h_cnt;
    avrh_r = (h_cnt == 0) ? 0 : avrh_r / h_cnt;
    avrh = (h_cnt == 0) ? 0 : avrh / h_cnt;

    //вывод заголовка таблицы
    printf("Средний балл по запрашиваемым предметам");
    if ((set_int & (1<<3)) != 0){
        printf(" среди студентов, получивших место в общежитии:\n");
        if ((set_int & (1<<0)) != 0){
            printf("Математика - %d\n", avrh_m);
        }
        if ((set_int & (1<<1)) != 0){
            printf("Физика - %d\n", avrh_p);
        }
        if ((set_int & (1<<2)) != 0){
            printf("Русский язык - %d\n", avrh_r);
        }
        printf("\nСписок студентов, получивших место в общежитии, с баллами выше средних:\n");
    } else {
        printf(":\n");
        if ((set_int & (1<<0)) != 0){
            printf("Математика - %d\n", avr_m);
        }
        if ((set_int & (1<<1)) != 0){
            printf("Физика - %d\n", avr_p);
        }
        if ((set_int & (1<<2)) != 0){
            printf("Русский язык - %d\n", avr_r);
        }
        printf("\nСписок студентов, с баллами выше средних:\n");
    }
    
    //вывод запрашиваемой таблицы
    while (fread(&p, sizeof(p), 1, in)){
        if (check(&p, set_int)){
            print(&p);
        }
    }

    putchar('\n');
    return 0;

}