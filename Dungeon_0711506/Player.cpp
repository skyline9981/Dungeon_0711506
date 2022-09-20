#include "Player.h"
#include "Item.h"
#include "Room.h"
#include "GameCharacter.h"
#include "tool.h"
#include <cstddef>
#include<vector>
#include<iomanip>
using namespace std;


vector<Item> Player::getInventory()const
{
    return inventory;
}

Player::Player():GameCharacter()
{
    currentRoom=NULL;
    previousRoom=NULL;
}
Player::Player(string name,int health,int att,int def):GameCharacter(name,"player",health,att,def)
{
    currentRoom=NULL;
    previousRoom=NULL;
}

void Player::addItem(Item obj)
{
    inventory.push_back(obj);
}
void Player::increaseStates(int maxh,int curh,int att, int def)
{
    if(maxh!=0){
        cout<<setw(17)<<"MaxHealth:"<<this->getMaxHealth()<<"--->"<<this->getMaxHealth()+maxh<<endl;
        this->setMaxHealth(this->getMaxHealth()+maxh);
    }
    if(curh!=0){
        cout<<setw(17)<<"CurrentHealth:"<<this->getCurrentHealth()<<"--->"<<this->getCurrentHealth()+curh<<endl;
        this->setCurrentHealth(this->getCurrentHealth()+curh);

    }
    if(att!=0){
        cout<<setw(17)<<"Attack:"<<this->getAttack()<<"--->"<<this->getAttack()+att<<endl;
        this->setAttack(this->getAttack()+att);
    }

    if(def!=0){
        cout<<setw(17)<<"Denfense:"<<this->getDefense()<<"--->"<<this->getDefense()+def<<endl;
        this->setDefense(this->getDefense()+def);
    }
}

void Player::changeRoom(Room* nextroom)
{
    previousRoom=currentRoom;
    currentRoom=nextroom;
}

void Player::setCurrentRoom(Room* setroom)
{
   currentRoom=setroom;
}
void Player::setPreviousRoom(Room* setroom)
{
    previousRoom=setroom;
}
void Player::setInventory(vector<Item> inventorylist)
{
    inventory.assign(inventorylist.begin(),inventorylist.end());
}

void Player::showstatus()
{
    cout<<"--------<player>--------"<<endl;
    cout<<setw(17)<<"name : "<<setw(10)<<getName()<<endl;
    cout<<setw(17)<<"maxHealth : "<<setw(10)<<getMaxHealth()<<endl;
    cout<<setw(17)<<"currentHealth : "<<setw(10)<<getCurrentHealth()<<endl;
    cout<<setw(17)<<"attack : "<<setw(10)<<getAttack()<<endl;
    cout<<setw(17)<<"defense : "<<setw(10)<<getDefense()<<endl;
}

int Player::countitem()
{
    int count=0;
    for(int i=0;i<inventory.size();i++)
    {
        if(inventory[i].getType()=="treasure")
            count++;
    }
    return count;
}

int Player::chooseskill()
{
    cout<<"a.normal atack("<<this->getAttack()<<")"<<endl;
    cout<<"b.using item"<<endl;
    if(countitem()>0){
        cout<<"c.Ultimate abilitiy("<<3*this->getAttack()<<"/one treasure)"<<endl;
    }

    char c;
    cin>>c;
    if(c=='a'||c=='A'){
        return this->getAttack();
    }
    else if(c=='b'||c=='B'){
        usingItem();
        return 0;
    }
    else if(c=='c'||c=='C'){
        int pos=findpos2(inventory,"treasure");
        popitem(pos);
        return 3*this->getAttack();
    }
    else{
        cout<<"System : invalid input"<<endl;
        return chooseskill();
    }
}

void Player::access(){
    showinventory();
};

void Player::usingItem()
{
    if(inventory.size()==0){
            cout<<"System : you do not have any Item"<<endl;
            return;
        }
        this->access();
        cout<<"Input the index of the Item that you want to use(1 ~ "
            <<inventory.size()<<")\nBack to previous(-1)"<<endl;
        int index;
        cin>>index;
        if(index==-1)
            return;
        index--;
        if(inventory[index].getType()=="weapon")
            wear_gear(index);
        else if(inventory[index].getType()=="recovery")
            using_recovery(index);
        else if(inventory[index].getType()=="treasure")
            cout<<"you can't use Item directly"<<endl;
}

void Player::popitem(int index)
{
    inventory.erase(inventory.begin()+index);
}

void Player::using_recovery(int index)
{
    int diff=(getMaxHealth()-getCurrentHealth());
    this->increaseStates(0,((diff>inventory[index].getHealth())?inventory[index].getHealth():diff),0,0);
    popitem(index);
}

void Player::wear_gear(int index)
{
    this->increaseStates(inventory[index].getHealth(),inventory[index].getHealth(),inventory[index].getAttack(),inventory[index].getDefense());
    popitem(index);
}

void Player::showinventory()
{
    cout<<"---------<Backpack information>----------"<<endl;
    if(inventory.empty())cout<<"The back pack is empty ..."<<endl;
    for(int i=0;i<(int)inventory.size();i++)
    {
        cout<<i+1<<"."<<endl;
        inventory[i].showitem();
    }
}
Room* Player::getCurrentRoom()const{
    return currentRoom ;
};
Room* Player::getPreviousRoom()const{
    return previousRoom ;
};
