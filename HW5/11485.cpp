#include<iostream>
#include<string>
#include<set>
#include<vector>
#include<algorithm>

int cal_vector(std::vector<int> a){
    int len = a.size();
    int a_res = 0;
    for(int i=0;i<len;i++) a_res += a[i]*(len-i);
    return a_res;
}

struct Vector{
    bool operator()(std::vector<int> a, std::vector<int> b){
        return cal_vector(a)<cal_vector(b);
    }
};



int main(){
    std::set<std::vector<int>,Vector> st;
    std::string op;
    while(std::cin>>op){
        if(op=="output"){
            for(auto it = st.begin(); it != st.end(); it++){
                for(int i = 0; i<it->size();i++){
                    std::cout<<(*it)[i]<<" ";
                }
                std::cout<<std::endl;
            }
        }
        else if(op == "insert"){
            std::pair<std::set<std::vector<int>>::iterator,bool> ret;
            std::vector<int> new_vec;
            int v;
            while(std::cin>>v){
                if(!v) break;
                new_vec.push_back(v);
            }
            ret = st.insert(new_vec);
            if(!ret.second){
                std::cout<<"exist\n";
                std::reverse(new_vec.begin(), new_vec.end());
                st.erase(ret.first);
                st.insert(new_vec);
            }
        }
        else if(op == "range_out"){
            std::vector<int> v1, v2;
            int v;
            while(std::cin>>v){
                if(!v) break;
                v1.push_back(v);
            }
            while(std::cin>>v){
                if(!v) break;
                v2.push_back(v);
            }
            if(cal_vector(v1)>cal_vector(v2)) continue;
            std::set<std::vector<int>>::iterator it_begin, it_end;
            it_begin = st.lower_bound(v1);
            it_end = st.upper_bound(v2);
            for(;it_begin!=it_end;it_begin++){
                for(int i=0;i<it_begin->size();i++){
                    std::cout<<(*it_begin)[i]<<" ";
                }
                std::cout<<std::endl;
            }
        }
    }
}