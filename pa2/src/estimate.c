#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string.h>

double** multiply(double **array1, double **array2, int rows1, int columns1, int rows2, int columns2) {
    double** result = malloc(rows1*sizeof(double*));
    for(int i = 0; i< rows1; i++) {
        result[i] = malloc((columns2)*sizeof(double));
    }
    double sum =0;
    for(int i = 0; i < rows1; i++) {
        for(int j = 0; j < columns2; j++) {
            for(int k = 0; k < columns1; k++) {
                sum += array1[i][k] * array2[k][j];
            }
           result[i][j] = sum;
           sum = 0;
        }   
    }
    return result;
}


double** inversion (double** array, int iterator) {
//allocate for I
    double **I = malloc(iterator*sizeof(double*));
    for(int i =0; i<iterator; i++) {
        I[i] = malloc(iterator*sizeof(double));
    }
//store I
    for(int i = 0; i <iterator; i++) {
        for(int j =0; j < iterator; j++) {
            if(i == j) {
                I[i][j] = 1;
            }
            else {I[i][j] = 0;}
        }
    }
//Algorithm
    for(int i = 0; i < iterator; i++) {
        double f = array[i][i];
        for(int a = 0; a<iterator; a++) {
            array[i][a] = array[i][a]/f;
            I[i][a] = I[i][a]/f;
        }
        for(int j =i+1; j<iterator; j++) {
            f = array[j][i];
            for(int k = 0; k<iterator; k++) {
                array[j][k] = array[j][k] - (array[i][k]*f);
                I[j][k] = I[j][k] - (I[i][k]*f);
            }
        }
    }
    for(int i = iterator-1; i>=0; i--) {
        for(int j = i-1; j >= 0; j--) {
            double f = array[j][i];
            for(int k = 0; k< iterator; k++) {
                array[j][k] = array[j][k] - (array[i][k]*f);
                I[j][k] = I[j][k] - (I[i][k]*f);
            }
        }
    }
    return I;
}

double **matrixTranspose(double** array, int rows, int columns) {
    double** arrayTranspose = malloc((columns+1) * sizeof(double*));
    for(int i = 0; i<columns+1; i++) {
        arrayTranspose[i] = malloc(rows * sizeof(double));
    }
    
    for(int i = 0; i< rows; i++) {
        for(int j = 0; j < columns+1; j++) {
            arrayTranspose[j][i] = array[i][j];
        }
    }
    return arrayTranspose;
}

int main(int argc, char** argv) {
    char tString[6];
    char dString[5];
    int trows, drows;
    int tcolumns, dcolumns;
    char const* const fileName = argv[1];
    FILE* file = fopen(fileName, "r");
    
    fscanf(file, "%s", tString);
    if(strcmp(tString, "train") != 0) {return -1;}
    fscanf (file, "%d", &tcolumns);
    fscanf (file, "%d", &trows);

    double** train = malloc(trows * sizeof(double*));
    double** trainMatrix = malloc(trows * sizeof(double*));
    double** yMatrix = malloc(trows * sizeof(double*));
    
    for(int i = 0; i < trows; i++) {
        train[i] = malloc((tcolumns + 2) * sizeof(double));
        trainMatrix[i] = malloc((tcolumns + 1) * sizeof(double));
        yMatrix[i] = malloc(1 * sizeof(double));
    }
    // Everything up until here works
    for(int i =0; i<trows; i++) {
        for(int j =1; j<tcolumns+2;j++) {
            if (!feof (file)){  
                fscanf (file, "%lf", &train[i][j]);
            }
        }
    }

    for(int i = 0; i<trows; i++) {
        train[i][0] = (double)1.0;
        yMatrix[i][0] = train[i][tcolumns+1];
    }

    for(int i =0; i<trows; i++) {
        for(int j =0; j<tcolumns+1; j++) {
            trainMatrix[i][j] = train[i][j];
        }
    }

    double** transpose = matrixTranspose(trainMatrix, trows, tcolumns);
    double** mult = multiply(transpose, trainMatrix, tcolumns+1, trows, trows, tcolumns+1); //A^TA
    double** inverse = inversion(mult, tcolumns+1);
    double** secondPart = multiply(transpose, yMatrix, tcolumns+1, trows, trows, 1);
    double** W = multiply(inverse, secondPart, tcolumns+1, tcolumns+1, trows, 1);
    for(int i = 0; i<tcolumns+1; i++) {
        free(secondPart[i]);
        free(transpose[i]);
        free(inverse[i]);
        free(mult[i]);
    }
    free(secondPart);
    free(transpose);
    free(inverse);
    for(int i =0; i<trows; i++){
        free(train[i]);
        free(trainMatrix[i]);
        free(yMatrix[i]);
    }
    free(yMatrix);
    free(train);
    free(trainMatrix);
    free(mult);
    fclose(file);

    char const* const dataFile = argv[2];
    FILE* x = fopen(dataFile, "r");
    fscanf (x, "%s", dString);
    if(strcmp(dString, "data") != 0) {return -1;}
    fscanf (x, "%d", &dcolumns);
    fscanf (x, "%d", &drows);

    double** data = malloc(drows * sizeof(double*));
    for(int i = 0; i<drows; i++) {
        data[i] = malloc((dcolumns+1) * sizeof(double));
    }

    for(int i = 0; i<drows; i++) {
        data[i][0] = (double)1.0;
    }

    for(int i =0; i<drows; i++) {
        for(int j =1; j<dcolumns+1;j++) {
            //if (!feof (x)){  
                fscanf(x, "%lf", &data[i][j]);
            //}
        }
    }

    double** finalMatrix = multiply(data, W, drows, dcolumns+1, trows, 1);
    for(int i = 0; i<drows; i++) {
        for(int j =0; j<1; j++) {
            printf("%.0f", finalMatrix[i][j]);
        }
        printf("\n");
    }
    
    for(int i = 0; i<tcolumns+1; i++) {
        free(W[i]);
    }
    for(int i =0; i<drows; i++) {
        free(finalMatrix[i]);
    }
    free(W);
    free(finalMatrix);
    for(int i = 0; i<drows; i++) {
        free(data[i]);
    }
    free(data);
}
