#include "Player.h"


Player::Player(GameMechs* thisGMRef, Food* foodRef)
{
    mainGameMechsRef = thisGMRef;
    mainFoodRef = foodRef;

    myDir = NONE;

    // more actions to be included
    objPos tempPos;
    tempPos.setObjPos(8, 3, '@');

    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos);

    //playerPosList->insertHead(tempPos);
    //playerPosList->insertHead(tempPos);
    //playerPosList->insertHead(tempPos);
    //playerPosList->insertHead(tempPos);
}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos()
{
    // return the reference to the playerPos arrray list
    return playerPosList;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic 
    char input = mainGameMechsRef->getInput();
    switch(input){
        case 'W':
        case 'w':
            if (myDir != DOWN){
                myDir = UP;
            }
            break;
        case 'A':
        case 'a':
            if (myDir != RIGHT){
                myDir = LEFT;
            }
            break;
        case 'S':
        case 's':
            if (myDir != UP){
                myDir = DOWN;
            }
            break;
        case 'D':
        case 'd':
            if (myDir != LEFT){
                myDir = RIGHT;
            }
            break;
        default:
            break;
    }
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    objPos currHead;
    playerPosList->getHeadElement(currHead);

    if (myDir == UP){
        currHead.y--;
        if (currHead.y < 0){
            currHead.y = (mainGameMechsRef->getBoardSizeY())-1; // need to get board size
        }
    }
    if (myDir == LEFT){
        currHead.x--;
        if (currHead.x < 0){
            currHead.x = (mainGameMechsRef->getBoardSizeX())-1;
        }
    }
    if (myDir == RIGHT){
        currHead.x++;
        if (currHead.x > (mainGameMechsRef->getBoardSizeX())-1){
            currHead.x = 0;
        }
    }
    if (myDir == DOWN){
        currHead.y++;
        if (currHead.y > (mainGameMechsRef->getBoardSizeY())-1){
            currHead.y = 0;
        }
    }
    if (myDir != NONE){
        mainGameMechsRef->setStartFlag();
    }

    playerPosList->insertHead(currHead);

    playerPosList->removeTail();

    if (checkSelfCollision() == true)
        mainGameMechsRef->setLoseFlag();
}

bool Player::checkFoodConsuption()
{
    objPos currHead;
    objPos foodpos;
    playerPosList->getHeadElement(currHead);
    mainFoodRef->getFoodPos(foodpos);
    return (foodpos.x==currHead.x&&foodpos.y==currHead.y);
}

void Player::increasePlayerLength()
{
    objPos currHead;
    playerPosList->getHeadElement(currHead);
    playerPosList->insertTail(currHead);
}

bool Player::checkSelfCollision() 
{
    objPos currHead;
    objPos tempBody;
    playerPosList->getHeadElement(currHead);
    for (int k = 1; k < playerPosList->getSize(); k++){
        playerPosList->getElement(tempBody, k);
        if (currHead.isPosEqual(&tempBody))
            return true;
    }
    return false;
}
