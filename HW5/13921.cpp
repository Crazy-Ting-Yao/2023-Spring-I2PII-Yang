#include<iostream>
#include<set>
#include<utility>
int main(){
    std::set<int> line;
    std::set<int, std::greater<int>> rev_line;
    int t;
    std::cin>>t;
    while(t--){
        int op, num;
        std::cin>>op>>num;
        if(op==1){
            if(line.find(num)==line.end()){
                line.insert(num);
                rev_line.insert(num);
            }
            else{
                line.erase(num);
                rev_line.erase(num);
            }
        }
        else{
            auto it1 = line.upper_bound(num);
            auto it2 = rev_line.lower_bound(num);
            if(it1==line.end()||it2 == rev_line.end()) std::cout<<"-1"<<std::endl;
            else std::cout<<*it1-*it2<<std::endl;
        }
    }
}