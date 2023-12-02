#include "Player.h"


Player::Player(GameMechs* thisGMRef, Food* foodRef)
{
    mainGameMechsRef = thisGMRef;
    mainFoodRef = foodRef;

    myDir = NONE;

    objPos tempPos;
    tempPos.setObjPos(8, 3, '@');

    playerPosList = new objPosArrayList(); // Creating space on the heap
    playerPosList->insertHead(tempPos);
}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos()
{
    // return the reference to the playerPos array list
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
            currHead.y = (mainGameMechsRef->getBoardSizeY())-1; 
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
    if (myDir != NONE){ // If the player starts moving the game has started
        mainGameMechsRef->setStartFlag();
    }

    // When player moves, add new head and remove tail to maintain snake length
    playerPosList->insertHead(currHead);
    playerPosList->removeTail();

    // If player collides with itself, game is lost
    if ((checkSelfCollision() == true) && (mainGameMechsRef->getWinFlagStatus() != true)){
        mainGameMechsRef->setLoseFlag();
    }
}

int Player::checkFoodConsuption()
{
    // returns 0 if no collision, 1, if collision with regular food, 2 if special food
    objPos currHead;
    objPos foodpos;
    objPosArrayList* foodbucketlist = mainFoodRef->getFoodPos();
    playerPosList->getHeadElement(currHead);
    for (int i = 0; i < foodbucketlist->getSize(); i++){
        foodbucketlist->getElement(foodpos, i);
        if ((foodpos.x==currHead.x)&&(foodpos.y==currHead.y)){
            if (foodpos.symbol == '$'){
                return 2;
            } else {
                return 1;
            }

        }
    }
    return 0;
}

void Player::increasePlayerLength(int x)
{
    // Will increase player length by specified amount
    objPos currHead;
    playerPosList->getHeadElement(currHead);
    for (int i = 0; i < x; i++){
        playerPosList->insertTail(currHead);
    }
}

bool Player::checkSelfCollision() 
{   
    // Check if head and tail are in the same position
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
