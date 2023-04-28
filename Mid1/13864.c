#include <stdio.h>
#include <stdlib.h>

typedef struct _Node{
    struct _Node* next;
    int val;
} Node;

Node* table[25];
int pos[25];

void resetBook(int p2) {
    Node* current = table[pos[p2]]->next;
    while(current->val!=p2) current = current->next;
    Node* temp = current;
    current = current->next;
    while(current){
        Node* t = current;
        current = current->next;
        table[t->val]->next = t;
        pos[t->val] = t->val;
        t->next = NULL;
    }
    temp->next = NULL;
}

void pileOnto(int p1, int p2) {
    Node* s = table[pos[p1]];
    if(s->next) while(s->next->val!=p1) s = s->next;
    Node* current = s;
    s = s->next;
    current->next = NULL;
    current = table[pos[p2]];
    while(current->next) current = current->next;
    current->next = s;
    while(s){
        pos[s->val] = pos[p2];
        s = s->next;
    }
}

void initialize(int n) {
    for(int i = 0; i<n; i++){
        table[i] = (Node*)malloc(sizeof(Node));
        table[i]->val = -1;
        table[i]->next = (Node*)malloc(sizeof(Node));
        table[i]->next->val = i;
        pos[i] = i;
        table[i]->next->next = NULL;
    }
}

int main() {
    int n; 
    scanf("%d", &n);
    initialize(n);

    while(1){
        char input[100] = {0};
        int p1, p2; scanf("%s", input);
        if(input[0] == 'e') break;
        scanf("%d%s%d", &p1, input, &p2);
        if(pos[p1] == pos[p2]) continue;
        resetBook(p2); 
        pileOnto(p1, p2);
    }

    Node* tmp;
    for(int i = 0; i < n; i++){
        printf("%d:", i);
        tmp = table[i]->next;
        while(tmp){
            printf(" %d", tmp->val);
            tmp = tmp->next;
        } 
        printf("\n");
    }

    return 0;
}