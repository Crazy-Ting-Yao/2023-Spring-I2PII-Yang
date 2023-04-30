#include <iostream>
using namespace std;
class Zoo {
   public:
    int animalCount;
    Zoo() { animalCount = 0; }
    void born(string name) {
        animalCount += 1;
        cout << "New " << name << " Born!\n";
        cnt();
    }
    void dead(string name) {
        animalCount -= 1;
        cout << "One " + name + " Dead!\n";
        cnt();
    }
    void cnt() { cout << "Now Zoo have " << (animalCount) << " animals!\n"; }
};
class Animal {
   public:
    Zoo *belong;
    string species;
    int legs;
    Animal(Zoo *zoo, string name);  // TODO
    virtual void barking() = 0;
    virtual void throwBall() = 0;
    virtual void carton() = 0;
    void printSpecies() { cout << this->species << "\n"; }
    virtual ~Animal() {
        if (this->belong != NULL) this->belong->dead(this->species);
    };  // Please Ensure that you know what this destructure is.
};
class Dog : public virtual Animal {
   public:
    Dog(Zoo *zoo);  // TODO
    void barking() { cout << "woof!\n"; }
    void throwBall() { cout << "it looks happy!\n"; }
    virtual void carton(){};
    ~Dog();  // TODO
};
class Cat : public virtual Animal {
   public:
    Cat(Zoo *zoo);  // TODO
    void barking() { cout << "meow!\n"; }
    void carton() { cout << "it looks so happy!\n"; }
    virtual void throwBall(){};
    ~Cat();  // TODO
};
class Caog : public Dog, public Cat {
   public:
    Caog(Zoo *zoo);          // TODO
    virtual void barking();  // TODO
    void carton();           // TODO
    void throwBall();        // TODO
    ~Caog();                 // TODO
};

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    Zoo z;
    int N;
    cin >> N;
    Animal *arr[12];
    int aniTypes;
    for (int i = 0; i < N; i++) {
        cin >> aniTypes;
        if (aniTypes == 0) {
            arr[i] = new Cat(&z);
        } else if (aniTypes == 1) {
            arr[i] = new Dog(&z);
        } else if (aniTypes == 2) {
            arr[i] = new Caog(&z);
        }
    }
    Animal *Ref;
    int T;
    cin >> T;
    int idx, inst;
    for (int i = 0; i < T; i++) {
        cin >> idx >> inst;
        Ref = arr[idx];
        Ref->printSpecies();
        if (inst == 0) {
            Ref->barking();
        } else if (inst == 1) {
            Ref->throwBall();
        } else if (inst == 2) {
            Ref->carton();
        }
    }
    for (int i = 0; i < N; i++) {
        delete arr[i];
    }
}

Animal::Animal(Zoo *zoo, string name){
    this->belong = zoo;
    species = name;
    zoo->born(name);
}  // TODO

Dog::Dog(Zoo *zoo) : Animal(zoo, "Dog"){}  // TODO

Dog::~Dog(){}  // TODO

Cat::Cat(Zoo *zoo) : Animal(zoo, "Cat"){}  // TODO

Cat::~Cat(){}

Caog::Caog(Zoo *zoo) : Animal(zoo, "Caog"), Dog(zoo), Cat(zoo){}  // TODO
void Caog::barking(){ cout << "woof!woof!meow!\n"; }
void Caog::carton(){ Cat::carton(); }           // TODO
void Caog::throwBall(){ Dog::throwBall(); }        // TODO
Caog::~Caog(){}                 // TODO