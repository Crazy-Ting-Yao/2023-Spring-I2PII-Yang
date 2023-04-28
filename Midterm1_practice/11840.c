#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node{
    int val, table;
    struct node* next;
}Node;
Node **list, **books;
void PutBackUpperBooks(int a){
    Node* current = books[a]->next;
    while(current){
        int val = current->val;
        list[val] = current;
        list[val]->table = val;
        current = current->next;
        list[val]->next = NULL;
    }
}
void PointLowerToNull(int a){
    if(a == books[a]->table) list[a] = NULL;
    else{
        Node* current = list[books[a]->table];
        while(current->next->val!=a) current = current->next;
        current->next = NULL;
    }
}
void MoveOnto(int a,int b){
    PutBackUpperBooks(a);
    books[a]->next = NULL;
    if(a==b) return;
    PutBackUpperBooks(b);
    books[b]->next = books[a];
    PointLowerToNull(a);
    books[a]->table = books[b]->table;
}
void MoveOver(int a,int b){
    PutBackUpperBooks(a);
    books[a]->next = NULL;
    if(a==b) return;
    Node* current = books[b];
    while(current->next) current = current->next;
    current->next = books[a];
    PointLowerToNull(a);
    books[a]->table = books[b]->table;
}
void RearrangeTable(int a,int b){
    Node* current = books[a];
    while(current){
        current->table = books[b]->table;
        current = current->next;
    }
}
void PileOnto(int a,int b){
    if(books[a]->table==books[b]->table) return;
    PutBackUpperBooks(b);
    books[b]->next = books[a];
    PointLowerToNull(a);
    RearrangeTable(a,b);
}
void PileOver(int a,int b){
    if(books[a]->table==books[b]->table) return;
    Node* current = books[b];
    while(current->next) current = current->next;
    current->next = books[a];
    PointLowerToNull(a);
    RearrangeTable(a,b);
}
void EndProcess(int n){
    for(int i=0;i<n;i++){
        printf("%d:",i);
        if(list[i]==NULL) printf("\n");
        else{
            Node *current = list[i], *del;
            while(current){
                printf(" %d",current->val);
                del = current;
                current = current->next;
                free(del);
            }
            printf("\n");
        }
    }
    free(list);
    free(books);
}
int main(){
    int n;
    scanf("%d",&n);
    list = malloc(sizeof(Node*)*n);
    books = malloc(sizeof(Node*)*n);
    for(int i=0;i<n;i++){
        books[i] = list[i] = malloc(sizeof(Node));
        books[i]->val = books[i]->table = i;
        books[i]->next = NULL;
    }
    char s[10];
    while(1){
        int l = scanf("%s",s);
        if(!strcmp(s,"exit")) break;
        else if(!strcmp(s,"move")){
            int a,b;
            scanf(" %d %s %d",&a,s,&b);
            if(!strcmp(s,"over")) MoveOver(a,b);
            else if(!strcmp(s,"onto")) MoveOnto(a,b);
        }
        else if(!strcmp(s,"pile")){
            int a,b;
            scanf(" %d %s %d",&a,s,&b);
            if(!strcmp(s,"over")) PileOver(a,b);
            else if(!strcmp(s,"onto")) PileOnto(a,b);
        }
    }
    EndProcess(n);
    return 0;
}

