#include "Player.h"
#include "Room.h"
#include "Dungen.h"
#include "Object.h"
#include "tool.h"
#include "Player.h"
#include "time.h"
#include <iostream>
#include <cstring>
#include <vector>

using namespace std ;

void Dungeon::runDungeor(){
    Dungeon backdun=(*this);
    cout<<"Hello "<<player->getName()<<" Welcome to Dungeon !"<<endl;

    char c;
    if(chooseaction())
        cout<<"victory !"<<endl;
    else
        cout<<"game over >_< "<<endl;
    cout<<"try again ? (y/n) "<<endl;
    cin>>c;
    if(c=='y'){
        backdun.runDungeor();
    }

    cout<<"thank you!"<<endl;
}

vector<Room> Dungeon::getGameroom()const{
    return gameroom;
}

Player *Dungeon::getPlayer()const{
    return player;
}

Room *Dungeon::getExitroom()const{
    return exitroom;
}

int Dungeon::getNumberofcollectItem()const{
    return numberof_collected_item;
}

int Dungeon::getNumberofkilledMonster()const{
    return numberof_killed_monster;
}

int Dungeon::getCurrentkilledMonster()const{
    return current_killed_monster;
}

Dungeon::Dungeon(const Dungeon &dun2){
    numberof_collected_item=getNumberofcollectItem();
    gameroom=dun2.getGameroom();
    player= new Player(dun2.getPlayer()->getName(),dun2.getPlayer()->getCurrentHealth(),dun2.getPlayer()->getAttack(),dun2.getPlayer()->getDefense());
    player->setCurrentRoom(dun2.getPlayer()->getCurrentRoom());
    player->setPreviousRoom(dun2.getPlayer()->getPreviousRoom());
    player->setInventory(dun2.getPlayer()->getInventory());
    exitroom=dun2.getExitroom();
}

Dungeon::Dungeon(int i){
    srand(unsigned(time(NULL)));
    int exitindex;
    cout<<"Do you want to load previous data ?\nA.Yes\nB.No,Start a new game"<<endl;
    char *filename=new char[100];
    char c;
    cin>>c;
    cin.get();
    if(c=='a'||c=='A'){
        cout<<"please input the file name"<<endl;
        cin.getline(filename,100);
        cout<<filename<<endl;
        ifstream infile(filename);
        player=reading(player,gameroom,exitindex,numberof_collected_item,current_killed_monster,numberof_killed_monster,filename,infile);

    }
    else if(c=='b'||c=='B'){
        filename="backup.txt";
        ifstream infile(filename);
        player=reading(player,gameroom,exitindex,numberof_collected_item,current_killed_monster,numberof_killed_monster,filename,infile);
        cout<<"please input the player name"<<endl;
        string str;
        cin>>str;
        player->setName(str);
    }

    exitroom=&gameroom[exitindex];
}


Dungeon::Dungeon(){}

void Dungeon::showinformation(){
    cout<<"A.show the backpack"<<endl
        <<"B.the state of the task"<<endl
        <<"C.show the current room"<<endl
        <<"D.show current status"<<endl;
    char tmp;
    cin>>tmp;
    switch(tmp)
    {
        case 'a' : case 'A' : player->access(); break ;
        case 'b' : case 'B' : showTasklist();break;
        case 'c' : case 'C' : cout<<"------<Position>-------"
                                  <<endl<< "You are in the Room"
                                  << player->getCurrentRoom()->getIndex() << endl ;break;
        case 'd' : case 'D' :player->showstatus();
    }

}

bool Dungeon::chooseaction(){
    char tmp ;
    bool conti  = checkgamelogic();
    while(conti){
        cout << "What do you want to do ?" << endl ;
        cout << "A.Move\nB.Using item\nC.Search the room\nD.Show information\nE.Save file" << endl ;
        cin >> tmp ;
        switch(tmp){
            case 'a' : case 'A' : walk(); break ;
            case 'b' : case 'B' : player->usingItem();break;
            case 'c' : case 'C' : trigger(player->getCurrentRoom()); break;
            case 'd' : case 'D' : showinformation();break;
            case 'e' : case 'E' : backup(*this);break;
            default : cout<<" Invalid input " << endl; conti = false ;break;
        }
        conti=checkgamelogic();
    }
    if(task_findexit()&&task_kill_monster()&&task_collectitem()){
        showTasklist();
        cout<<"Congradulation you finish all the task !!"<<endl;
    }
    if(player->getCurrentHealth()<=0)
        return false;
    else
        return true;
}

