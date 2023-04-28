#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
// construct a binary tree
typedef struct node {
    int data;
    struct node *left, *right;
} Node;
int total_level;
Node* head;
//create binary tree
Node* create_tree(int level){
    if(level == total_level) return NULL;
    Node* current = malloc(sizeof(Node));
    scanf(" %d", &current->data);
    current->left = create_tree(level+1);
    current->right = create_tree(level+1);
    return current;
}
void reconstruct_tree(Node* current){
    if(!current->left) return;
    if(current->left->data > current->right->data){
        Node* temp = current->left;
        current->left = current->right;
        current->right = temp;
    }
    reconstruct_tree(current->left);
    reconstruct_tree(current->right);
}
// print binary tree postorder
void print_tree(Node* current){
    if(current->left){
        print_tree(current->left);
        print_tree(current->right);
    }
    if(current==head)  printf("%d", current->data);
    else printf("%d ", current->data);
}
void free_tree(Node* current){
    if(current->left){
        free_tree(current->left);
        free_tree(current->right);
    }
    free(current);
}
int main(){
    int n;
    scanf("%d", &n);
    total_level = log2(n+1);
    head = create_tree(0);
    reconstruct_tree(head);
    print_tree(head);
    puts("");
    free_tree(head);
    return 0;
}