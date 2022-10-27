#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string.h>

void multiply(int array[500][500], int iterator, int multiplier) {
    int temp[500][500];
    int copy[500][500];
    for ( int i = 0 ; i < iterator ; i++ ) {
        for ( int j = 0 ; j < iterator ; j++ ) {
            copy[i][j] = array[i][j];
        }
    }
    int sum = 0;
    //you loop 1 time less of the power
    for (int i = 0; i < multiplier - 1; i++) // for power
    {
        for ( int b = 0 ; b < iterator ; b++ ) // number of rows
        {
            for (int d = 0 ; d < iterator ; d++ ) //number of columns
            {
                for (int k = 0 ; k < iterator ; k++ )
                {
                    sum += copy[b][k]*array[k][d];
                }
                temp[b][d] = sum;
                sum = 0;
            }
        }

        for ( int b = 0 ; b < iterator ; b++ ) {
            for ( int d = 0 ; d < iterator ; d++ ) {
                copy[b][d] = temp[b][d];
            }
        }
    }
    for (int c = 0 ; c < iterator ; c++ )
    {
        for (int d = 0 ; d < iterator ; d++ )
        {
            printf("%d",copy[c][d]);
            if(d<iterator-1) {
                printf("%s"," ");
            }
        }
        printf("\n");
    }
}

int countcolumns (const char *s)
{
    int columns = 0;
    
    while (isspace(*s)) // Skip leading whitespace
        s++;    // Go to next character in string
    while (*s != '\0') {    // While not at end of string
        columns++;
        while (*s != '\0' && !isspace(*s)) {    // While NOT spaces
            s++;    // Go to next character in string
        }
        while (isspace(*s)) // Skip inter-column whitespace
            s++;
    }
    
    return columns;
}

#define BUFFSIZE 1024
int countlines (FILE *fin)
{
    int  nlines  = 0;
    char line[BUFFSIZE];

    while(fgets(line, BUFFSIZE, fin) != NULL) {
        nlines++;
    }

    return nlines;
}

int main(int argc, char** argv) {
        
    char const* const fileName = argv[1]; /*should check that argc > 1*/ 
    FILE* file = fopen(fileName, "r"); /*should check the result */
    //read_ints(fileName);
    rewind(file);
    rewind(file);
    int size = 0;
    int times = 0;
    fscanf (file, "%d", &size);

    int array[500][500];
    for(int i = 0; i< size; i++) {
        for(int j = 0; j < size; j++) {
            if (!feof (file)){  
                fscanf (file, "%d", &array[i][j]);
            }
        }
    }
    fscanf (file, "%d", &times);
    rewind(file);
    multiply(array, size, times); 

    fclose(file);
    /* may check feof here to make a difference between eof and io failure -- network
       timeout for instance */
}