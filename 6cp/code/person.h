#ifndef PERSON_H
#define PERSON_H
typedef struct {
    char name[64];          //имя
    char surname[64];       //фамилия
    char patronymic[64];    //отчество
    unsigned int m;         //баллы за математику
    unsigned int ph;        //баллы за физику
    unsigned int r;         //баллы за русский язык
    unsigned int pa;        //индвивидуальные достижения
    int hostel;             //наличие общежития
} Person;

#endif