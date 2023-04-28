#include<stdio.h>
#include<stdlib.h>
typedef struct node{
    int idx;
    struct node *left, *right;
}Node;
int pos;
int n;
int *preorder, *inorder, *postorder;
int exception;
Node* create_tree(int start, int end){
    Node* current = malloc(sizeof(Node));
    int p;
    for(p=start;p<=end;p++){
        if(preorder[pos]==inorder[p]) break;
    }
    current->idx = preorder[pos++];
    if(p>end){
        exception = 1;
        free(current);
        return NULL;
    }
    else if(start==end){
        current->left = current->right = NULL;
    }
    else if(p==start){
        current->left = NULL;
        current->right = create_tree(start+1,end);
    }
    else if(p==end){
        current->right = NULL;
        current->left = create_tree(start,end-1);
    }
    else{
        current->left = create_tree(start,p-1);
        current->right = create_tree(p+1,end);
    }
    return current;
}
int check(Node* current){
    if(current->left){
        if(!check(current->left)){
            return 0;
        }
    }
    if(current->right){
        if(!check(current->right)){
            return 0;
        }
    }
    if(current->idx==postorder[pos++]) return 1;
    return 0;
}
void free_tree(Node* current){
    if(current->left) free_tree(current->left);
    if(current->right) free_tree(current->right);
    free(current);
}
int main(){
    scanf("%d",&n);
    preorder = malloc(sizeof(int)*n);
    inorder = malloc(sizeof(int)*n);
    postorder = malloc(sizeof(int)*n);
    for(int i=0;i<n;i++) scanf("%d",&preorder[i]);
    for(int i=0;i<n;i++) scanf("%d",&postorder[i]);
    int q;
    scanf("%d",&q);
    while(q--){
        pos = exception = 0;
        for(int i=0;i<n;i++) scanf("%d",&inorder[i]);
        Node* head = create_tree(0,n-1);
        if(exception)printf("No\n");
        else{
            pos=0;
            int a = check(head);
            if(a) printf("Yes\n");
            else printf("No\n");
        }
        free_tree(head);
    }
    free(preorder);
    free(postorder);
    free(inorder);
    return 0;
}