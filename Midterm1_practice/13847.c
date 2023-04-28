#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int data;
    struct node *left, *right;
}Node;
int n, *children_pair, *inorder_pos;
Node* head;
Node* constructTree(int num){
    Node* current = malloc(sizeof(Node));
    current->left = current->right = NULL;
    current->data = num;
    for(int i=1;i<=n;i++){
        if(!children_pair[i]) continue;
        int pos = inorder_pos[num];
        int a = i;
        int b = children_pair[i];
        if(inorder_pos[a]<pos&&inorder_pos[b]>pos){
            children_pair[a] = children_pair[b] = 0;
            current->left = constructTree(a);
            current->right = constructTree(b);
        }
        else if(inorder_pos[a]>pos&&inorder_pos[b]<pos){
            children_pair[a] = children_pair[b] = 0;
            current->left = constructTree(b);
            current->right = constructTree(a);
        }
    }
    return current;
}
//print preorder
void print_tree(Node* current){
    if(current==head)  printf("%d", current->data);
    else printf(" %d", current->data);
    if(current->left){
        print_tree(current->left);
        print_tree(current->right);
    }
}
void free_tree(Node* current){
    if(current->left){
        free_tree(current->left);
        free_tree(current->right);
    }
    free(current);
}
int main(){
    scanf("%d", &n);
    children_pair = calloc(n+1, sizeof(int));
    inorder_pos = malloc(sizeof(int)*(n+1));
    for(int i=0; i<n; i++){
        int a;
        scanf("%d", &a);
        inorder_pos[a] = i;
    }
    int pair = (n-1)/2, root;
    for(int i=0; i<pair; i++){
        int a,b;
        scanf("%d %d", &a, &b);
        children_pair[a] = b;
        children_pair[b] = a;
    }
    for(root=1;root<=n;root++) if(!children_pair[root]) break;
    head = constructTree(root);
    print_tree(head);
    puts("");
    free(children_pair);
    free(inorder_pos);
    free_tree(head);
    return 0;
}