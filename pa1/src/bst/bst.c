#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string.h>

typedef struct Node{
    struct Node* left; 
    struct Node* right; //this is the node the current node points to. this is how the nodes link
    int data;
}Node;

struct Keeper* deletedNodes = NULL;
struct Keeper* insertedNodes = NULL;
int counter = 0; 

struct Node *createNode (int data) {
    struct Node* new = (struct Node *)malloc (sizeof(struct Node));
    new->data = data;
    new->right = NULL;
    new->left = NULL;
    counter++;
    return new;
}

void clearBST (struct Node* bst) {
    
}

int isDeleted = 0;
int isInserted = 0;
struct Node* BST = NULL;


void print(struct Node* root) {
    if(root == NULL) {
        return;
    }printf("(");
    print(root->left);
    printf("%d",root->data);
    print(root->right);
    printf(")");
}

void search(struct Node* root, int key) {
    isDeleted =0;
    if(root == NULL) {printf("absent\n");} 
    else if(root->data == key) {printf("present\n");}
    else if(deletedNodes!= NULL) {
        if(isDeleted > 0) {
            printf("deleted");
        }
    }
    else if(key < root->data) {return search(root->left, key);}
    else {return search(root->right, key);}
}

struct Node* insert(struct Node* root, int key) {
    if (root == NULL) {
        root = createNode(key);
        isInserted++;
        return root;
    }
    else if(isInserted > 0) {
        return root;
    }
    else if (key  > root-> data) {
        root->right = insert(root->right, key);
    }
    else if(key < root->data) {
        root->left = insert(root->left, key);
    }
    else{
        return root;
    }
    return root;
}

struct Node* find_minimum(struct Node *root)
{
    if(root == NULL)
        return NULL;
    else if(root->left != NULL) // node with minimum value will have no left child
        return find_minimum(root->left); // left most element will be minimum
    return root;
}

struct Node* delete(struct Node* root, int key) {
    //searching for the item to be deleted
    isDeleted =0;
    if(root==NULL) {return NULL;}
    else if (key > root->data) {root->right = delete(root->right, key);}
    else if(key<root->data) {root->left = delete(root->left, key);}
    else {
        //No Children
        if(root->left==NULL && root->right==NULL) {
            free(root);
            isDeleted++;
            return NULL;
        }

        //One Child
        else if(root->left==NULL) {
            struct Node *temp = root;
            root = root->right;
            free(temp);
            isDeleted++;
        }
        else if(root->right==NULL) {
            struct Node *temp = root;
            root = root->left;
            free(temp);
            isDeleted++;
        }

        //Two Children
        else {
            struct Node *temp = find_minimum(root->right);
            root->data = temp->data;
            root->right = delete(root->right, temp->data);
        }
    }
    return root;
}

int main(int argc,char** argv) {
    char s;
    int a;
    BST = NULL;
    for(int i =scanf("%c", &s); i != EOF; i=scanf("%c", &s)){
        if(s == 'p') {
            print(BST);
            printf("\n");
        }
        else if(s == 'i' || s == 'd' || s == 's') {
            isInserted =0;
            scanf("%d", &a);
            if(s == 'i') {
                BST = insert(BST, a);
                if(isInserted>0) {printf("%s","inserted\n");}
                else {printf("%s","not inserted\n");}   
            }
            if(s == 's') {
                search(BST, a);
                if(isDeleted > 0) {
                    printf("deleted\n");
                }
            }
            if(s == 'd') {
                BST = delete(BST, a);
                if(isDeleted > 0) {
                    printf("deleted\n");
                }
                else{
                    printf("absent\n");
                }
            }
        }
    }
} 