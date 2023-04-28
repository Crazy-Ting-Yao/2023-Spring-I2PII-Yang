#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node{
    int idx;
    struct node* left;
    struct node* right;
    struct node* parent;
}Node;
Node** pos;
char buf[3005];
int* visited;
int dest;
int recursion(int strpos,int current){
    if(pos[current]->idx == dest) return 1;
    if(visited[current]) return 0;
    else visited[current] = 1;
    if(pos[current]->left){
        if(recursion(strpos+1,pos[current]->left->idx)){
            buf[strpos] = 'L';
            return 1;
        }
    }
    if(pos[current]->right){
        if(recursion(strpos+1,pos[current]->right->idx)){
            buf[strpos] = 'R';
            return 1;
        }
    }
    if(pos[current]->parent){
        if(recursion(strpos+1,pos[current]->parent->idx)){
            buf[strpos] = 'P';
            return 1;
        }
    }
    return 0;
}
int main(){
    int t;
    scanf("%d",&t);
    pos = malloc(sizeof(Node*)*(t+1));
    visited = malloc(sizeof(int)*(t+1));
    for(int i=1;i<=t;i++){
        pos[i] = malloc(sizeof(Node));
        pos[i]->idx = i;
        pos[i]->left = pos[i]->right = pos[i]->parent = NULL;
    }
    for(int i=1;i<=t;i++){
        int l,r;
        scanf("%d %d",&l,&r);
        if(l){
            pos[i]->left = pos[l];
            pos[l]->parent = pos[i];
        }
        if(r){
            pos[i]->right = pos[r];
            pos[r]->parent = pos[i];
        }
    }
    int o;
    scanf("%d",&o);
    while (o--){
        memset(buf,0,sizeof(char)*3005);
        memset(visited,0,sizeof(int)*(t+1));
        int from;
        scanf("%d %d",&from,&dest);
        recursion(0,from);
        printf("%s\n",buf);
    }
    for(int i=1;i<=t;i++) free(pos[i]);
    free(visited);
    free(pos);
    return 0;
}