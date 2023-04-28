#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
enum position{
    FLOOR,
    STOMACH,
    TRASHCAN
};

class Food;
class Fruit;
class Meat;

class Food{
    protected:
        string name;
        int fly;
        int pos;
    public:
        // constructor
        Food();
        Food(string&);
        // copy constructor
        Food(const Food&);
        // functions
        // eaten: the food is eaten, change its position
        // thrown: the food is thrown, change its position
        // on_floor: return whether the food is on the floor
        // get_name: return the Food's name
        // get_fly: return the amount of the fly
        void eaten();
        void thrown();
        bool on_floor();
        string get_name();
        int get_fly();
        // operators
        // < : use this operator to sort the food so the output of on-floor food satisfy the requirement
        // == : determine whether the food's name is same as a string
        // << : output the food as the mentioned output format
        bool operator < (const Food&);
        bool operator == (const string&);
        friend ostream& operator << (ostream&, Food);
};

class Fruit: public Food{
    public:
        Fruit();
        Fruit(string&);
        // five_min_pass: 5 min passes
        // sickness: return whether the fruit makes someone sick
        // += : mix the food together
        void five_min_pass();
        bool sickness();
        void operator += (Fruit&);
        void operator += (Meat&);
};

class Meat: public Food{
    public:
        Meat();
        Meat(string&);
        // five_min_pass: 5 min passes
        // sickness: return whether the meat makes someone sick
        // += : mix the food together
        void five_min_pass();
        bool sickness();
        void operator += (Fruit&);
        void operator += (Meat&);
};

Meat meat[105];
Fruit fruit[105];
int meat_count, fruit_count;

int get_index(string n, string k){
    if(k == "fruit"){
        for(int i = 0; i < fruit_count; i++){
            if(fruit[i] == n) return i;
        }
    }
    else{
        for(int i = 0; i < meat_count; i++){
            if(meat[i] == n) return i;
        }
    }
    return 0;
}

int main(){
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        while(n--){
            string s, n1, n2, k1, k2;
            cin >> s;
            if(s == "report"){
                cin >> n1 >> k1;
                if(k1 == "fruit"){
                    fruit[fruit_count++] = Fruit(n1);
                }
                else{
                    meat[meat_count++] = Meat(n1);
                }
            }
            else if(s == "eat"){
                cin >> n1 >> k1;
                int idx = get_index(n1, k1);
                if(k1 == "fruit"){
                    fruit[idx].eaten();
                }
                else{
                    meat[idx].eaten();
                }
            }
            else if(s == "throw"){
                cin >> n1 >> k1;
                int idx = get_index(n1, k1);
                if(k1 == "fruit"){
                    fruit[idx].thrown();
                }
                else{
                    meat[idx].thrown();
                }
            }
            else{
                cin >> n1 >> n2 >> k1 >> k2;
                int idx1 = get_index(n1, k1);
                int idx2 = get_index(n2, k2);
                if(k1 == "fruit"){
                    if(k2 == "fruit"){
                        fruit[idx1] += fruit[idx2]; 
                    }
                    else{
                        fruit[idx1] += meat[idx2];
                    }
                }
                else{
                    if(k2 == "fruit"){
                        meat[idx1] += fruit[idx2]; 
                    }
                    else{
                        meat[idx1] += meat[idx2];
                    }
                }
            }
        }
        for(int i = 0; i < fruit_count; i++){
            fruit[i].five_min_pass();
        }
        for(int i = 0; i < meat_count; i++){
            meat[i].five_min_pass();
        }
    }
    // sort the food in the order which meets the requirement
    sort(fruit, fruit + fruit_count);
    sort(meat, meat + meat_count);
    // Making the first t food be all the food on the floor. Design the '<' operator to do this.
    int sick = 0, flag = 0;
    int fruit_floor = fruit_count, meat_floor = meat_count;
    for(int i = 0; i < fruit_count; i++){
        Fruit f(fruit[i]);
        if(!f.on_floor() && !flag){
            fruit_floor = i;
            flag = 1;
        }
        if(f.sickness()) sick++;
    }
    flag = 0;
    for(int i = 0; i < meat_count; i++){
        Meat m(meat[i]);
        if(!m.on_floor() && !flag){
            meat_floor = i;
            flag = 1;
        }
        if(m.sickness()) sick++;
    }

    int onfloor = fruit_floor + meat_floor ;
    cout << sick << "\n" << onfloor << "\n";

    int fruit_idx = 0, meat_idx = 0;
    while(onfloor--){
        bool f1 = meat_idx == meat_floor;
        bool f2 = fruit_idx != fruit_floor;
        bool f3 = fruit[fruit_idx].get_name() < meat[meat_idx].get_name();
        if(f1 || (f2 && f3)){
            cout << fruit[fruit_idx++] << "\n";
        }
        else{
            cout << meat[meat_idx++] << "\n";
        }
    }
    return 0;
}

Food::Food(){ fly = 0; pos = FLOOR; }
Food::Food(string& name){ this->name = name; fly = 0; pos = FLOOR;}
// copy constructor
Food::Food(const Food& f){
    this->name = f.name;
    this->fly = f.fly;
    this->pos = f.pos;
}
// functions
// eaten: the food is eaten, change its position
// thrown: the food is thrown, change its position
// on_floor: return whether the food is on the floor
// get_name: return the Food's name
// get_fly: return the amount of the fly
void Food::eaten(){ this->pos = STOMACH; }
void Food::thrown(){ this->pos = TRASHCAN; }
bool Food::on_floor() { return ( pos==FLOOR ); }
string Food::get_name(){ return name; }
int Food::get_fly(){ return fly; }
// operators
// < : use this operator to sort the food so the output of on-floor food satisfy the requirement
// == : determine whether the food's name is same as a string
// << : output the food as the mentioned output format
bool Food::operator<(const Food& f){
    if( pos==FLOOR ){
        if(f.pos != FLOOR) return true;
        else return (name < f.name);
    }
    else{
        if(f.pos == FLOOR) return false;
        else return (name < f.name);
    }
}

bool Food::operator == (const string& s){ return name==s; }
ostream& operator << (ostream& output, Food f){
    output << f.get_name();
    return output;
}

Fruit::Fruit() :Food() { }
Fruit::Fruit(string& s) : Food(s){}
// five_min_pass: 5 min passes
// sickness: return whether the fruit makes someone sick
// += : mix the food together
void Fruit::five_min_pass(){ if(pos==FLOOR) fly+=4; }
bool Fruit::sickness(){ return (fly>=10 && pos==STOMACH); }
void Fruit::operator += (Fruit& f){
    name=f.name+name;
    fly+=f.fly;
}
void Fruit::operator += (Meat& m){
    name=m.get_name()+name;
    fly+=m.get_fly();
}

Meat::Meat():Food(){}
Meat::Meat(string& s):Food(s){}
// five_min_pass: 5 min passes
// sickness: return whether the meat makes someone sick
// += : mix the food together
void Meat::five_min_pass(){ if(pos==FLOOR) fly+=5; }
bool Meat::sickness(){ return (pos==STOMACH && fly>=20); }
void Meat::operator+=(Fruit& f){
    name = f.get_name() + name;
    fly += f.get_fly();
}
void Meat::operator+=(Meat& m){
    name=m.name+name;
    fly+=m.fly;
}