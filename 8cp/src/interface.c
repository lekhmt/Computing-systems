#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../headers/interface.h"

char* commands[] = {"insert", "add", "remove", "delete", "print", "size", "sorted", "exit", "help"};

void clear_from_tabs(char* _word){
    for (int i = 0; i < strlen(_word); ++i){
        if (_word[i] == '\t'){
            _word[i] = ' ';
        }
    }
    if (_word[strlen(_word) - 1] == '\n'){
        _word[strlen(_word) - 1] = '\0';
    }
}

bool is_command(char* _word){
    bool result = false;
    for (int i = 0; i < 9; ++i){
        if (strcmp(_word, commands[i]) == 0){
            result = true;
        }
    }
    return result;
}

bool is_spaces(char* _word){
    bool result = true;
    for (int i = 0; i < strlen(_word); ++i){
        if (_word[i] != ' ' && _word[i] != '\n' && _word[i] != '\t'){
            result = false;
        }
    }
    return result;
}

bool read_command(char* _word){
    scanf("%s", _word);
    return is_command(_word);
}

void read_arguments(char* _word){
    fgets(_word, STRING_CAPACITY, stdin);
    clear_from_tabs(_word);
}

void help(){
    printf("Run this program with option \"-p\" or \"--preset\" to preset list.\n"
           "Available options:\n"
           "\t--- \033[1minsert\033[0m \033[4mOBJECT\033[0m \033[4mINDEX\033[0m  - insert OBJECT to INDEX position in list\n"
           "\t--- \033[1madd front\033[0m \033[4mOBJECT\033[0m  - insert OBJECT at the front of list\n"
           "\t--- \033[1madd back\033[0m \033[4mOBJECT\033[0m  - insert OBJECT at the back of list\n"
           "\t--- \033[1mremove\033[0m \033[4mINDEX\033[0m - delete object on INDEX position from list\n"
           "\t--- \033[1mdelete front\033[0m - delete one object at the front of list\n"
           "\t--- \033[1mdelete back\033[0m - delete one object at the back of list\n"
           "\t--- \033[1mprint\033[0m - print list\n"
           "\t--- \033[1msize\033[0m - print size of list\n"
           "\t--- \033[1msorted\033[0m - shows if list is sorted\n"
           "\t--- \033[1mexit\033[0m - close program\n"
           "\t--- \033[1mhelp\033[0m - show this information\n");
}

void print_error(char* _msg){
    fprintf(stderr, "\033[31;3mError\033[0m: %s\n", _msg);
}

void print_note(char* _msg){
    printf("\033[33;3mNote\033[0m: %s\n", _msg);
}

void print_interface(char* _msg){
    printf("\033[32;1m%s\033[0m", _msg);
}