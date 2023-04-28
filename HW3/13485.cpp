#include "function.h"
#include<string>

String_Calculator::String_Calculator(const string x){
    s = x;
}

String_Calculator& String_Calculator::Add(const string x){
    s += x;
    return *this;
}
String_Calculator& String_Calculator::Subtract(const string x){
    int pos = s.find(x);
    if(pos!=-1) s.erase(pos, x.length());
    else s = "error";
    return *this;
}
String_Calculator& String_Calculator::DividedBy(const string x){
    int ans = 0;
    int pos = s.find(x);
    while(pos!=-1){
        ans++;
        pos = s.find(x,pos+1);
    }
    s = to_string(ans);
    return *this;
}
void String_Calculator::output() const{
    cout<< s << endl;
}