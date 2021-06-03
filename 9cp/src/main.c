#include <stdio.h>
#include <string.h>

#include "../headers/table.h"
#include "../headers/sort.h"

int table_size = 0;
table_element table[TABLE_CAPACITY];

void help(){
    printf("Available options:\n"
           "\t--- \033[1madd\033[0m \033[4mKEY\033[0m \033[4mVALUE\033[0m - add element to table\n"
           "\t--- \033[1mfind\033[0m \033[4mKEY\033[0m - find first entry of element with this key\n"
           "\t--- \033[1mprint\033[0m - print table\n"
           "\t--- \033[1mexit\033[0m - exit this program\n");
}

void print_table(){
    printf("\n");
    int key_size = 12;
    int value_size = 30;
    printf("\033[255;7m| Key%*c| Value%*c|\033[0m\n", 8, ' ', value_size - 6, ' ');
    for (int i = 0; i < table_size; ++i){
        table_element tmp = table[i];
        int length = 1;
        long long n = tmp.key;
        if (n == 0){
            length = 2;
        } else {
            if (n < 0){
                ++length;
                n *= -1;
            }
            while (n > 0){
                ++length;
                n /= 10;
            }
        }
        if (i + 1 != table_size){
            printf("| %lld%*c| %s%*c|\n", tmp.key, key_size - length, ' ', tmp.value, (int)(value_size - strlen(tmp.value)) - 1, ' ');
        } else {
            printf("\033[0255;4m| %lld%*c| %s%*c|\033[0m\n", tmp.key, key_size - length, ' ', tmp.value, (int)(value_size - strlen(tmp.value)) - 1, ' ');
        }
    }
    printf("\n");
}

int binary_search(long long key){
    int l = 0;
    int r = table_size;
    while (r - l > 1){
        int mid = (l + r)/2;
        if (key >= table[mid].key){
            l = mid;
        } else {
            r = mid;
        }
    }
    int idx = l;
    if (table[idx].key != key){
        return -1;
    }
    while (idx > 0){
        if (table[idx - 1].key != key){
            break;
        }
        --idx;
    }
    return idx;
}

int main(){

    char word[STRING_CAPACITY];
    int response;

    preset();

    help();

    do {

        printf("\033[32;1mcmd:\033[0m ");
        response = scanf("%s", word);

        if (strcmp(word, "exit") == 0 || response == EOF){
            break;
        }

        if (strcmp(word, "add") == 0){
            table_element tmp;
            scanf("%lld", &tmp.key);
            scanf("%s", tmp.value);
            table[table_size] = tmp;
            ++table_size;
            continue;
        }

        if (strcmp(word, "find") == 0){
            quick_sort(0, table_size - 1);
            long long key;
            scanf("%lld", &key);
            int idx = binary_search(key);
            if (idx == -1){
                printf("No element found.\n");
            } else {
                printf("Element found: %lld %s\n", table[idx].key, table[idx].value);
            }
            continue;
        }

        if (strcmp(word, "print") == 0){
            print_table();
            shell_sort();
            print_table();
            continue;
        }

    } while (strcmp(word, "exit") != 0);

}