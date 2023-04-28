#include<iostream>
#include<string.h>

class ListNode
{
    friend class List_stack; //make List_stack a friend
    public:
        ListNode( const int &info ) //constructor
        : data( info ), nextPtr( NULL ), prevPtr( NULL )
        {
        } //end ListNode constructor

    private:
        int data; //data
        ListNode *nextPtr; // next node in list
        ListNode *prevPtr;
}; //end class ListNode

class List_stack {
    public:
        List_stack();
        ~List_stack();
        void push(const int &);
        void pop();
        void print();
    private:
        ListNode *head;
        ListNode *tail;
};
using namespace std;
List_stack::List_stack(){
    head = tail = new ListNode(-1);
}
List_stack::~List_stack(){
    while(head!=tail){
        ListNode* temp = head;
        head = head->nextPtr;
        delete temp;
    }
    delete tail;
}
void List_stack::push(const int &data){
    tail->nextPtr = new ListNode(data);
    tail->nextPtr->prevPtr = tail;
    tail = tail->nextPtr;
}
void List_stack::pop(){
    if(head==tail) return;
    tail = tail->prevPtr;
    delete tail->nextPtr;
    tail->nextPtr = NULL;
}
void List_stack::print(){
    if(head == tail) return;
    ListNode* temp = tail;
    while(temp->prevPtr!=head){
        std::cout<<temp->data<<" ";
        temp = temp->prevPtr;
    }
    std::cout<<temp->data;
}
int main(){
    List_stack L_stack;
    char command[10];
    int n;
    while(cin>>command){

        if(strcmp(command,"pop")==0){
            L_stack.pop();
        }else if(strcmp(command,"push")==0){
            cin >> n;
            L_stack.push(n);
        }else if(strcmp(command, "print") == 0){
            L_stack.print();
            cout << endl;
        }
    }
    return 0;
}
