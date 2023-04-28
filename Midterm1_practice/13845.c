#include<stdio.h>
#include<stdlib.h>
long long val[5];
typedef struct nmode{
    char c;
    struct nmode *left, *right;
}Nmode;
Nmode** trees;
long long mod(long long num){
    num %= 998244353;
    if(num < 0) num += 998244353;
    return num;
}
Nmode* buildtree(){
    Nmode* current = malloc(sizeof(Nmode));
    scanf(" %c",&current->c);
    switch (current->c){
    case '+': case '-': case '*': case '@':
        current->left = buildtree();
        current->right = buildtree();
        break;
    default:
        current->left = current->right = NULL;
    }
    return current;
}
long long calculate(Nmode* current){
    if(!current) return 0;
    switch (current->c){
    case 'A': case 'B': case 'C': case 'D':
        return val[(current->c)-'A'];
    case 'X':
        return mod(val[4]);
    case '+':
        return mod(calculate(current->left)+calculate(current->right));
    case '-':
        return mod(calculate(current->left)-calculate(current->right));
    case '*':
        return mod(calculate(current->left)*calculate(current->right));
    }
    long long x = val[4];
    val[4] = mod(calculate(current->right));
    long long res = mod(calculate(trees[current->left->c-'a']));
    val[4] = x;
    return res;
}
void FreeTree(Nmode* current){
    if(current->left){
        FreeTree(current->left);
        FreeTree(current->right);
    }
    free(current);
}
int main(){
    int n,t;
    scanf("%d %d",&n,&t);
    trees = calloc(26,sizeof(Nmode*));
    do{
        char c;
        scanf(" %c",&c);
        trees[c-'a'] = buildtree();
    }while(--n);
    do{
        char fun;
        scanf(" %c %lld %lld %lld %lld %lld",&fun,&val[4],&val[0],&val[1],&val[2],&val[3]);
        long long ans = calculate(trees[fun-'a']);
        printf("%lld\n",mod(ans));
    }while(--t);
    for(int i=0;i<26;i++) if(trees[i]) FreeTree(trees[i]);
    free(trees);
    return 0;
}