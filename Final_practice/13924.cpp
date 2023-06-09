#include<iostream>
#include<queue>
#include<set>
#include<list>
#include<algorithm>
struct group;

struct group
{
    int id;
    int time;
    int size;
    int duration;
    std::list<group>::iterator itd;
    group(int i, int t, int s, int d)
    : id(i), time(t), size(s), duration(d){}
};

std::list<group> gp_time;
std::priority_queue<int,std::vector<int>,std::greater<int>> tb[2];
std::queue<group> gp_size[6];

int main(){
    int n,m;
    std::cin>>n>>m;
    for(int i=0;i<n;i++){
        int t, s, d;
        std::cin>>t>>s>>d;
        group temp(i,t,s,d);
        gp_time.push_back(temp);
        temp.itd = std::prev(gp_time.end());
        gp_size[s-1].push(temp);
    }
    int time_list[n];
    int small, large, l = 1, s = 0;
    int num;
    std::cin>>small>>num;
    while(num--) tb[0].push(0);
    if(m==2){
        std::cin>>large>>num;
        while(num--) tb[1].push(0);
        if(small>large){ 
            std::swap(small,large);
            l = 0;
            s = 1;
        }
    }
    int time = gp_time.front().time;
    while(!gp_time.empty()){
        if(m==2){
            time = std::max(std::min(tb[0].top(), tb[1].top()), gp_time.front().time);
            if(gp_time.front().size>small){
                if(time>=tb[l].top()){
                    time_list[gp_time.front().id] = time;
                    tb[l].pop();
                    tb[l].push(time+gp_time.front().duration);
                    gp_size[gp_time.front().size-1].pop();
                    gp_time.pop_front();
                    continue;
                }
                else{
                    time = tb[l].top();
                    int id = 6;
                    for(int i=0;i<small;i++){
                        if(!gp_size[i].empty() && std::max(gp_size[i].front().time,tb[s].top())<=time){
                            time = std::max(gp_size[i].front().time,tb[s].top());
                            id = i;
                        }
                    }
                    if(id!=6){
                        time_list[gp_size[id].front().id] = time;
                        tb[s].pop();
                        tb[s].push(time+gp_size[id].front().duration);
                        gp_time.erase(gp_size[id].front().itd);
                        gp_size[id].pop();
                        continue;
                    }
                    time_list[gp_time.front().id] = time;
                    tb[l].pop();
                    tb[l].push(time+gp_time.front().duration);
                    
                    gp_size[gp_time.front().size-1].pop();
                    gp_time.pop_front();
                }
            }
            else{
                if(time<tb[s].top()){
                    time_list[gp_time.front().id] = time;
                    tb[l].pop();
                    tb[l].push(time+gp_time.front().duration);
                    
                    gp_size[gp_time.front().size-1].pop();
                    gp_time.pop_front();
                }
                else{
                    time_list[gp_time.front().id] = time;
                    tb[s].pop();
                    tb[s].push(time+gp_time.front().duration);
                    gp_size[gp_time.front().size-1].pop();
                    gp_time.pop_front();
                }
            }
        }
        else{
            time = std::max(tb[0].top(),gp_time.front().time);
            time_list[gp_time.front().id] = time;
            tb[0].pop();
            tb[0].push(time+gp_time.front().duration);
            gp_size[gp_time.front().size-1].pop();
            gp_time.pop_front();
        }     
    }
    for(int i=0;i<n;i++){
        std::cout<<time_list[i]<<std::endl;
    }
    return 0;
}
