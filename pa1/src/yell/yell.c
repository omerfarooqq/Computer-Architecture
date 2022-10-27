#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string.h>


int main(int argc, char** argv) {
    char* c = argv[1];
    if(argc != 2 || argc == 1 || argv[1] == NULL) {
        printf("%s", "");
    }
    for (int i = 0; i < strlen(argv[1]); i++) {
        int a = toupper(c[i]);
        printf("%c", a);
        if(i == (strlen(argv[1])-1)) {
            printf("%s", "!!");
        }
    }
}