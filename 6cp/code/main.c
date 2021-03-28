#include <stdio.h>
#include <string.h>
#include "person.h"

const int MAX_CAPACITY = 1000; //максимальное количество обрабатываемых записей

//вызов справки
void help(){
    fprintf(stdout, "Использование: ./<PROGRAM_NAME> <INPUT> [KEYS]\nПри вызове без ключей выводит список"
                    "студентов с суммарным баллом выше среднего по 3 предметам.\nИспользование ключей:\n"
                    "   -m --- сравнивать средний балл по математике.\n   -p --- сравнивать средний балл по физике.\n   "
                    "-r --- сравнивать средний балл по русскому языку.\n   -h --- учитывать только студентов с местом"
                    " в общежитии.\n");
}

void key_error(char c){
    fprintf(stderr, "Неверный ключ \"%c\"\n", c);
    help();
}

//функция печати строки таблицы
void print(Person p){

    int name_len = 35; //длина поля имени
    int score_len = 7; //длина полей баллов

    //костыли для вывода строки таблицы
    int l1 = name_len - (int) strlen(p.name) / 2 - (int) strlen(p.surname) / 2;
    int m = (p.m == 100) ? 3 : 2;
    int ph = (p.ph == 100) ? 3 : 2;
    int r = (p.r == 100) ? 3 : 2;
    int l2 = score_len - 3 - m;
    int l3 = score_len - 3 - ph;
    int l4 = score_len - 3 - r;

    if (strcmp(p.patronymic, "-") != 0){
        l1 -= (int) strlen(p.patronymic) / 2 + 1;
        fprintf(stdout, "%s %s %s%*c|  M%d%*c| Ф%d%*c| P%d%*c| C%d", p.name, p.surname, p.patronymic, l1, ' ',
                p.m, l2, ' ', p.ph, l3, ' ', p.r, l4, ' ', p.m + p.ph + p.r);
    } else {
        fprintf(stdout, "%s %s%*c|  M%d%*c| Ф%d%*c| P%d%*c| C%d", p.name, p.surname, l1, ' ',
                p.m, l2, ' ', p.ph, l3, ' ', p.r, l4, ' ', p.m + p.ph + p.r);
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

    Person data_arr[MAX_CAPACITY];
    int data_size = 0;
    Person _p;

    //переменные для хранения значений средних баллов
    unsigned int avr_m = 0, avrh_m = 0;
    unsigned int avr_p = 0, avrh_p = 0;
    unsigned int avr_r = 0, avrh_r = 0;
    unsigned int avr = 0, avrh = 0;
    int h_cnt = 0;

    //обработка файла src.bin
    while (fread(&_p, sizeof(_p), 1, in)){
        data_arr[data_size] = _p;
        ++data_size;
        avr_m += _p.m;
        avr_p += _p.ph;
        avr_r += _p.r;
        avr = avr + _p.m + _p.ph + _p.r;
        if (_p.hostel == 1){
            avrh_m += _p.m;
            avrh_p += _p.ph;
            avrh_r += _p.r;
            avrh = avrh + _p.m + _p.ph + _p.r;
            ++h_cnt;
        }
    }

    //подсчёт средних значений
    avr_m /= data_size;
    avr_p /= data_size;
    avr_r /= data_size;
    avr /= data_size;
    avrh_m = (h_cnt == 0) ? 0 : avrh_m / h_cnt;
    avrh_p = (h_cnt == 0) ? 0 : avrh_p / h_cnt;
    avrh_r = (h_cnt == 0) ? 0 : avrh_r / h_cnt;
    avrh = (h_cnt == 0) ? 0 : avrh / h_cnt;

    //вывода запрашиваемой таблицы
    switch (set_int) {

        case 0:
            fprintf(stdout, "Средний балл за 3 предмета: %d\nСписок студентов с суммарным баллом"
                            " больше среднего:\n", avr);
            for (int i = 0; i < data_size; ++i){
                Person p = data_arr[i];
                if (p.m + p.ph + p.r > avr){
                    print(p);
                }
            }
            break;

        case 1:
            fprintf(stdout, "Средний балл по математике: %d\nСписок студентов с баллом по математике больше "
                            "среднего:\n", avr_m);
            for (int i = 0; i < data_size; ++i){
                Person p = data_arr[i];
                if (p.m > avr_m){
                    print(p);
                }
            }
            break;

        case 2:
            fprintf(stdout, "Средний балл по физике: %d\nСписок студентов с баллом по физике больше "
                            "среднего:\n", avr_p);
            for (int i = 0; i < data_size; ++i){
                Person p = data_arr[i];
                if (p.ph > avr_p){
                    print(p);
                }
            }
            break;

        case 3:
            fprintf(stdout, "Средний балл по математике: %d\nСредний балл по физике: %d\n"
                            "Список студентов с баллами по этим 2 предметам больше средних:\n", avr_m, avr_p);
            for (int i = 0; i < data_size; ++i){
                Person p = data_arr[i];
                if (p.ph > avr_p && p.m > avr_m){
                    print(p);
                }
            }
            break;

        case 4:
            fprintf(stdout, "Средний балл по русскому языку: %d\nСписок студентов с баллом по русскому"
                            " языку больше среднего:\n", avr_r);
            for (int i = 0; i < data_size; ++i){
                Person p = data_arr[i];
                if (p.r > avr_r){
                    print(p);
                }
            }
            break;

        case 5:
            fprintf(stdout, "Средний балл по математике: %d\nСредний балл по русскому языку: %d\n"
                            "Список студентов с баллами по этим 2 предметам больше средних:\n", avr_m, avr_r);
            for (int i = 0; i < data_size; ++i){
                Person p = data_arr[i];
                if (p.r > avr_r && p.m > avr_m){
                    print(p);
                }
            }
            break;

        case 6:
            fprintf(stdout, "Средний балл по русскому языку: %d\nСредний балл по физике: %d\n"
                            "Список студентов с баллами по этим 2 предметам больше средних:\n", avr_r, avr_p);
            for (int i = 0; i < data_size; ++i){
                Person p = data_arr[i];
                if (p.ph > avr_p && p.r > avr_r){
                    print(p);
                }
            }
            break;

        case 7:
            fprintf(stdout, "Средний балл по математике: %d\nСредний балл по физике: %d\nСредний балл"
                            " по русскому языку: %d\nСписок студентов с баллами по этим 3 предметам "
                            "больше средних:\n", avr_m, avr_p, avr_r);
            for (int i = 0; i < data_size; ++i){
                Person p = data_arr[i];
                if (p.m > avr_m && p.ph > avr_p && p.r > avr_r){
                    print(p);
                }
            }
            break;

        case 8:
            fprintf(stdout, "Средний балл за 3 предмета среди студентов, получивших место в общежитии: %d\n"
                            "Список студентов, получивших место в общежитии, с суммарным баллом больше среднего:",
                    avrh);
            for (int i = 0; i < data_size; ++i){
                Person p = data_arr[i];
                if (p.m + p.ph + p.r > avrh && p.hostel == 1){
                    print(p);
                }
            }
            break;

        case 9:
            fprintf(stdout, "Средний балл по математике среди студентов, получивших место в общежитии: %d\n"
                            "Список студентов, получивших место в общежитии, с баллом по математике больше"
                            " среднего:", avrh_m);
            for (int i = 0; i < data_size; ++i){
                Person p = data_arr[i];
                if (p.hostel == 1 && p.m > avrh_m){
                    print(p);
                }
            }
            break;

        case 10:
            fprintf(stdout, "Средний балл по физике среди студентов, получивших место в общежитии: %d\n"
                            "Список студентов, получивших место в общежитии, с баллом по физике больше"
                            " среднего:", avrh_p);
            for (int i = 0; i < data_size; ++i){
                Person p = data_arr[i];
                if (p.hostel == 1 && p.ph > avrh_p){
                    print(p);
                }
            }
            break;

        case 11:
            fprintf(stdout, "Средний балл по математике среди студентов, получивших место в общежитии: %d\n"
                            "Средний балл по физике среди студентов, получивших место в общежитии: %d\n"
                            "Список студентов, получивших место в общежитии, с баллом по этим 2 предметам больше"
                            " средних:", avrh_m, avrh_p);
            for (int i = 0; i < data_size; ++i){
                Person p = data_arr[i];
                if (p.hostel == 1 && p.m > avrh_m && p.ph > avrh_p){
                    print(p);
                }
            }
            break;

        case 12:
            fprintf(stdout, "Средний балл по русскому языку среди студентов, получивших место в общежитии: %d\n"
                            "Список студентов, получивших место в общежитии, с баллом по русскому языку больше"
                            " среднего:", avrh_r);
            for (int i = 0; i < data_size; ++i){
                Person p = data_arr[i];
                if (p.hostel == 1 && p.r > avrh_r){
                    print(p);
                }
            }
            break;

        case 13:
            fprintf(stdout, "Средний балл по математике среди студентов, получивших место в общежитии: %d\n"
                            "Средний балл по русскому языку среди студентов, получивших место в общежитии: %d\n"
                            "Список студентов, получивших место в общежитии, с баллом по этим 2 предметам больше"
                            " средних:", avrh_m, avrh_r);
            for (int i = 0; i < data_size; ++i){
                Person p = data_arr[i];
                if (p.hostel == 1 && p.m > avrh_m && p.r > avrh_r){
                    print(p);
                }
            }
            break;

        case 14:
            fprintf(stdout, "Средний балл по русскому языку среди студентов, получивших место в общежитии: %d\n"
                            "Средний балл по физике среди студентов, получивших место в общежитии: %d\n"
                            "Список студентов, получивших место в общежитии, с баллом по этим 2 предметам больше"
                            " средних:", avrh_r, avrh_p);
            for (int i = 0; i < data_size; ++i){
                Person p = data_arr[i];
                if (p.hostel == 1 && p.r > avrh_r && p.ph > avrh_p){
                    print(p);
                }
            }
            break;

        case 15:
            fprintf(stdout, "Средний балл по математике среди студентов, получивших место в общежитии: %d\n"
                            "Средний балл по физике среди студентов, получивших место в общежитии: %d\n"
                            "Средний балл по русскому языку среди студентов, получивших место в общежитии: %d\n"
                            "Список студентов, получивших место в общежитии, с баллом по этим 3 предметам больше"
                            " средних:", avrh_m, avrh_p, avrh_r);
            for (int i = 0; i < data_size; ++i){
                Person p = data_arr[i];
                if (p.hostel == 1 && p.m > avrh_m && p.ph > avrh_p && p.r > avrh_r){
                    print(p);
                }
            }
            break;

        default:
            fprintf(stderr, "Произошла неизвестная ошибка при обработке ключей\n");
            return 2;
    }

    putchar('\n');
    return 0;

}