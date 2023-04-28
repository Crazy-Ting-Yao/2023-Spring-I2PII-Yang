#include<stdio.h>
#include<stdlib.h>
int a,b,c,d;
typedef struct node{
    char c;
    struct node *left, *right;
}Node;
Node* head;
Node* build_tree() {
    Node* current = malloc(sizeof(Node));
    scanf(" %c",&current->c);
    switch (current->c) {
        case '&':
        case '|':
            current->left = build_tree();
            current->right = build_tree();
            break;
        default:
            current->left = current->right = NULL;
    }
    return current;
}
void free_nodes(Node* current){
    if(current->left){
        free_nodes(current->left);
        free_nodes(current->right);
    }
    free(current);
}
int calculate(Node* current){
    switch (current->c){
    case '&':
        return (calculate(current->left)&calculate(current->right));
    case '|':
        return (calculate(current->left)|calculate(current->right));
    case 'A':
        return a;
    case 'B':
        return b;
    case 'C':
        return c;
    case 'D':
        return d;
    }
    return 0;
}
int main(){
    head = build_tree();
    for(int i=0;i<16;i++){
        d = i&1;
        c = (i>>1)&1;
        b = (i>>2)&1;
        a = (i>>3)&1;
        printf("%d %d %d %d %d\n",a,b,c,d,calculate(head));
    }
    free_nodes(head);
    return 0;
}