#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "GameCharacter.h"
#include "Player.h"
#include "Monster.h"
#include "Item.h"
#include "time.h"

using namespace std;



Monster::Monster(){};


Monster::Monster(string name ,int health ,int attack ,int defense):GameCharacter(name,"Monster",health , attack , defense ){


};

Item Monster:: createTreasure()
{
    int tt=rand()%3;
    if(tt==0){
        int health;
        health=80+rand()%100;
        return Item("pill<super>","recovery",health,0,0);
    }
    else if(tt==1){
        int att,def,health;
        att=rand()%50;
        def=rand()%50;
        health=rand()%100;
        return Item("dragon_sword<supre>","weapon",health,att,def);
    }
    else if(tt==2){
        int att,def,health;
        att=rand()%20;
        def=rand()%20;
        health=rand()%10;
        return Item("dragon_blood","treasure",health,att,def);
    }
}


bool Monster:: retreatornot()
{
    cout<<"A.keep fighting\nB.retreat\n";
    char temp;
    cin>>temp;
    if(temp=='a'||temp=='A')
        return true;
    else if(temp=='b'||temp=='B')
        return false;
}


void Monster::triggerEvent(Object* play){
    Player *playptr=static_cast<Player*>(play);
    char temp;
    cout<<endl;
    cout<<"What do you want to do"<<endl;
    cout<<"a.Fight with "<<this->getName()<<endl;
    cout<<"b.check the information with the monster"<<endl;
    cout<<"c.Retreat"<<endl;
    cin>>temp;

    if(temp=='a'||temp=='A')
    {
        cout << "System: Start Fightting!!" <<endl ;
        while(!playptr->checkIsDead()&&!this->checkIsDead()){
            int dam=playptr->chooseskill();
            cout<<endl;
            this -> takeDamage(dam) ;
            cout << "You -> Monster   Damage:" << dam <<endl ;
            cout << "Your health : "<< ((playptr->getCurrentHealth()>=0)?playptr->getCurrentHealth():0) << " / " << "Monster health : " << ((this->getCurrentHealth()>=0)?this->getCurrentHealth():0) <<endl ;
            if(this->checkIsDead()){
                cout << "You beat " << this->getName() << ", Congraduration !" <<endl ;
                cout <<"Now you can get a part of the monster ability!"<<endl;
                char c;
                cout<<"a.health: +"<<this->getMaxHealth()/2<<"\nb.attack : +"<<this->getAttack()/2<<"\nc.defense : +"<<this->getDefense()/2<<endl;
                cin>>c;
                switch (c)
                {
                    case 'a':
                        playptr->increaseStates(this->getMaxHealth()/2,this->getMaxHealth()/2,0,0);
                        break;
                    case 'b':
                        playptr->increaseStates(0,0,this->getAttack()/2,0);
                        break;
                    case 'c':
                        playptr->increaseStates(0,0,0,this->getDefense()/2);
                        break;
                }
                Item treasure=createTreasure();
                cout<<"You get "<<treasure.getName()<<"<"<<treasure.getType()<<">"<<endl;
                playptr->addItem(treasure);
                break;
            }
            playptr->takeDamage(this->getAttack());
            cout << "Monster -> You   Damage:" << this->getAttack() <<endl ;
            cout << "Your health : "<< ((playptr->getCurrentHealth()>=0)?playptr->getCurrentHealth():0) << "/" << "Monster health : " << ((this->getCurrentHealth()>=0)?this->getCurrentHealth():0) <<endl ;
            if(playptr->checkIsDead()){
                cout << "You are killed by the monster ! " <<endl ;
                break;
            }
            if(!retreatornot()){
                playptr->setCurrentRoom(playptr->getPreviousRoom());
                cout<<"Back to Room"<<playptr->getCurrentRoom()->getIndex()<<endl;
                break;
            }
        }
    }
    else if(temp=='b'||temp=='B'){
        this->access();
        triggerEvent(playptr);
    }
    else if(temp=='c'||temp=='C'){
        playptr->setCurrentRoom(playptr->getPreviousRoom());
        cout<<"Back to Room "<<playptr->getCurrentRoom()->getIndex()<<endl;
        return;
    }
    else{
        cout<<"Invalid input"<<endl;
        triggerEvent(playptr);
    }


};

void Monster::access()
{
    showstatus();
}

void Monster::showstatus(){
    cout<<"--------<Monster>--------"<<endl;
    cout<<setw(17)<<"name : "<<setw(10)<<getName()<<endl;
    cout<<setw(17)<<"maxHealth : "<<setw(10)<<getMaxHealth()<<endl;
    cout<<setw(17)<<"currentHealth : "<<setw(10)<<getCurrentHealth()<<endl;
    cout<<setw(17)<<"attack : "<<setw(10)<<getAttack()<<endl;
    cout<<setw(17)<<"defense : "<<setw(10)<<getDefense()<<endl;
}
void Monster::showinventory(){};
