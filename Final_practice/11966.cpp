#include<stack>
#include<iostream>
#include<string>
int main(){
    int n;
    std::cin>>n;
    std::string s;
    getline(std::cin, s);
    for(int i=1;i<=n;i++){
        getline(std::cin, s);
        std::stack<char> stk;
        bool flag = true;
        for(auto &it:s){
            switch (it){
            case '{': case '[': case '(': case '<':
                stk.push(it);
                break;
            case '}':
                if(!stk.empty() && stk.top()=='{') stk.pop();
                else flag = false;
                break;
            case ']':
                if(!stk.empty() && stk.top()=='[') stk.pop();
                else flag = false;
                break;
            case ')':
                if(!stk.empty() && stk.top()=='(') stk.pop();
                else flag = false;
                break;
            case '>':
                if(!stk.empty() && stk.top()=='<') stk.pop();
                else flag = false;
                break;
            }
            if(!flag) break;
        }
        if(flag&&stk.empty()) std::cout<<"Case "<<i<<": Yes"<<std::endl;
        else std::cout<<"Case "<<i<<": No"<<std::endl;
    }
}