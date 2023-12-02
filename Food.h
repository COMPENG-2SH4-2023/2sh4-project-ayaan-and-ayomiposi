#ifndef FOOD_H
#define FOOD_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "MacUILib.h"
#include <time.h>

class Food
{
    private:
        objPosArrayList *foodBucket;     

        GameMechs* mainGameMechsRef;
    public:
        Food(GameMechs* thisGMRef);
        ~Food();

        void generateFood(objPosArrayList* blockOff);
        objPosArrayList* getFoodPos();
};

#endif