#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string.h>
#include<stdio.h>
#include<strings.h>
#include<stdlib.h>

struct Node {
    char value;
    struct Node *next;
};
struct Node *first = NULL;
 //construct push pop methods