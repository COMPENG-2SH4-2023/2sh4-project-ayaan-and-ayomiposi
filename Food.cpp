#include "Food.h"

Food::Food(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;

    foodPos.setObjPos(0, 0, 'o');
}

Food::~Food()
{

}

void Food::generateFood(objPos blockOff)
{
    //if (input == 'g'){ // for debugging purposes
        int xexc = blockOff.x;
        int yexc = blockOff.y;
        int random;
        bool matchflag = false;

        while (matchflag==false){
            random = rand() % (mainGameMechsRef->getBoardSizeX());
            if (random != xexc){
                matchflag = true;
            }
        }
        foodPos.x = random;
        matchflag = false;
        while (matchflag==false){
            random = rand() % (mainGameMechsRef->getBoardSizeY());
            if (random != yexc){
                matchflag = true;
            }
        }
        foodPos.y = random;
    //}
}

void Food::getFoodPos(objPos &returnPos)
{
    returnPos.setObjPos(foodPos.x, foodPos.y, foodPos.symbol);
}