#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"

using namespace std;

#define DELAY_CONST 100000
// global variables
char disp[8][19] = {
    "                  ",
    "  WASD to start!  ",
    "                  ",
    "                  ",
    "                  ",
    "                  ",
    "                  ",
    "                  "
};
GameMechs* gmpointer;
Player* myPlayer;



bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(exitFlag == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();
    gmpointer = new GameMechs(18,8);
    myPlayer = new Player(gmpointer);

    exitFlag = false;
}

void GetInput(void)
{
   //Once get input delete start screen
   gmpointer->getInput();
}

void RunLogic(void)
{
    // Clear previous player position
    objPos currentPos;
    myPlayer->getPlayerPos(currentPos); //to get the players current position
    disp[currentPos.y][currentPos.x] = ' ';

    // display new position
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
    myPlayer->getPlayerPos(currentPos); //to get the players current position
    disp[currentPos.y][currentPos.x] = currentPos.symbol;
}

void DrawScreen(void)
{
    MacUILib_clearScreen();    
    MacUILib_printf("  ####################\n");

    // Print the game board
    for (int i = 0; i < 8; i++) {
        MacUILib_printf("  #%s#\n", disp[i]);
    }

	MacUILib_printf("  ####################\n");
    // Add lose screen statement
    objPos currentPos;
    myPlayer->getPlayerPos(currentPos); //to get the players current position

    MacUILib_printf("The Boardsize is %dx%d, The Player Position is (%d, %d) %c", 
                    gmpointer->getBoardSizeX(), gmpointer->getBoardSizeY(),
                    currentPos.x, currentPos.y, currentPos.symbol);
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
  
    MacUILib_uninit();
}
