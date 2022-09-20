#include<vector>
#include<string>
#include<cstddef>
#include<iomanip>
#include "tool.h"
#include "Object.h"
#include "NPC.h"
#include "tool.h"
#include "Item.h"
#include "Monster.h"
#include "Chest.h"
#include "Dungen.h"
#include <fstream>

using namespace std;

ifstream infile("setting.txt");

int getnumberfrom_ifstream()
{
    int idx;
    infile>>idx;
    return idx;
}

int findpos2(vector<Item> &ll,string type)
{
    int pos=-1;
    for(int i=0;i<ll.size();i++)
    {
        if(ll[i].getType()==type)
            pos=i;
    }
    return pos;
}

int findpos(vector<Object*> &inventory,string s)
{
    int pos=-1;
    for(int i=0;i<inventory.size();i++)
    {
        if(inventory[i]->getName()==s)
            pos=i;
    }
    return pos;
}



void traverseroom(vector<Room> roomlist)
{
    for(int i=0;i<(int)roomlist.size();i++)
    {
        cout<<"------------< Room-"<<roomlist[i].getIndex()<<" >-----------"<<endl;
        roomlist[i].showallobject();
        cout << endl;
    }
}

void backup(Dungeon &dun)
{
    ofstream outfile("backupfile.txt");
    if(outfile.bad()){
         cout<<"Something Wrong! Can't save the file"<<endl;
         return;
    }
    /*save player*/
    saveplayer(dun.getPlayer(),dun.getGameroom(),outfile);
    outfile<<dun.getExitroom()->getIndex()<<" "<<dun.getNumberofcollectItem()<<" "<<dun.getCurrentkilledMonster()<<" "<<dun.getNumberofkilledMonster()<<endl;
    cout<<"Finish back up"<<endl;
}

void saveplayer(Player *player,vector<Room> gameroom,ofstream &outfile)
{
        outfile<<gameroom.size()<<endl;
    for(int i=0;i<gameroom.size();i++)
    {
        outfile<<  i  <<" "<<gameroom[i].objects.size()<<endl;
        outfile<<((gameroom[i].getUpRoom()!=NULL)?gameroom[i].getUpRoom()->getIndex():-1)<<" ";
        outfile<<((gameroom[i].getDownRoom()!=NULL)?gameroom[i].getDownRoom()->getIndex():-1)<<" ";
        outfile<<((gameroom[i].getLeftRoom()!=NULL)?gameroom[i].getLeftRoom()->getIndex():-1)<<" ";
        outfile<<((gameroom[i].getRightRoom()!=NULL)?gameroom[i].getRightRoom()->getIndex():-1)<<" ";
        outfile<<endl;
        for(int j=0;j<gameroom[i].objects.size();j++)
        {
            if(gameroom[i].objects.empty())
            {
                cout<<"break"<<endl;
                break;
            }

            string tagofobj=gameroom[i].objects[j]->getTag();

            if(tagofobj=="Monster")
            {
                Monster *monptr=static_cast<Monster *>(gameroom[i].objects[j]);
                outfile<<monptr->getTag()<<" "<<monptr->getName()<<" "<<monptr->getMaxHealth()<<" "<<monptr->getCurrentHealth()<<" "<<monptr->getAttack()<<" "<<monptr->getDefense()<<" "<<endl;
            }
            else if(tagofobj=="NPC")
            {
                NPC *npcptr=static_cast<NPC*>(gameroom[i].objects[j]);
                outfile<<npcptr->getTag()<<" "<<npcptr->getName()<<" "<<npcptr->getScript()<<" "<<npcptr->getCommodity().size()<<endl;

                vector<Item> outvec=npcptr->getCommodity();

                for(int i=0;i<outvec.size();i++){
                    outfile<<outvec[i].getName()<<" "<<outvec[i].getType()<<" "<<outvec[i].getHealth()<<" "<<outvec[i].getAttack()<<" "<<outvec[i].getDefense()<<endl;
                }

            }
            else if(tagofobj=="CHEST")
            {
                Chest *chestptr=static_cast<Chest*>(gameroom[i].objects[j]);
                outfile<<chestptr->getTag()<<" "<<chestptr->getName()<<" "
                       <<chestptr->getScript()<<'!'<<endl
                       <<((chestptr->getisbadchest())?0:1)<<" "<<chestptr->getTreasure().size()<<endl;


                vector<Item> outvec=chestptr->getTreasure();

                for(int i=0;i<outvec.size();i++){
                    outfile<<outvec[i].getName()<<" "<<outvec[i].getType()<<" "<<outvec[i].getHealth()<<" "<<outvec[i].getAttack()<<" "<<outvec[i].getDefense()<<endl;
                }

            }
        }
    }
    outfile<<player->getName()<<" "<<player->getMaxHealth()<<" "<<player->getCurrentHealth()<<" "
           <<player->getAttack()<<" "<<player->getDefense()<<" "
           <<((player->getCurrentRoom()!=NULL)?player->getCurrentRoom()->getIndex():-1)<<" "
           <<((player->getPreviousRoom()!=NULL)?player->getPreviousRoom()->getIndex():-1)<<" "<<player->getInventory().size()<<endl;

    vector<Item> outvec=player->getInventory();

    for(int i=0;i<outvec.size();i++){
        outfile<<outvec[i].getName()<<" "<<outvec[i].getType()<<" "<<outvec[i].getHealth()<<" "<<outvec[i].getAttack()<<" "<<outvec[i].getDefense()<<endl;
    }
}



