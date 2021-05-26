// тип элементов - вещественный
// линейный двунаправленный
// переставить элементы списка в обратном порядке

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../headers/interface.h"
#include "../headers/list.h"

int main(int argc, char* argv[]){

    if (argc != 1){
        if (strcmp(argv[1], "-p") == 0 || strcmp(argv[1], "--preset") == 0){
            printf("preset value\n");
        } else {
            print_error("undefined option.");
            exit(1);
        }
    }

    list l;
    list_create(&l);

    char word[STRING_CAPACITY];
    bool response;

    help();

    do {

        print_interface("cmd: ");
        response = read_command(word);

        if (!response){
            print_error("not a command. Try again.");
            read_arguments(word);
            continue;
        }

        if (is_spaces(word) || strcmp(word, "") == 0 || strcmp(word, "\n") == 0){
            print_note("type a command.");
            continue;
        }

        if (strcmp(word, "insert") == 0){
            T value; int index;
            scanf("%d %d", &value, &index);
            list_insert(&l, index, value);
            continue;
        }

        if (strcmp(word, "add") == 0){
            char target[STRING_CAPACITY];
            scanf("%s", target);
            T value;
            scanf("%d", &value);
            if (strcmp("front", target) == 0){
                list_push_front(&l, value);
            } else if (strcmp("back", target) == 0){
                list_push_back(&l, value);
            } else {
                read_arguments(word);
                print_error("not a command. Try again.");
            }
            continue;
        }

        if (strcmp(word, "remove") == 0){
            int index;
            scanf("%d", &index);
            list_delete(&l, index);
            continue;
        }

        if (strcmp(word, "delete") == 0) {
            char target[STRING_CAPACITY];
            scanf("%s", target);
            if (strcmp("front", target) == 0) {
                list_pop_front(&l);
            } else if (strcmp("back", target) == 0) {
                list_pop_back(&l);
            } else {
                read_arguments(word);
                print_error("not a command. Try again.");
            }
            continue;
        }

        if (strcmp(word, "print") == 0){
            read_arguments(word);
            if (strcmp(word, "") != 0){
                print_note("function \"print\" does not require arguments.");
            }
            list_print(&l);
            continue;
        }

        if (strcmp(word, "size") == 0){
            read_arguments(word);
            if (strcmp(word, "") != 0){
                print_note("function \"size\" does not require arguments.");
            }
            printf("list size = %d\n", list_size(&l));
            continue;
        }

        if (strcmp(word, "reverse") == 0){
            read_arguments(word);
            if (strcmp(word, "") != 0){
                print_note("function \"reverse\" does not require arguments.");
            }
            list_reverse(&l);
            continue;
        }

        if (strcmp(word, "clear") == 0){
            read_arguments(word);
            if (strcmp(word, "") != 0){
                print_note("function \"clear\" does not require arguments.");
            }
            // do clear
            printf("function clear\n");
            continue;
        }

        if (strcmp(word, "help") == 0) {
            help();
            continue;
        }

    } while ((strcmp(word, "exit") != 0));

}