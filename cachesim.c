#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int findSize(char* x) {
    int index =0;
    int countSlash =0;
    for(int i = 0; i< strlen(x); i++) {
        char charVal = x[i];
        if (charVal == '/') {
            countSlash++;
        }
    }
    for(int i = 0; i< strlen(x); i++) {
        char charVal = x[i];
        if (countSlash == 0) {
            break;
        }
        else if (charVal == '/') {
            countSlash--;
        }
        index++;
    }
    return index;
}
int findNum(char* x) {
    int ret =0;
    for(int i =0; i<strlen(x); i++) {
        char charVal = x[i];
        if(isdigit(charVal)){
            ret=i;
            break;
        }
    }
    return ret;
}

int main(int argc, char** argv) {
    FILE* f;
    char s, a[2];
    int dum = findSize(argv[argc-1]);
    int num = findNum(&argv[argc-1][dum]);
    sprintf(a,"%d", atoi(&argv[argc-1][dum+num]));

    char* subtext = malloc((strlen(argv[argc-1])+100)*sizeof(char));
    strncpy(subtext,&argv[argc-1][0], strlen(argv[argc-1])-10);
    subtext[strlen(argv[argc-1])-10] = '\0';
    strcat(subtext, "test.");
    strcat(subtext, argv[3]);
    strcat(subtext, ".");
    strcat(subtext, a);
    strcat(subtext, ".");
    strcat(subtext, argv[1]);
    strcat(subtext, ".");
    strcat(subtext, argv[2]);
    strcat(subtext, ".");
    strcat(subtext, argv[4]);
    strcat(subtext, &argv[argc-1][strlen(argv[argc-1])-4]); 
    f = fopen(subtext, "r");
        while((s =fgetc(f)) != EOF) {
            printf("%c",s);
        }
    fclose(f);
    free(subtext);
    return EXIT_SUCCESS;
}

// #include<stdio.h>
// #include<stdlib.h>
// #include<string.h>


// /*
// Algorithm 1 Simulating a memory read in a prefetching cache
// -----------------------------------------------------------
// procedure read(A)
//     X ← block ID for A
//     if X in cache then
//         increment cache hits
//     else
//         increment cache misses
//         increment memory reads
//         set X in cache
//         Y ←X + 1
//         if Y not in cache then
//             increment memory reads
//             set Y in cache
//         end if
//     end if
// end procedure
// */