Player* reading(Player *playptr,vector<Room> &room,int &exit,int &numberofcollect,int &currentkilled,int &numberofkilled,char *filename,ifstream &infile)
{
    int numberofroom;
    infile>>numberofroom;
    vector<Room> room2(numberofroom);
    for(int i=0;i<numberofroom;i++)
    {
        Room r;
        room.push_back(r);
    }
    for(int i=0;i<room.size();i++)
    {
        int numberofobj;
        infile>>room[i].index;
        infile>>numberofobj;;
        int u,d,l,r;
        infile >> u >> d >> l >> r;
        if(u>=0)
            room[i].upRoom = &room[u];
        else
            room[i].upRoom = NULL;
        if(d>=0)
            room[i].downRoom = &room[d];
        else
            room[i].downRoom = NULL;
        if(l>=0)
            room[i].leftRoom = &room[l];
        else
            room[i].leftRoom = NULL;
        if(r>=0)
            room[i].rightRoom = &room[r];
        else
            room[i].rightRoom = NULL;

        if(numberofobj==0){
            vector<Object *>obj(0);
            room[i].setObjects(obj);
        }
        else{
            room[i].setObjects(setroomobject(infile,numberofobj));
        }
    }

    /*player*/
    string name;
    int maxh,curh,att,def,inventory_num,current,previous;
    infile>>name>>maxh>>curh>>att>>def>>current>>previous>>inventory_num;
    playptr=new Player(name,maxh,att,def);
    playptr->setCurrentHealth(curh);
    if(current!=-1){
        playptr->setCurrentRoom(&room[current]);
    }
    else{
        playptr->setCurrentRoom(NULL);
    }
    if(previous!=-1){
        playptr->setPreviousRoom(&room[previous]);
    }
    else{
        playptr->setPreviousRoom(NULL);
    }

    vector <Item> inventory;
    for(int i=0;i<inventory_num;i++)
    {
        string itemname,type;
        int att,def,health;
        infile>>itemname>>type>>health>>att>>def;
        Item it(itemname,type,health,att,def);
        inventory.push_back(it);
    }
    playptr->setInventory(inventory);
    infile>>exit>>numberofcollect>>currentkilled>>numberofkilled;
    return playptr;
}

vector<Object *> setroomobject(ifstream &infile,int numberofobj)
{
    vector<Object *>objectlist;
    string objtag;
    string name;
    for(int i=0;i<numberofobj;i++)
    {
        infile>>objtag>>name;
        if(objtag=="NPC")
        {
            string script;
            int numberofinventory;
            vector <Item> commoditylist;
            infile>>script;
            infile>>numberofinventory;
            for(int i=0;i<numberofinventory;i++)
            {
                string itemname,type;
                int att,def,health;
                infile>>itemname>>type>>health>>att>>def;
                Item it(itemname,type,health,att,def);
                commoditylist.push_back(it);
            }
            NPC *npcptr=new NPC(name,script,commoditylist);
            objectlist.push_back(npcptr);
        }
        if(objtag=="CHEST")
        {
            string script;
            int numberofinventory,goodornot;
            bool tag;
            getline(infile,script,'!');
            infile>>goodornot;
            if(goodornot==0)tag=true;
            else tag=false;
            infile>>numberofinventory;
            vector <Item> commoditylist;
            for(int i=0;i<numberofinventory;i++)
            {
                string itemname,type;
                int att,def,health;
                infile>>itemname>>type>>health>>att>>def;
                Item it(itemname,type,health,att,def);
                commoditylist.push_back(it);
            }
            Chest *chestptr=new Chest(name,script,commoditylist,tag);
            objectlist.push_back(chestptr);
        }
        if(objtag=="Monster")
        {
            int maxh,curh,att,def;
            infile>>maxh>>curh>>att>>def;
            Monster *monsptr=new Monster(name,maxh,att,def);
            monsptr->setCurrentHealth(curh);
            objectlist.push_back(monsptr);
        }
    }
    return objectlist;
}
