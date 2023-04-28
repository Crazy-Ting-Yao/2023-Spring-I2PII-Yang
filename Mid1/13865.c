#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node{
    char c;
    struct node *left, *right;
}Node;
Node* functions[26];
int A,B,C,D;
char building;
int sub_functions[26][26];
int recursion_occurs[26];
long long Mod(long long num){
    num %= 998244353;
    if(num < 0) num += 998244353;
    return num;
}
Node* build_tree(){
    Node* root = malloc(sizeof(Node));
    scanf(" %c",&root->c);
    switch (root->c){
    case '+': case '*': 
        root->left = build_tree();
        root->right = build_tree();
        break;
    case '@':
        root->left = malloc(sizeof(Node));
        scanf(" %c",&root->left->c);
        root->left->left = root->left->right = NULL;
        sub_functions[building-'a'][root->left->c-'a'] = 1;
        root->right = build_tree();
        break;
    case '-':
        root->left = NULL;
        root->right = build_tree();
        break;
    default:
        root->left = root->right = NULL;
    }
    return root;
}
long long calculate(Node* head,long long x){
    switch (head->c){
    case 'A': 
        return A;
    case 'B':
        return B;
    case 'C':
        return C;
    case 'D':
        return D;
    case 'X':
        return x;
    case '+':
        return Mod(calculate(head->left, x)+calculate(head->right, x));
    case '-':
        return Mod(0-calculate(head->right, x));
    case '*':
        return Mod(calculate(head->left, x)*calculate(head->right, x));
    case '@':
        return Mod(calculate(functions[head->left->c-'a'],calculate(head->right,x)));
    }
    return 0;
}
int passed[26];
int rec(int start){
    if(passed[start]) return 1;
    passed[start] = 1;
    int res=0;
    for(int i=0;i<26;i++)
        if(sub_functions[start][i]) 
            res+=rec(i);
    if(!res) passed[start] = 0;
    return res;
}
void checkrecur(){
    memset(recursion_occurs, 0, sizeof(recursion_occurs));
    for(int i=0;i<26;i++){
        if(recursion_occurs[i]) continue;
        memset(passed,0,sizeof(passed));
        if(rec(i))
            for(int j=0;j<26;j++) 
                if(passed[j])
                    recursion_occurs[j] = 1;
    }
}
void free_tree(Node* head){
    if(head){
        free_tree(head->left);
        free_tree(head->right);
        free(head);
    }
}   
int main(){
    int f,n;
    memset(sub_functions,0,sizeof(sub_functions));
    scanf("%d %d",&f,&n);
    while(f--){
        scanf(" %c",&building);
        functions[building-'a'] = build_tree();
    }
    checkrecur();
    while(n--){
        long long x;
        scanf(" %c %lld %d %d %d %d",&building,&x,&A,&B,&C,&D);
        if(recursion_occurs[building-'a']) printf("Error\n");
        else printf("%lld\n",Mod(calculate(functions[building-'a'],x)));
    }
    for(int i=0;i<26;i++){
        free_tree(functions[i]);
    }
}