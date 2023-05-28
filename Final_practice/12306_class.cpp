#include<iostream>
#include<queue>
#include<set>

short *dmgList, *HLlist;
unsigned short maxlevel, maxHP;
short monsterDMG;

class state{
    public:
        unsigned short level;
        short HP;
        short monsterHP;
        //constructor
        state(short hp, short monsterHP, int level) :
            HP(hp), monsterHP(monsterHP), level(level){}
        //copy constructor
        state(const state& s):
            HP(s.HP), monsterHP(s.monsterHP), level(s.level){}

        bool isMaxLevel() {return level == maxlevel;}

        state& levelUP(){ level++; return *this; }

        bool canHeal(){ return HP<maxHP-monsterDMG && HLlist[level]>monsterDMG; }

        state& HEAL(){
            HP += HLlist[level];
            if(HP>maxHP) HP = maxHP;
            return *this;
        }

        state& attack(){ 
            monsterHP -= dmgList[level];
            return *this;
        }

        bool win() { return monsterHP<=0; }

        bool attackByMonster(){ HP -= monsterDMG; return HP>0;}   
};

struct cmp
{
    bool operator()(const state &a, const state &b){
        if(a.HP-b.HP) return  a.HP>b.HP;
        if(a.monsterHP-b.monsterHP) return a.monsterHP>b.monsterHP;
        return a.level>b.level;
    }
};  

int main(){
    int steps = -1;
    short MHP;
    std::cin>>maxlevel>>maxHP>>MHP>>monsterDMG;
    dmgList = new short[maxlevel+1];
    HLlist = new short[maxlevel+1];
    for(int i=1;i<=maxlevel;i++)
        std::cin>>dmgList[i]>>HLlist[i];
    std::queue<std::pair<state,int>> states;
    std::set<state,cmp> passed;
    state initial(maxHP,MHP,1);
    passed.insert(initial);
    states.push(std::make_pair(initial,0));
    while(states.size()){
        state current(states.front().first);
        int cur_step = states.front().second+1;
        states.pop();
        if(!current.isMaxLevel()){
            state lvup(current);
            if(lvup.levelUP().attackByMonster()&&passed.insert(lvup).second) 
                states.push(std::make_pair(lvup,cur_step));
        }
        if(current.canHeal()){
            state Heal(current);
            if(Heal.HEAL().attackByMonster()&&passed.insert(Heal).second) 
                states.push(std::make_pair(Heal,cur_step));
        }
        state attack(current);
        if(attack.attack().win()){ steps = cur_step; break;}
        else if(attack.attackByMonster()&&passed.insert(attack).second) 
            states.push(std::make_pair(attack,cur_step));
    }
    std::cout<<steps<<std::endl;
    delete [] dmgList;
    delete [] HLlist;
    return 0;
}