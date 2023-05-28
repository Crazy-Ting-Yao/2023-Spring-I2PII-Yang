#include<iostream>
#include<queue>
#include<set>
typedef struct{
    int HP;
    int MHP;
    int level;
}state;

struct cmp
{
    bool operator()(const state &a, const state &b){
        if(a.HP-b.HP) return  a.HP>b.HP;
        if(a.MHP-b.MHP) return a.MHP>b.MHP;
        return a.level>b.level;
    }
};

int main(){
    std::ios::sync_with_stdio(false);
    int steps = -1;
    int L, HP, MHP, MDMG;
    std::cin>>L>>HP>>MHP>>MDMG;
    int HL_List[L+1], DMG_List[L+1];
    for(int i=1;i<=L;i++) std::cin>>DMG_List[i]>>HL_List[i];
    std::queue<std::pair<state,int>> states;
    std::set<state,cmp> passed;
    state initial;
    initial.HP = HP, initial.level = 1, initial.MHP = MHP;
    passed.insert(initial);
    states.push(std::make_pair(initial,0));
    while(!states.empty()){
        state current = states.front().first;
        int step = states.front().second+1;
        states.pop();
        state attack;
        attack.MHP = current.MHP - DMG_List[current.level];
        if(attack.MHP<=0){
            steps = step;
            break;
        }
        attack.HP = current.HP-MDMG;
        attack.level = current.level;
        if( attack.HP>0 && passed.find(attack)==passed.end()) {
            passed.insert(attack);
            states.push(std::make_pair(attack,step));
        }
        if( current.level < L && current.HP-MDMG>0 ){
            state upgrade;
            upgrade.HP = current.HP-MDMG;
            upgrade.level = current.level+1;
            upgrade.MHP = current.MHP;
            if(passed.find(upgrade)==passed.end()){
                passed.insert(upgrade);
                states.push(std::make_pair(upgrade,step));
            }
        }
        if(current.HP<HP-MDMG && HL_List[current.level]>MDMG){
            state heal;
            heal.HP = current.HP+HL_List[current.level];
            if(heal.HP>HP) heal.HP=HP;
            heal.HP-=MDMG;
            if(heal.HP<=0) continue;
            heal.level = current.level;
            heal.MHP = current.MHP;
            if(passed.find(heal)==passed.end()){
                passed.insert(heal);
                states.push(std::make_pair(heal,step));
            }
        }
    }
    std::cout<<steps<<std::endl;
}