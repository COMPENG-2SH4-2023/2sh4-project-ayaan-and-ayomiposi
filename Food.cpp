#include "Food.h"

Food::Food(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;

    foodPos.setObjPos(0, 0, 'o');
}

Food::~Food()
{

}

void Food::generateFood(objPosArrayList* blockOff)
{
    int random;
    bool matchflag1 = true;
    bool matchflag2 = false;
    objPos tempBody;

    while (matchflag1==true){
        random = rand() % (mainGameMechsRef->getBoardSizeX());
        for (int k = 0; k < blockOff->getSize(); k++){
            blockOff->getElement(tempBody, k);
            if (tempBody.x == random){
                matchflag2 = true;
            }
        }
        if (matchflag2 == false){
            matchflag1 = false;
        }
    }
    foodPos.x = random;
    matchflag1 = true;
    matchflag2 = false;
        while (matchflag1==true){
        random = rand() % (mainGameMechsRef->getBoardSizeY());
        for (int k = 0; k < blockOff->getSize(); k++){
            blockOff->getElement(tempBody, k);
            if (tempBody.y == random){
                matchflag2 = true;
            }
        }
        if (matchflag2 == false){
            matchflag1 = false;
        }
    }
    foodPos.y = random;
}

void Food::getFoodPos(objPos &returnPos)
{
    returnPos.setObjPos(foodPos.x, foodPos.y, foodPos.symbol);
}