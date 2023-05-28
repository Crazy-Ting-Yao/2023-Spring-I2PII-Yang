#include<iostream>
#include<string>
#include<map>

int main(){
    std::map<std::string, std::string> pokemon;
    pokemon.insert(std::make_pair("Wa","Waninoko"));
    pokemon.insert(std::make_pair("Mi","Milotic"));
    pokemon.insert(std::make_pair("Ma","Magikarp"));
    pokemon.insert(std::make_pair("Va","Vaporeon"));
    pokemon.insert(std::make_pair("Sh","Sharpedo"));
    pokemon.insert(std::make_pair("Em","Empoleon"));
    pokemon.insert(std::make_pair("La","Lapras"));
    pokemon.insert(std::make_pair("Pi","Pikachu"));
    pokemon.insert(std::make_pair("Pe","Pikachu"));
    pokemon.insert(std::make_pair("Me","Mega Gyarados"));
    int n;
    std::cin>>n;
    std::string name, school;
    while(n--){
        std::cin>>name>>school;
        auto it = pokemon.find(name.substr(0,2));
        if(it==pokemon.end()){
            if(name.substr(0,4)=="Tapu"){
                std::cout<<name<<" the "<<school<<" Tapu Fini"<<std::endl;
            }
            else{
                std::cout<<name<<" is looking for a Chinese tutor, too!"<<std::endl;
            }
        }
        else{
            std::cout<<name<<" the "<<school<<" "<<it->second<<std::endl;
        }
    }
}