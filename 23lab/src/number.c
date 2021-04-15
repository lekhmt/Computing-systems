#include "../headers/number.h"
#include <string.h>
#include <ctype.h>

char* get_enum_name(Number n){
    switch (n) {
        case ZERO:
            return "ZERO";
        case ONE:
            return "ONE";
        case TWO:
            return "TWO";
        case THREE:
            return "THREE";
        case FOUR:
            return "FOUR";
        case FIVE:
            return "FIVE";
        case SIX:
            return "SIX";
        case SEVEN:
            return "SEVEN";
        case EIGHT:
            return "EIGHT";
        case NINE:
            return "NINE";
        case TEN:
            return "TEN";
        default:
            return "ERROR";
    }
}

Number get_enum_number(char* word){
    if (word[strlen(word) - 1] == '\n'){
        word[strlen(word) - 1] = '\0';
    }
    for (int i = 0; i < strlen(word); ++i){
        word[i] = (char) tolower(word[i]);
    }
    if (strcmp(word,  "zero") == 0){
        return ZERO;
    }
    if (strcmp(word,  "one") == 0){
        return ONE;
    }
    if (strcmp(word,  "two") == 0){
        return TWO;
    }
    if (strcmp(word,  "three") == 0){
        return THREE;
    }
    if (strcmp(word,  "four") == 0){
        return FOUR;
    }
    if (strcmp(word,  "five") == 0){
        return FIVE;
    }
    if (strcmp(word,  "six") == 0){
        return SIX;
    }
    if (strcmp(word,  "seven") == 0){
        return SEVEN;
    }
    if (strcmp(word,  "eight") == 0){
        return EIGHT;
    }
    if (strcmp(word,  "nine") == 0){
        return NINE;
    }
    if (strcmp(word,  "ten") == 0){
        return TEN;
    }
    return ERROR;
}