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
int hasrun = 0; // Check if start conditions have run

GameMechs* gmpointer; // Pointing to mechanics of the game
Player* myPlayer; // Pointing to the player data
Food* myFood; // Pointing to the food data


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

    //creating space on the heap for game mechanics, food and the player. 
    gmpointer = new GameMechs(18,8);
    myFood = new Food(gmpointer);
    myPlayer = new Player(gmpointer, myFood);
}

void GetInput(void)
{
   gmpointer->getInput();
}

void RunLogic(void)
{
    objPos foodpos;
    objPosArrayList* foodbucketlist = myFood->getFoodPos();
    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    
    // Clear start screen and generate first food
    if (hasrun == 0 && gmpointer->getStartFlagStatus() == true){
        for (int i = 1; i < 16; i++){
            disp[1][i] = ' ';
        }
        
        myFood->generateFood(playerBody); // Generate new positions for food items
        for (int k = 0; k < foodbucketlist->getSize(); k++){
            foodbucketlist->getElement(foodpos, k);
            disp[foodpos.y][foodpos.x] = foodpos.symbol; // Display all food items on the board
        }
        
        hasrun = 1; // Start screen has run
    }

    // Clear previous player position
    objPos tempBody;
    for (int k = 0; k < playerBody->getSize(); k++){
        playerBody->getElement(tempBody, k);
        disp[tempBody.y][tempBody.x] = ' ';
    }

    // Update player position
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();

    // Interact with food
    int foodcon = myPlayer->checkFoodConsuption();
    if (foodcon == 1 || foodcon == 2){
        for (int k = 0; k < foodbucketlist->getSize(); k++){
            foodbucketlist->getElement(foodpos, k);
            disp[foodpos.y][foodpos.x] = ' '; // Clear old food positions
        }
        myFood->generateFood(playerBody); // Generate new positions for food items
        for (int k = 0; k < foodbucketlist->getSize(); k++){
            foodbucketlist->getElement(foodpos, k);
            disp[foodpos.y][foodpos.x] = foodpos.symbol; // Display all food items on the board
        }
        if (foodcon == 1){
            // Normal food conditions
            gmpointer->incrementScore(1);
            myPlayer->increasePlayerLength(1);
        } else {
            // Special food conditions
            gmpointer->incrementScore(3);
            myPlayer->increasePlayerLength(5);
        }
        
    }

    // Display new player position
    for (int k = 0; k < playerBody->getSize(); k++){
        playerBody->getElement(tempBody, k);
        disp[tempBody.y][tempBody.x] = tempBody.symbol;
    }

    // Debugging inputs
    // Input h sets to win state
    if (gmpointer->getInput() == 'h'){
        gmpointer->setWinFlag();
    }
    // Input j sets to lose state
    if (gmpointer->getInput() == 'j'){
        gmpointer->setLoseFlag();
    }

    // Win Screen
    if ((gmpointer->getWinFlagStatus() == true)){
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
    if ((gmpointer->getLoseFlagStatus() == true)){
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

    // Game end condition:  if exit flag is true, end game. 
    if ((gmpointer->getExitFlagStatus() == true)){
        gmpointer->setExitTrue();
    }
    
    // Game end condition: if you score 2000, you win (purposely unreachable)
    if (gmpointer->getScore() == 2000){ 
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
    delete myFood; 
}
