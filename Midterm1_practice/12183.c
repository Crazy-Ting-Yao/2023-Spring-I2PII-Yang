#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
    int val;
    char op;
    struct node *left, *right, *parent;
}Node;
Node* variable[100001];
Node* head;
Node* PrefixTree(){
    char c;
    scanf(" %c",&c);
    Node* current;
    if(c=='['){
        int id;
        scanf("%d",&id);
        getchar();
        current = malloc(sizeof(Node));
        current->left = current->right = NULL;
        current->op = 0;
        current->val = 0;
        variable[id] = current;
    }
    else{
        current = malloc(sizeof(Node));
        current->op = c;
        current->left = PrefixTree();
        current->left->parent = current;
        current->right = PrefixTree();
        current->right->parent = current;
        current->val = 0;
    }
    return current;
}
void ValueChange(Node* current){
    if(!current) return;
    char op = current->op;
    if(op=='&'){
        int cal = (current->left->val)&(current->right->val);
        if(cal==current->val) return;
        current->val = cal;
        ValueChange(current->parent);
    }
    else if(op=='|'){
        int cal = (current->left->val)|(current->right->val);
        if(cal==current->val) return;
        current->val = cal;
        ValueChange(current->parent);
    }
    return;
}
void FreeTree(Node* head){
    if(head->left){
        FreeTree(head->left);
        FreeTree(head->right);
    }
    free(head);
}
int main(){
    int t;
    scanf("%d",&t);
    do{
        int n,m;
        scanf("%d %d",&n,&m);
        head = PrefixTree();
        head->parent = NULL;
        do{
            int id;
            scanf("%d",&id);
            variable[id]->val = (variable[id]->val) ? 0:1;
            ValueChange(variable[id]->parent);
            printf("%d\n",head->val);
        }while(--m);
        FreeTree(head);
    }while(--t);
    return 0;
}