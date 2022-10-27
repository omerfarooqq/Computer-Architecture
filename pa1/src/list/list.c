#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string.h>

struct Node {
    int data;
    struct Node* next;
}Node;

struct Node* createNode(int value){
    struct Node* x = (struct Node*) malloc(sizeof(struct Node));
    x->data = value;
    x->next = NULL;
    return x;
}
//Global Node
struct Node* List = NULL;
int count; //count for iteration

void clear(struct Node* received) {
    for(struct Node* f= List; f != NULL; f= List) {
        List = List->next;
        free(f);
    }
    
}
//Sorting
void sortList() {  
    //Node current will point to head  
    struct Node *current = List, *index = NULL;  
    int temp;        
    if(List == NULL) {  
        return;  
    }  
    else {  
        while(current != NULL) {  
            //Node index will point to node next to current  
            index = current->next;        
            while(index != NULL) {  
                //If current node's data is greater than index's node data, swap the data between them  
                if(current->data > index->data) {  
                    temp = current->data;  
                    current->data = index->data;  
                    index->data = temp;  
                }  
                index = index->next;  
            }  
            current = current->next;  
        }      
    }  
}  

struct Node* insert(int value) {
    struct Node* listDummy =NULL;

    int r = 0;
    if(List == NULL) {
        r++;
        List = createNode(value);
        return List;
    }
    else{
        listDummy = List;
        while(listDummy->next != NULL) {
            if(listDummy->data == value) {
                r++;
                break;
            }
            listDummy = listDummy->next;
        }
        if(listDummy->data == value) {
            r++;
        }
        if(r == 0){
            listDummy->next = createNode(value);
        }
    }
    return List;
}

struct Node* delete(int value) {
    struct Node* temp;
    //value found on the head node.
    //move to head node to the next and free the head.
    if( List == NULL) {
        return List;
    }
    if(List->data == value) {
        temp = List;    //backup to free the memory
        List = List->next;
        free(temp);
        return List;
    }
    else {
        struct Node* current  = List;
        while(current->next != NULL) {
            //if yes, we need to delete the current->next node
            if(current->next->data == value) {
                temp = current->next;
                //node will be disconnected from the linked list.
                current->next = current->next->next;
                free(temp);
                break;
            }
            //Otherwise, move the current node and proceed
            else {current = current->next;}
        }
        return List;
    }
    return List;
}

int returnData () {
    count = 0;
    for(struct Node* n = List; n!=NULL; n = n->next) {
        count++;
    }
    return count;
}

int main(int argc,char** argv) {
    char letterInput;
    int numInput, c, dataVal;
    for(int s = scanf("%c %d",&letterInput,&numInput); s != EOF; s = scanf("%c %d",&letterInput,&numInput)) {
        if(letterInput == 'i' || letterInput == 'd') {
            if(letterInput == 'i') {
                c = 0;
                List = insert(numInput);
                c = returnData();
                sortList();
                printf("%i :",c);
                for(struct Node* n = List; n!=NULL; n = n->next) {
                    dataVal = n->data;
                    printf(" %i", dataVal);
                }
                printf("\n");
            }
            if(letterInput == 'd') {
                c = 0;
                List = delete(numInput);
                c = returnData();
                printf("%i :", count);
                for(struct Node* n = List; n != NULL; n = n->next){
                    dataVal = n->data;
                    printf(" %i", dataVal);
                }
            printf("\n");
            }
        }
        else {
            continue;
        }
    }
    clear(List);
    
    return EXIT_SUCCESS;
}
