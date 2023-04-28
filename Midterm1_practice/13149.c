#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node{
    int id;
    struct node *left, *right;
}Node;
int val[3001];
Node* BuildTree(){
    int id;
    scanf("%d",&id);
    Node* current = malloc(sizeof(Node));
    current->id = id;
    char c = getchar();
    if(c=='?'){
        current->left = BuildTree();
        current->right = BuildTree();
    }
    else{
        current->left = current->right = NULL;
    }
    return current;
}
int Calculate(Node* current){
    if(current->left){
        if(val[current->id]) return Calculate(current->left);
        else return Calculate(current->right);
    }
    else return val[current->id];
}
void FreeTree(Node* head){
    if(head->left){
        FreeTree(head->left);
        FreeTree(head->right);
    }
    free(head);
}
int main(){
    Node* head = BuildTree();
    int t;
    scanf("%d",&t);
    do{
        char s[3003];
        scanf("%s",s);
        int n = strlen(s);
        for(int i=0;i<n;i++) val[i+1] = s[i]-'0';
        printf("%d\n",Calculate(head));
    }while(--t);
    FreeTree(head);
    return 0;
}