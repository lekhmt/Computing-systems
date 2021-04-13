#ifndef _NUMBER_H
#define _NUMBER_H

typedef enum{
    ERROR = -1,
    ZERO,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN
} Number;

char*    get_enum_name(Number n);
Number   get_enum_number(char* word);

#endif
