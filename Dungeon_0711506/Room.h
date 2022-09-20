#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "Object.h"

using namespace std;


class Room
{
public:
    Room* upRoom;
    Room* downRoom;
    Room* leftRoom;
    Room* rightRoom;
    int index;
    vector<Object*> objects; /*contain 1 or multiple objects, including monster, npc, etc*/

    Room();
    Room(int, vector<Object*>);
    void popObject(Object*); /*pop out the specific object, used when the interaction is done*/

    /* Setter & Getter*/
    void setUpRoom(Room*);
    void setDownRoom(Room*);
    void setLeftRoom(Room*);
    void setRightRoom(Room*);
    void setIndex(int);
    void setObjects(vector<Object*>);
    int getIndex();
    vector<Object*> getObjects();
    Room* getUpRoom();
    Room* getDownRoom();
    Room* getLeftRoom();
    Room* getRightRoom();
    char tagjudge(Object* objptr);

    void showallobject();

};

#endif // ROOM_H_INCLUDED
