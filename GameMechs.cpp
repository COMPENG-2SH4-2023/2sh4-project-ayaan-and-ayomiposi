#include "GameMechs.h"
#include "MacUILib.h"
#include <cstdlib>

// Game mechanism constructor i.e. default game mode
GameMechs::GameMechs()
{
    input = 0; //no input at this stage
    exitFlag = false;
    startflag = false; // Custom //
    winflag = false; // Custom //
    boardSizeX = 30; //default board size
    boardSizeY = 15;
    loseFlag = false;
}

// Default mode, but with specified board size inputs allowed
GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0; 
    exitFlag = false;
    startflag = false; // Custom //
    winflag = false; // Custom //
    boardSizeX = boardX;
    boardSizeY = boardY;
    loseFlag = false;
}

bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;
}

char GameMechs::getInput()
{
    if(MacUILib_hasChar()) 
    {
        input = MacUILib_getChar();
        if (input == 27){
            setExitTrue();
        }
    }
    return input;
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}

void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::setStartFlag() // Custom //
{
    startflag = true;
}

bool GameMechs::getStartFlagStatus() // Custom //
{
    return startflag;
}

void GameMechs::setWinFlag() // Custom //
{
    winflag = true;
}

bool GameMechs::getWinFlagStatus() // Custom //
{
    return winflag;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = '\0';
}

int GameMechs::getScore()
{
    return score;
}

void GameMechs::incrementScore(int x)
{
    score += x;  
}