#include<map>
#include<vector>
#include<iostream>
#include<queue>
using namespace std;

int dest_list[1000000];

class candies{
    queue<int> id;
    public:
        int number;
        candies(int id){
            number = 1;
            this->id.push(id);
        }
        void push(int id){
            number++;
            this->id.push(id);
        }
        void pop(int i){
            dest_list[id.front()] = i+1;
            id.pop();
        }
};
vector<int> children[1000000];
int n,m;
map<int,candies*> id;
int type,num; 
vector<int>::iterator child_it;
map<int,candies*>::iterator id_it;

int main(){
    ios::sync_with_stdio(false);
    cin>>n>>m;
    for(int i=0;i<n;i++){
        cin>>num;
        while(num--){
            cin>>type;
            children[i].push_back(type);
        }
    }
    for(int i=0;i<m;i++){
        cin>>type;
        if(id.find(type)==id.end()) id.insert(pair<int,candies*>(type,new candies(i))); 
        else id.at(type)->push(i);
    }
    for(int i=0;i<n;i++){
        bool is_subset = true;
        for(auto &it: children[i]){
            id_it = id.find(it);
            if(id_it==id.end()||!id_it->second->number){
                is_subset = false;
                break;
            }
            id_it->second->number--;
        }
        if(is_subset)
            for(int it: children[i]) 
                id.at(it)->pop(i);         
        else break;
    }
    for(int i=0;i<m;i++) cout<<dest_list[i]<<endl;
}