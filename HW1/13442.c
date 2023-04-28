#include <stdio.h>
#include <stdlib.h>
typedef struct _Node{
    int number, age;
    struct _Node* prev;
    struct _Node* next;
}Node;

Node* head;
Node* createList(int n);
int cmp(const void *pa,const void *pb);
Node* solve(int n, int m);


int main(){

    int n, k;

    scanf("%d%d", &n, &k);
    head = createList(n);
    Node *p = solve(n, k);
    for(int i = 0; i < n; i ++){
        printf("%d ", p -> age);
        p = p -> next;
    }
    printf("\n");
    return 0;
}

Node* createList(int n){
    Node* h = malloc(sizeof(Node));
    scanf("%d",&h->age);
    h->number=1;
    Node* tmp = h;
    for(int i=2;i<=n;i++){
        tmp->next = malloc(sizeof(Node));
        tmp->next->prev = tmp;
        tmp = tmp->next;
        scanf("%d",&tmp->age);
        tmp->number = i;
    }
    tmp->next = h;
    h->prev = tmp;
    return h;
}
int cmp(const void *pa,const void *pb){
    Node** a = (Node**)(pa);
    Node** b = (Node**)(pb);
    if((*a)->age-(*b)->age){
        return (*a)->age-(*b)->age;
    }
    else return (*a)->number-(*b)->number;
}
Node* solve(int n, int m){
    Node** dict = malloc(sizeof(Node*)*n);
    Node* tmp = head;
    for(int i=0;i<n;i++){
        dict[i] = tmp;
        tmp = tmp->next;
    }
    qsort(dict,n,sizeof(Node*),cmp);
    while(m--){
        int age, movement;
        char c;
        scanf("%d %d %c",&age,&movement,&c);
        age--;
        if(c=='R'){
            Node* next_node = dict[age]->next;
            dict[age]->prev->next = next_node;
            next_node->prev = dict[age]->prev;
            while(--movement) next_node = next_node->next;
            next_node->next->prev = dict[age];
            dict[age]->next = next_node->next;
            next_node->next = dict[age];
            dict[age]->prev = next_node;
        }
        else{
            Node* prev_node = dict[age]->prev;
            dict[age]->next->prev = prev_node;
            prev_node->next = dict[age]->next;
            while(--movement) prev_node = prev_node->prev;
            prev_node->prev->next = dict[age];
            dict[age]->prev = prev_node->prev;
            prev_node->prev = dict[age];
            dict[age]->next = prev_node;
        }
    }
    return dict[0];
}