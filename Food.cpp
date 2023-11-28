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
    bool matchflag = false;
    bool unique;
    objPos tempBody;

    while (matchflag == false){
        unique = true;
        random = rand() % (mainGameMechsRef->getBoardSizeX());
        for (int k = 0; k < blockOff->getSize(); k++){
            blockOff->getElement(tempBody, k);
            if (tempBody.x == random){
                unique = false;
            }
        }
        if (unique == true){
            matchflag = true;
        }
    }
    foodPos.x = random;
    matchflag = false;

    while (matchflag == false){
        unique = true;
        random = rand() % (mainGameMechsRef->getBoardSizeY());
        for (int k = 0; k < blockOff->getSize(); k++){
            blockOff->getElement(tempBody, k);
            if (tempBody.y == random){
                unique = false;
            }
        }
        if (unique == true){
            matchflag = true;
        }
    }
    foodPos.y = random;
}

void Food::getFoodPos(objPos &returnPos)
{
    returnPos.setObjPos(foodPos.x, foodPos.y, foodPos.symbol);
}