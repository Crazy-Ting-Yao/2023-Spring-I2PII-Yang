typedef struct _Node {
    int serial, stu_id;
    char name[1001]; 
    struct _Node* next;
} Node;

void eFormSort(Node *head){
    Node* sorted = head;
    head = head->next;
    Node* current_pos = sorted;
    for(int i=2;head;i++){
        Node* current = head;
        if(current->serial==i){
            head = head->next;
            current_pos->next = current;
            current_pos = current_pos->next;
            continue;
        }
        while(current->next->serial!=i) current = current->next;
        current_pos->next = current->next;
        current_pos = current_pos->next;
        current->next = current_pos->next;
    }
}