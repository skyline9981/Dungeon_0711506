#ifndef DUNGEN_H_INCLUDED
#define DUNGEN_H_INCLUDED
#include "Player.h"
#include "Room.h"
#include "Object.h"

using namespace std ;

class Dungeon {
private:
    Player *player;
    Room *exitroom;
    vector <Room> gameroom;
    int numberof_collected_item;
    int numberof_killed_monster;
    int current_killed_monster;
public:
    Dungeon();
    Dungeon(int);
    Dungeon(const Dungeon&);
    bool chooseaction();
    void walk();
    void trigger(Room *);
    void runDungeor();
    void showTasklist();
    void showinformation();
    bool checkgamelogic();
    bool task_findexit();
    bool task_collectitem();
    bool task_kill_monster();

    /*  Getter   */
    vector<Room> getGameroom()const;
    Player *getPlayer()const;
    Room *getExitroom()const;
    int getNumberofcollectItem()const;
    int getNumberofkilledMonster()const;
    int getCurrentkilledMonster()const;

};

#endif // DUNGEN_H_INCLUDED
