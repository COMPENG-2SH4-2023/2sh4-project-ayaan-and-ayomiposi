#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "Food.h"
#include "objPosArrayList.h"

class Player
{
    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, NONE};  // This is the direction state

        Player(GameMechs* thisGMRef, Food* foodRef);
        ~Player();

        objPosArrayList* getPlayerPos();
        void updatePlayerDir();
        void movePlayer();
        bool checkFoodConsuption();
        void increasePlayerLength();
        bool checkSelfCollision();

    private:
        objPosArrayList *playerPosList;       
        enum Dir myDir;

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
        Food* mainFoodRef;
};

#endif