#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "GameCharacter.h"
#include "Room.h"
#include "Item.h"

using namespace std;

class Item;

class Player: public GameCharacter
{
private:
    Room* currentRoom;
    Room* previousRoom;
    vector<Item> inventory;
public:
    Player();
    Player(string,int,int,int);
    int countitem();
    void addItem(Item);
    void increaseStates(int,int,int,int);
    void changeRoom(Room*);

    /* Virtual function that you need to complete   */
    /* In Player, this function should show the     */
    /* status of player.                            */

    /* Setter & Getter*/
    void setCurrentRoom(Room*);
    void setPreviousRoom(Room*);
    void popitem(int index);
    void usingItem();
    void wear_gear(int index);
    void using_recovery(int index);
    void setInventory(vector<Item>);
    Room* getCurrentRoom()const;
    Room* getPreviousRoom()const;
    vector<Item> getInventory()const;
    int chooseskill();

    /* showstatus inhertance from gamecharacter class*/
    void showstatus();
    void showinventory();
    void access();
};

#endif // PLAYER_H_INCLUDED
