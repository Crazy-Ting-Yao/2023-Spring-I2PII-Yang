#include <iostream>
#include <string>
using namespace std;

class Darray{
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

class Darray_stack{
    public:
        Darray_stack();
        void operator << (const int&);
        void operator >> (int&);
        int size(){
            return arr.length();
        }
    private:
        Darray arr;
};

using namespace std;

string verify_code(string v){
    Darray_stack st;
    string s = "";
    for(int i = 0; i < v.length(); i++){
        int t = v[i] - 48, tmp;
        while(st.size()){
            st >> tmp;
            if(tmp <= t){
                st << tmp;
                break;
            }
        }
        s += to_string(st.size());
        st << t;
    }
    return s;
}

int main(){
    string verify_input, s;
    cin >> verify_input;
    getline(cin, s);
    getline(cin, s);
    cout << verify_code(verify_input) << "\n";
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

Darray_stack::Darray_stack(){}
void Darray_stack::operator << (const int& x){
    arr.pushback(x);
}
void Darray_stack::operator >> (int& x){
    x = arr.back();
    arr.popback();
}