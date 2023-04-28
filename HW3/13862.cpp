#include "function.h"
void Person::describe(string* arr, int now, int len){
    Person* current = getRelative(arr,now,len-2);
    if(!arr[len-2].compare("Gender")){
        if(!arr[len-1].compare(table[0])){
            current->gender = MALE;
        }
        else if(!arr[len-1].compare(table[1])){
            current->gender = FEMALE;
        }
    }
    else if(!arr[len-2].compare("Age")){
        current->age = stoi(arr[len-1]);
    }
    else if(!arr[len-2].compare("Name")){
        current->name = arr[len-1];
    }
    else if(!arr[len-2].compare("Personality")){
        if(current->personality.length()) current->personality.append(" ");
        current->personality.append(arr[len-1]);
    }
}
Person* Person::getRelative (string* arr, int now, int len){
    Person* narrator = this;
    while(now!=len){
        string current = arr[now];
        if(!current.compare("ParentA")){
            if(narrator->parentA==NULL){
                narrator->parentA = new Person();
                narrator->parentA->child = narrator;
                if(narrator->parentB){
                    narrator->parentA->mate = narrator->parentB;
                    narrator->parentB->mate = narrator->parentA;
                }
            }
            narrator = narrator->parentA;
        }
        else if(!current.compare("ParentB")){
            if(narrator->parentB==NULL){
                narrator->parentB = new Person();
                narrator->parentB->child = narrator;
                if(narrator->parentA){
                    narrator->parentA->mate = narrator->parentB;
                    narrator->parentB->mate = narrator->parentA;
                }
            }
            narrator = narrator->parentB;
        }
        else if(!current.compare("Child")){
            if(narrator->child==NULL){
                narrator->child = new Person();
                narrator->child->parentA = narrator;
                if(narrator->mate){
                    narrator->mate->child = narrator->child;
                    narrator->child->parentB = narrator->mate;
                }
            }
            narrator = narrator->child;
        }
        else if(!current.compare("Mate")){
            if(narrator->mate==NULL){
                narrator->mate = new Person();
                narrator->mate->mate = narrator;
                if(narrator->child){
                    narrator->mate->child = narrator->child;
                    if(narrator->child->parentA) 
                        narrator->child->parentB = narrator->mate;
                    else
                        narrator->child->parentA = narrator->mate;
                }
            }
            narrator = narrator->mate;
        }
        now++;
    }
    return narrator;
}