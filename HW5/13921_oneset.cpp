#include<iostream>
#include<set>
int main(){
    std::set<int> line;
    int t;
    std::cin>>t;
    while(t--){
        int op, num;
        std::cin>>op>>num;
        if(op==1)
            if(line.find(num)==line.end()) line.insert(num);
            else line.erase(num);
        else{
            auto it1 = line.upper_bound(num);
            if(it1==line.end() || it1==line.begin()){
                std::cout<<"-1"<<std::endl; 
                continue;
            }
            auto it2 = it1;
            it1--;
            std::cout<<*it2 - *it1<<std::endl;
        }
    }
}