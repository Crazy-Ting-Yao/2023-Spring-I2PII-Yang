#include <stdio.h>
#include <stdlib.h>
typedef struct _Node {
    int size;
    int* data;
    struct _Node* next;
} Node;

Node* ReadOneList();
void PrintList(Node*);
void Merge(Node*, int, int);
void Cut(Node*, int, int);

int main() {
    Node* dummy_head;
    Node* tail;

    dummy_head = (Node*)malloc(sizeof(Node));
    dummy_head->data = NULL;
    dummy_head->size = -1;

    tail = dummy_head;

    int N, M;
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        tail->next = ReadOneList();
        tail = tail->next;
    }
    char act[10];
    int x, y;
    for (int i = 0; i < M; i++) {
        scanf("%s %d %d", act, &x, &y);
        if (act[0] == 'M') {
            Merge(dummy_head, x, y);
        } else {
            Cut(dummy_head, x, y);
        }
    }
    PrintList(dummy_head);
    return 0;
}

Node* ReadOneList() {
    Node* newnode = (Node*)malloc(sizeof(Node));
    scanf("%d: ", &newnode->size);
    newnode->data = (int*)malloc(sizeof(int) * (newnode->size));
    for (int i = 0; i < newnode->size; i++) scanf("%d", &newnode->data[i]);
    return newnode;
}
void PrintList(Node* head) {
    Node* temp = head->next;
    free(head);
    while (temp != NULL) {
        head = temp;
        temp = head->next;
        for (int i = 0; i < head->size - 1; i++) printf("%d ", head->data[i]);
        printf("%d\n", head->data[head->size - 1]);
        free(head->data);
        free(head);
    }
}
void Merge(Node* head, int from, int to) {
    Node* t = head;
    Node* f = head;
    Node* one_before_f;
    for (int i = 0; i < to; i++) t = t->next;
    for (int i = 0; i < from; i++) {
        one_before_f = f;
        f = f->next;
    }
    one_before_f->next = f->next;
    int new_size = t->size + f->size;
    int* r = (int*)realloc(t->data, new_size);
    t->data = r;
    for (int i = t->size; i < new_size; i++)
        t->data[i] = f->data[i - (t->size)];
    t->size = new_size;
    free(f->data);
    free(f);
}
void Cut(Node* head, int from, int pos) {
    Node* f = head;
    for (int i = 0; i < from; i++) f = f->next;
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->size = f->size - pos;
    new_node->data = malloc(sizeof(int) * (new_node->size));
    for (int i = pos; i < f->size; i++) new_node->data[i - pos] = f->data[i];
    int* r = (int*)realloc(f->data, sizeof(int) * pos);
    f->data = r;
    f->size = pos;
    Node* temp = f->next;
    f->next = new_node;
    new_node->next = temp;
}