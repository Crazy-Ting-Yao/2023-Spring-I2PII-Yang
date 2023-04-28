#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    char c;
    struct node *left, *right;
} Node;
typedef enum{
    left,right,none
}Direction;
Node* build_tree() {
    Node* current = malloc(sizeof(Node));
    scanf(" %c",&current->c);
    switch (current->c) {
        case '+':
        case '-':
        case '*':
        case '/':
            current->left = build_tree();
            current->right = build_tree();
            break;
        default:
            current->left = current->right = NULL;
    }
    return current;
}
void printing(char previous, Node* current,Direction dir) {
    char c = current->c;
    switch (c){
    case '+':
        if(previous=='/'||previous=='*'||(dir==right&&previous=='-')){
            printf("(");
            printing(c, current->left, left);
            printf("%c",c);
            printing(c, current->right, right);
            printf(")");
        }
        else{
            printing(c, current->left, left);
            printf("%c",c);
            printing(c, current->right, right);
        }
        break;
    case '-':
        if(previous=='/'||previous=='*'||(dir==right&&(previous=='-'))){
            printf("(");
            printing(c, current->left, left);
            printf("%c",c);
            printing(c, current->right, right);
            printf(")");
        }
        else{
            printing(c, current->left, left);
            printf("%c",c);
            printing(c, current->right, right);
        }
        break;
    case '*':
        if(dir==right&&previous=='/'){
            printf("(");
            printing(c, current->left, left);
            printf("%c",c);
            printing(c, current->right, right);
            printf(")");
        }
        else{
            printing(c, current->left, left);
            printf("%c",c);
            printing(c, current->right, right);
        }
        break;
    case '/':
        if(dir==right&&previous=='/'){
            printf("(");
            printing(c, current->left, left);
            printf("%c",c);
            printing(c, current->right, right);
            printf(")");
        }
        else{
            printing(c, current->left, left);
            printf("%c",c);
            printing(c, current->right, right);
        }
        break;
    default:
        printf("%c",c);
        break;
    }
    free(current);
}
int main() {
    Node* head = build_tree();
    printing(' ', head, none);
    printf("\n");
    return 0;
}