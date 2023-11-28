#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "Food.h"
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
int hasrun = 0;
GameMechs* gmpointer;
Player* myPlayer;
Food* myFood; // test food item


void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(gmpointer->getExitFlagStatus() == false)  
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
    myFood = new Food(gmpointer);
    myPlayer = new Player(gmpointer, myFood);
    

}

void GetInput(void)
{
   //Once get input delete start screen
   gmpointer->getInput();
}

void RunLogic(void)
{
    objPos foodpos;
    myFood->getFoodPos(foodpos);
    objPosArrayList* playerBody =  myPlayer->getPlayerPos();
    
    // Clear start screen and generate first food
    if (hasrun == 0 && gmpointer->getStartFlagStatus() == true){
        for (int i = 2; i < 16; i++){
            disp[1][i] = ' ';
        }
        /// ISSUE -- generates the same inital position everytime///
        ///             might be a seeding issue                 ///
        /// ISSUE -- randomly stops -- gets stuck in loop        ///
        
        myFood->generateFood(playerBody); // generate a new position 
        myFood->getFoodPos(foodpos); // get the new position 
        disp[foodpos.y][foodpos.x] = foodpos.symbol; // display that new position
        hasrun = 1;
    }
    // Clear previous player position
    objPos tempBody;
    for (int k = 0; k < playerBody->getSize(); k++){
        playerBody->getElement(tempBody, k);
        disp[tempBody.y][tempBody.x] = ' ';
    }

    // display new position
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
    if (myPlayer->checkFoodConsuption()){
        gmpointer->incrementScore();
        myPlayer->increasePlayerLength();

        disp[foodpos.y][foodpos.x] = ' '; // clear the current positon
        myFood->generateFood(playerBody); // generate a new position
        myFood->getFoodPos(foodpos); // get the new position 
        disp[foodpos.y][foodpos.x] = foodpos.symbol; // display that new position
        
    }
    for (int k = 0; k < playerBody->getSize(); k++){
        playerBody->getElement(tempBody, k);
        disp[tempBody.y][tempBody.x] = tempBody.symbol;
    }

    // Debugging inputs
    if (gmpointer->getInput() == 'h'){
        gmpointer->setWinFlag();
    }
    if (gmpointer->getInput() == 'j'){
        gmpointer->setLoseFlag();
    }

    // Win Screen
    if (gmpointer->getWinFlagStatus() == true){
        char msg[37] = "  Congratulations      you WON!     ";
        for (int i=0; i<8; i++){
            for (int j=0; j<18; j++){
                disp[i][j] = ' ';
            }
        }
        for (int i=0; i < 18; i++){
            disp[2][i] = msg[i];
            disp[4][i] = msg[i+18];
        }
    }
    // Lose Screen
    if (gmpointer->getLoseFlagStatus() == true){
        char msg[37] = "      Sorry           you LOST!     ";
        for (int i=0; i<8; i++){
            for (int j=0; j<18; j++){
                disp[i][j] = ' ';
            }
        }
        for (int i=0; i < 18; i++){
            disp[2][i] = msg[i];
            disp[4][i] = msg[i+18];
        }
    }

    if (gmpointer->getExitFlagStatus() == true){
        gmpointer->setExitTrue();
    }
    if (gmpointer->getScore() == 20){
        gmpointer->setWinFlag();
    }

    // Clear input
    gmpointer->clearInput();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();    
    MacUILib_printf("       SNAKE GAME\n");
    MacUILib_printf("  ####################\n");

    // Print the game board
    for (int i = 0; i < 8; i++) {
        MacUILib_printf("  #%s#\n", disp[i]);
    }

	MacUILib_printf("  ####################\n");
    MacUILib_printf("        SCORE: %d\n   PRESS 'ESC' TO END\n", gmpointer->getScore());
    // Add lose screen statement
    //objPos currentPos;
    //myPlayer->getPlayerPos(currentPos); //to get the players current position

    /*
    MacUILib_printf("\nThe Boardsize is %dx%d, The Player Position is (%d, %d) %c", 
                    gmpointer->getBoardSizeX(), gmpointer->getBoardSizeY(),
                    currentPos.x, currentPos.y, currentPos.symbol);
    */
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
    MacUILib_uninit();
    delete gmpointer;
    delete myPlayer;
    delete myFood; // test food item
}
