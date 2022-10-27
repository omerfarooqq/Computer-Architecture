#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string.h>

/*char *combineStrings(char* inputA, char* inputB) {
    char* output = malloc(strlen(inputA)+strlen(inputB));
    sprintf((char*)output,"%s%s",inputA,inputB);
    return output;
}
char* uniqueChar(char* input) {
    int a = 1;
    char* ret = "";
    for(int i =0; i<strlen(input); i++) {
        char charValue1[2];
        char charValue2[2];
        int number = input[i];
        int compare = input[a];
        sprintf(charValue1, "%c", number);
        sprintf(charValue2, "%c", compare);
        if(charValue1 != charValue2) {
            ret = combineStrings(ret, charValue1);
        }
    }
    return ret;
}
int main(int argc, char** argv) {
    char* insert = argv[1];
    int count = 0;
    char* final = " ";
    char* unique = uniqueChar(argv[1]);
    char* output = malloc(strlen(unique));
    char charValue1[2];
    char charValue2[2];
    char countToChar[2];
    for(int i =0; i<strlen(unique); i++) {  
        count = 0;
        for(int j =0; j<strlen(insert); j++) {
            int number = unique[i];
            int compare = insert[j];
            sprintf(charValue1, "%c", number);
            sprintf(charValue2, "%c", compare);
            if(charValue1 == charValue2) {
                count++;
            }  
        }
        
        sprintf(countToChar, "%c", (count+'0'));
        final = combineStrings(final, charValue1);
        final = combineStrings(final, countToChar);
        sprintf((char*)output,"%s%s",charValue1,countToChar);
    }
    printf("%s", output);
}*/

/*int main(int argc, char** argv) {
    char* dup = argv[1];
    //int countToChar = 0;
    int count = 1;
    for(int i = 0; i< strlen(dup); i++) {
        count = 1;  
        for(int j = i+1; j < strlen(dup); j++) {
            if(dup[i] == dup[j] && dup[i] != ' ') {  
                count++;  
                //Set string[j] to 0 to avoid printing visited character  
                dup[j] = '0'; 
            }  
        }
        if(count > 1 && dup[i] != '0')  {
            printf("%c%c", dup[i], (count+'0'));
        }
    }
}
*/
int main(int argc, char** argv) {
    char* dup = argv[1];
    int count = 1;
    int isDigit = 0;
    char final[100000];
    int size = 0;
    for(int i = 0; i< strlen(dup); i++) {
        for(int j = i+1; j < strlen(dup); j++) {
            if(isdigit(dup[i]) > 0) {
                isDigit++;
            }
        }
    }
    if(isDigit > 0) {
        printf("error");
    }
    else{    
        for(int i = 0; i< strlen(dup); i++) {
            count=1;
            for(int j = i+1; j < strlen(dup); j++) {
                char number = (char)dup[i];
                char compare = (char)dup[j];
                if(number == compare) {
                    count++;
                    i=j;
                }
                else{
                    break;
                }
            }
            snprintf(final, 100000, "%c%d", dup[i], count);
            size += snprintf(final, 100000, "%c%d", dup[i], count);
        }
        if(size <= strlen(argv[1])) {
            for(int i = 0; i< strlen(dup); i++) {
                count=1;
                for(int j = i+1; j < strlen(dup); j++) {
                    char number = (char)dup[i];
                    char compare = (char)dup[j];
                    if(number == compare) {
                        count++;
                        i=j;
                    }
                    else{
                        break;
                    }
                }
                printf("%c%d", dup[i], count);
            }
        }
        else{
            printf("%s" , argv[1]);
        }
    }
}