bool Dungeon::task_findexit(){
    static int idx=0;
    if(player->getCurrentRoom()==exitroom){
        return true;
    }
    else{
         return false;
    }

}

bool Dungeon::task_kill_monster(){
    if(this->getCurrentkilledMonster()>=this->getNumberofkilledMonster()){
         return true;
    }
    else{
        return false;
    }
}

bool Dungeon::task_collectitem(){
    if(player->countitem()>=numberof_collected_item){
        return true;
    }
    else{
        return false;
    }

}

void Dungeon::showTasklist(){
    cout<<"------<Task1>-------"<<endl;
    cout<<"Get to the exit : "<<((player->getCurrentRoom()==exitroom)?"Yes":"No")<<endl;
    cout<<"------<Task2>-------"<<endl;
    cout<<"Collect Item :"<<player->countitem()<<"/"<<numberof_collected_item<<endl;
    cout<<"------<Task3>-------"<<endl;
    cout<<"Killed Monster :"<<current_killed_monster<<"/"<<numberof_killed_monster<<endl;

}

void Dungeon::walk(){
    if(player->getCurrentRoom()->getUpRoom() != NULL ){
        cout << "U. Go up into Room" << player->getCurrentRoom()->getUpRoom()->getIndex() << " \n" ;
    }
    if(player->getCurrentRoom()->getDownRoom() != NULL ){
        cout << "D. Go down into Room" << player->getCurrentRoom()->getDownRoom()->getIndex() << " \n" ;
    }
    if(player->getCurrentRoom()->getLeftRoom() != NULL ){
        cout << "L. Go left into Room" << player->getCurrentRoom()->getLeftRoom()->getIndex() << " \n" ;
    }
    if(player->getCurrentRoom()->getRightRoom() != NULL ){
        cout << "R. Go right into Room" << player->getCurrentRoom()->getRightRoom()->getIndex() << " \n" ;
    }

    char tmp ;
    cin>>tmp;
    switch(tmp){
        case 'u' : case 'U' :   player->setPreviousRoom(player->getCurrentRoom());
                                player->setCurrentRoom(player->getCurrentRoom()->getUpRoom());
                                break;
        case 'd' : case 'D' :   player->setPreviousRoom(player->getCurrentRoom());
                                player->setCurrentRoom(player->getCurrentRoom()->getDownRoom());
                                break;
        case 'l' : case 'L' :   player->setPreviousRoom(player->getCurrentRoom());
                                player->setCurrentRoom(player->getCurrentRoom()->getLeftRoom());
                                break;
        case 'r' : case 'R' :   player->setPreviousRoom(player->getCurrentRoom());
                                player->setCurrentRoom(player->getCurrentRoom()->getRightRoom());
                                break;
        default  : cout<<"Invalid input"<<endl;
    }
    if(!task_findexit())
        cout << "Enter the Room" << player->getCurrentRoom()->getIndex() << endl ;
    else{
        cout<< "You may found the exit! Check you task state!"<<endl;
    }

    if(player->getCurrentRoom()->getObjects().empty()){
        return;
    }
    else if(player->getCurrentRoom()->objects[0]->getTag()=="Monster"){
        trigger(player->getCurrentRoom());
    }
};



bool Dungeon::checkgamelogic(){
    bool flag=true;
    if((task_collectitem()&&task_findexit()&&task_kill_monster())||player->getCurrentHealth()<=0)
        flag=false;
    return flag;

}

void Dungeon::trigger(Room *tmpptr){
    if(tmpptr->getObjects().empty()){
        cout<<"There is nothing in the Room"<<endl;
        return;
    }
    cout << "There is a <"<<tmpptr->objects[0]->getTag() << "> is in this room." << endl;
    char tmp ;
    tmp = tmpptr->tagjudge(tmpptr->objects[0]);
    if(tmp=='a'){
        GameCharacter *gamecharptr=static_cast<GameCharacter*>(tmpptr->objects[0]);
        gamecharptr->triggerEvent(player);
        if(gamecharptr->checkIsDead()){
            if(gamecharptr->getTag()=="Monster")
                current_killed_monster++;
            player->getCurrentRoom()->popObject(gamecharptr);
        }
    };
    if(tmp=='b'){
        this->player->setCurrentRoom(player->getPreviousRoom());
        cout<<"back to Room"<<player->getCurrentRoom()->getIndex()<<endl;
    };
    if(tmp=='B'){
            return;
    }
}
