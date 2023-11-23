#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = NONE;

    // more actions to be included
    playerPos.setObjPos(8, 3, '*');
}


Player::~Player()
{
    // delete any heap members here
}

void Player::getPlayerPos(objPos &returnPos)
{
    // return the reference to the playerPos arrray list
    returnPos.setObjPos(playerPos.x, playerPos.y, playerPos.symbol);
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
    if (myDir == UP){
        playerPos.y--;
        if (playerPos.y < 0){
            playerPos.y = (mainGameMechsRef->getBoardSizeY())-1; // need to get board size
        }
    }
    if (myDir == LEFT){
        playerPos.x--;
        if (playerPos.x < 0){
            playerPos.x = (mainGameMechsRef->getBoardSizeX())-1;
        }
    }
    if (myDir == RIGHT){
        playerPos.x++;
        if (playerPos.x > (mainGameMechsRef->getBoardSizeX())-1){
            playerPos.x = 0;
        }
    }
    if (myDir == DOWN){
        playerPos.y++;
        if (playerPos.y > (mainGameMechsRef->getBoardSizeY())-1){
            playerPos.y = 0;
        }
    }
    if (myDir != NONE){
        /*
        int i;
        for (i=2; i < 16; i++){
            disp[1][i] = ' ';
        }
        for (i = 0; i < 5; i++) {
            disp[itemBin[i]->y][itemBin[i]->x] = itemBin[i]->symbol;
        }
        */
    }
}

