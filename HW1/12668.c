#include<stdio.h>
#include<stdlib.h>
typedef struct node{
    char data;
    struct node* before;
    struct node* after;
}Node;
int main(){
    int T;
    scanf("%d",&T);
    Node* head = malloc(sizeof(Node));
    Node* tail = malloc(sizeof(Node));
    while (T--){
        head->after = tail;
        tail->before = head;
        head->before = tail->after = NULL;
        Node* current = head;
        int steps;
        scanf("%d",&steps);
        Node* temp;
        for(int i=0;i<steps;i++){
            char c;
            scanf(" %c",&c);
            switch (c){
            case 'L':
                current = current->before;
                break;
            case 'R':
                current = current->after;
                break;
            case 'B':
                temp = current->before;
                temp->after = current->after;
                current->after->before = temp;
                free(current);
                current = temp;
                break;
            default:
                temp = malloc(sizeof(Node));
                temp->data = c;
                temp->after = current->after;
                current->after = temp;
                temp->before = current;
                temp->after->before = temp;
                current = current->after;
                break;
            }
        }
        Node* printer=head->after;
        while(printer!=tail){
            printf("%c",printer->data);
            Node* temp = printer;
            printer = printer->after;
            free(temp);
        }
        printf("\n");
    }
    free(head);
    free(tail);
    return 0;
}