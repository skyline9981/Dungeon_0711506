#include "Item.h"
#include "Object.h"
#include "Player.h"
#include <string>
using namespace std;

Item::Item():Object()
{}

Item::Item(string name,string t,int h, int a, int d):Object(name,"item"),type(t),health(h),attack(a),defense(d)
{}

int Item::getHealth(){
    return health;
}

int Item::getAttack(){
    return attack;
}

int Item::getDefense(){
    return defense;
}

string Item::getType()
{
    return type;
}

void Item::setType(string type)
{
    this->type=type;
}

void Item::setHealth(int h){
    this->health=h;
}

void Item::setAttack(int a){
    this->attack=a;
}
void Item::setDefense(int d){
    this->defense=d;
}

void Item::triggerEvent(Object* player){
    Player *playerptr=static_cast<Player*>(player);
    char c;

    if(type=="weapon"){
        cout<<"Wear "<<this->getName()<<"(a) ,or put it into the backpack(b)"<<endl;
        cin>>c;
        if(c=='a'||c=='A'){
            playerptr->increaseStates(getHealth(),getHealth(),getAttack(),getDefense());
        }
        else{
            playerptr->addItem(*this);
        }
    }
    else if(type=="recovery"){
        cout<<"Use "<<this->getName()<<"(a) ,or put it into the backpack(b)"<<endl;
        cin>>c;
        if(c=='a'||c=='A'){
            int diff=(playerptr->getMaxHealth()-playerptr->getCurrentHealth());
            playerptr->increaseStates(0,((diff>this->getHealth())?this->getHealth():diff),0,0);
        }
        else{
            playerptr->addItem(*this);
        }
    }else if(type=="treasure"){
        cout<<"adding "<<this->getName()<<" into the backpack"<<endl;
        playerptr->addItem(*this);
    }
}

void Item::showitem()
{
    cout<<"-------<"<<getType()<<">------"<<endl;
    cout<<"name : "<<getName()<<endl;
    cout<<"health :"<<getHealth()<<endl;
    cout<<"attack :"<<getAttack()<<endl;
    cout<<"defense : "<<getDefense()<<endl;
}
