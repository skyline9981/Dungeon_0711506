#include "GameCharacter.h"
#include "Item.h"
#include "Object.h"
#include "Player.h"
#include "Chest.h"
#include <vector>
#include <iostream>

using namespace std;


Chest::Chest():GameCharacter()
{}

Chest::Chest(string name, string script,vector<Item> &Treasure,bool isbadchest):GameCharacter(name,"CHEST",100,30,0)
{
        this->setTreasure(Treasure);
        this->setScript(script);
        //this->setOpenornot(openyet);
        this->setIsbadchest(isbadchest);
}

string Chest::getScript(){
    return script;
}

vector<Item> Chest::getTreasure(){
    return treasure;
}

bool Chest::getisbadchest(){
    return isbadchest;
}

void Chest::setIsbadchest(bool isbadchest){
    this->isbadchest=isbadchest;
}

void Chest::setScript(string script){
    this->script=script;
}

void Chest::setTreasure(vector<Item> Treasure){
    this->treasure.assign(Treasure.begin(),Treasure.end());
}

void Chest::showinventory(){
    for(int i=0;i<treasure.size();i++)
        treasure[i].showitem();
}

void Chest::showstatus(){
    cout<<getScript()<<endl;
}

void Chest::triggerEvent(Object * play){
    showstatus();
    Player *playerptr=static_cast<Player*>(play);
    cout<<"Do you want to open the chest (y/n)?"<<endl;
    char temp;
    cin>>temp;
    /*if(temp=='y'){
        cout<<"hello world"<<endl;
    }
*/
//treasure[0].triggerEvent(play);
    /*while(!(temp=='y'||temp=='Y')&&!(temp=='N'||temp=='n')){
        cout<<"Invalid input"<<endl;
        cout<<"please type in again(y/n)"<<endl;
        cin>>temp;
    }*/
    if(temp=='y'||temp=='Y'){
        if(getisbadchest()){
            cout<<"Shit ! There is no treasure inside"<<endl;
            cout<<"Warning ! You got poison ! "<<endl;
            playerptr->increaseStates(0,-10,0,0);
        }
        else{
            cout<<"Wow ! Found "<<treasure[0].getName()<<"<"<<treasure[0].getType()<<">"<<endl;
            treasure[0].triggerEvent(playerptr);
            //playerptr->addItem(treasure[0]);
        }
        //cout<<"OPen the chest"<<endl;
        this->takeDamage(100);
    }
    //cout<<"HELLO"<<endl;
}

void Chest::access()
{
    for(int i=0;i<treasure.size();i++)
    {
        treasure[i].showitem();
    }
}







