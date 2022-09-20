#include "NPC.h"
#include "GameCharacter.h"
#include "Item.h"
#include "Player.h"
#include "Object.h"

#include <string>
#include <vector>
#include <iostream>
using namespace std ;

NPC::NPC():GameCharacter()
{}

NPC::NPC(string name,string script,vector<Item> &item):GameCharacter(name, "NPC",100,0,10000){
    setName(name) ;
    setScript(script);
    setCommodity(item);
}


void NPC::setScript(string script){
    this -> script = script ;
}

void NPC::listCommodity()
{
    for(int i=0;i<commodity.size();i++)
    {
        commodity[i].showitem();
    }
}

void NPC::access()
{
    listCommodity();
}


void NPC::setCommodity(vector<Item> itemlist)
{
    commodity.assign(itemlist.begin(),itemlist.end());
}

string NPC::getScript()
{
    return script;
}

vector<Item> NPC::getCommodity()
{
    return commodity;
}

void NPC::showstatus()
{
    cout<<getScript()<<endl;
}

void NPC::showinventory()//show commodity of NPC
{
    for(int i=0;i<(int)commodity.size();i++)
    {
        cout << i+1 << "." << endl ;
        commodity[i].showitem();
    }
}

void NPC::triggerEvent(Object* play){
    showstatus();
    Player *playptr=static_cast<Player*>(play);
    if(this->getCommodity().empty() )
    {
        cout<<"Sorry,all the commdity have been sold out"<<endl;
        return;
    }

    cout << "Do you want trade your health with my commodity?(y/n)" <<endl
         << "cost 10 current to get an obj"<<endl;
    char q ;
    cin >> q ;
    if(q=='y'){
        if(playptr->getCurrentHealth()<=10){
            cout<<"Sorry do not have enough health to trade with me"<<endl;
            return ;
        }
        showinventory();
        int index ;
        cout << "which do you want to trade?" << endl ;
        cin >> index ;
        cout<<"NICE CHOOSE!"<<endl;
        playptr->increaseStates(0,-10,0,0);
        commodity[index-1].triggerEvent(playptr);
        commodity.erase(commodity.begin()+(index-1));
    }
}

