#include "Object.h"
#include "Room.h"
#include <vector>
#include <algorithm>
#include "tool.h"
#include "NPC.h"

using namespace std;

Room::Room(){}


Room::Room(int index,vector<Object*> objectlist)
{
    this->index=index;
    objects.assign(objectlist.begin(),objectlist.end());
}

void Room::popObject(Object* obj){
    int pos=findpos(objects,obj->getName());
    if(pos!=-1)
    {
        delete objects[pos];
        objects.erase(objects.begin()+pos);
    }
}

void Room::setUpRoom(Room* roomptr){
    upRoom=roomptr;
}

void Room::setDownRoom(Room* roomptr){
    downRoom=roomptr;
}

void Room::setLeftRoom(Room* roomptr){
    leftRoom=roomptr;
}

void Room::setRightRoom(Room* roomptr){
    rightRoom=roomptr;
}

void Room::setIndex(int index){
    this->index=index;
}

void Room::setObjects(vector<Object*> objectlist){
    if(!objectlist.empty())
        objects.assign(objectlist.begin(),objectlist.end());
}

int Room::getIndex(){
    return index;
}

vector<Object*> Room::getObjects(){
    return objects;
}

Room* Room::getUpRoom(){
    return upRoom;
}

Room* Room::getDownRoom(){
    return downRoom;
}

Room* Room::getLeftRoom(){
    return leftRoom;
}

Room* Room::getRightRoom(){
    return rightRoom;
}

void Room::showallobject(){
    if(objects.empty())
        cout<<"there is no object in the room"<<endl;

    cout<<"the follow is the object in the room"<<endl;

    for(int i=0;i<objects.size();i++){
        cout<<"Name: "<<objects[i]->getName()<<endl;
        cout<<"---------<object list>---------"<<endl;
        objects[i]->access();
    }
}

char Room::tagjudge(Object* objptr){
    char chr;
    cout << "What do you want to do?\n" ;
    if(objptr->getTag()=="Monster"){
        cout << "a.Eenter the monster territory ?" <<endl ;
        cout<<"b.Retreat" <<endl ;
    }
    else if(objptr->getTag()=="NPC"){
        cout << "Interact with the NPC ? " <<endl ;
        cout<< "a.Yes !"<<endl;
        cout<<"b.No,negelect the npc"<<endl;
    }
    else if(objptr->getTag()=="CHEST"){
        cout << "a.Open the chest" <<endl ;
        cout << "b.Abandom the chest"<<endl;
    }
    cin>>chr;
    while(chr!='a'&&chr!='b'){
        cout<<"Invalid input"<<endl;
        cout<<"please type in again(a/b)"<<endl;
        cin>>chr;
    }
    if(chr=='a')
        return chr;
    else if(chr=='b'&&objptr->getTag()=="Monster")
        return 'b';
    else if(chr=='b'&&(objptr->getTag()=="NPC"||objptr->getTag()=="CHEST"))
        return 'B';
}
