#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "Object.h"
//#include "Player.h"
using namespace std;

//class Player;

class Item: public Object
{
private:
    int health,attack,defense;
    string type;
public:
    Item();
    Item(string,string,int, int, int);

    /* Virtual function that you need to complete    */
    /* In Item, this function should deal with the   */
    /* pick up action. You should add status to the  */
    /* player.                                       */
    void triggerEvent(Object*);

    /* Setter & Getter*/
    int getHealth();
    int getAttack();
    int getDefense();
    string getType();
    void setHealth(int);
    void setAttack(int);
    void setDefense(int);
    void setType(string type);

    /* show item*/
    void showitem();
};

#endif // ITEM_H_INCLUDED
