#include<stdio.h>
#include<stdlib.h>
int cmp(const void *a,const void *b)
{
    return *(int *)a-*(int *)b;
}

typedef struct node{
    int val;
    struct node *left, *right;
}Node;
Node* head;
#define Size 1001
int preorder[Size], inorder[Size];
int pos=0;
int n;
Node* construct_tree(int l,int r){
    Node* root=(Node*)malloc(sizeof(Node));
    root->left=root->right=NULL;
    root->val=preorder[pos++];
    for(int i=0;i<Size;i++){
        if(inorder[i]==root->val){
            if(i>l)
                root->left=construct_tree(l,i-1);
            if(i<r)
                root->right=construct_tree(i+1,r);
            break;
        }
    }
    return root;
}
void reconstruct_tree(Node* root){
    if(root->left!=NULL)
        reconstruct_tree(root->left);
    root->val=inorder[pos++];
    if(root->right!=NULL)
        reconstruct_tree(root->right);
}
void print_tree(Node* root){
    if(root->left!=NULL)
        print_tree(root->left);
    if(root->right!=NULL)
        print_tree(root->right);
    if(root==head) printf("%d",root->val);
    else printf("%d ",root->val);
    free(root);
}
int main(){
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        scanf("%d",&preorder[i]);
    for(int i=0;i<n;i++)
        scanf("%d",&inorder[i]);
    head=construct_tree(0,n-1);
    qsort(inorder,n,sizeof(int),cmp);
    pos = 0;
    reconstruct_tree(head);
    print_tree(head);
    printf("\n");
    return 0;
}