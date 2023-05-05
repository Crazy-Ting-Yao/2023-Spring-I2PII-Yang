#include<iostream>
#include<string.h>
using namespace std;
class Darray {
    public:
        Darray() {
            capacity = 100;
            size = 0;
            data = new int[capacity];
        };
        ~Darray();
        int& operator[](int);
        void pushback(int x);
        void popback(void);
        void clear(void);
        int length(void);
        int back(void);
        void print(void){
            if(this->size == 0){
                cout << endl;
            }
            else{
                for(int i=0; i<this->size; i++){
                    cout << this->data[i] << " ";
                }
                cout << endl;
            }
        };
    private:
        void resize(void); // double the capacity
        int *data;
        int capacity;
        int size;
};
using namespace std;

int main(){
    Darray D_array;
    char command[10];
    int n;
    while(cin>>command){
        if(strcmp(command,"popback")==0){
            D_array.popback();
        }else if(strcmp(command,"pushback")==0){
            cin >> n;
            D_array.pushback(n);
        }else if(strcmp(command,"clear")==0){
            D_array.clear();
        }else if(strcmp(command, "back") == 0){
            int ans = D_array.back();
            cout << ans << endl;
        }else if(strcmp(command, "length") == 0){
            int ans = D_array.length();
            cout << ans << endl;
        }else if(strcmp(command, "print") == 0){
            D_array.print();
        }
    }
    return 0;
}


Darray::~Darray(){ delete [] data; }
int& Darray::operator[](int p){ return data[p]; }
void Darray::pushback(int x){
    if(size==capacity) resize();
    data[size++] = x;
}
void Darray::popback(void){
    if(!size) return;
    else size--;
}
void Darray::clear(void){
    size=0;
    capacity = 100;
    delete [] data;
    data = new int[100];
}
int Darray::length(void){ return size;}
int Darray::back(void){
    if(!size) return -1;
    else return data[size-1];
}
void Darray::resize(void){
    int* n = new int[capacity*=2];
    for(int i=0;i<size;i++) n[i] = data[i];
    delete [] data;
    data = n;
}