#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "GameCharacter.h"
#include "Player.h"
#include "Object.h"

using namespace std;
class Monster: public GameCharacter
{
private:
public:
    Monster();
    Monster(string,int,int,int);
    //Item treasure ;
    /* Virtual function that you need to complete   */
    /* In Monster, this function should deal with   */
    /* the combat system.                           */
    void triggerEvent(Object*);
    Item createTreasure();
    bool retreatornot();
    //virtual
    void showstatus();
    void showinventory();
    void access();
};


#endif // ENEMY_H_INCLUDED
