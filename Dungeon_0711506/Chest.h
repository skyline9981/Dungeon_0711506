#ifndef CHEST_H_INCLUDED
#define CHEST_H_INCLUDED
#include "GameCharacter.h"
#include "Item.h"
#include "Object.h"
#include "Player.h"
#include <vector>

using namespace std;

class Chest :public GameCharacter
{
private:
    string script;
    vector<Item> treasure;
    bool isbadchest;
public:
    Chest();
    Chest(string, string,vector<Item>&,bool);

    /*Setter & Getter*/
    string getScript();
    vector<Item> getTreasure();
    bool getisbadchest();
    void setScript(string);
    void setTreasure(vector<Item>);
    void setIsbadchest(bool);
    /*virtual function*/
    void triggerEvent(Object *);
    void showinventory();
    void showstatus();
    void access();
};

#endif // CHEST_H_INCLUDED
