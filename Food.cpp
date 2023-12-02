#include "Food.h"

Food::Food(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    foodBucket = new objPosArrayList(); // Creating space on the heap
    objPos tempFood;

    // Insert 5 default food items in array list
    tempFood.setObjPos(0, 0, 'o');
    foodBucket->insertHead(tempFood);
    foodBucket->insertTail(tempFood);
    foodBucket->insertTail(tempFood);
    foodBucket->insertTail(tempFood);
    foodBucket->insertTail(tempFood);
}

Food::~Food()
{
    delete foodBucket;
}

void Food::generateFood(objPosArrayList* blockOff) // changed this
{
    srand(time(NULL)); // Seeding with time to randomize intial food position
    int xrand, yrand;
    bool matchflag = false;
    bool unique;
    objPos tempBody; // Temporary object to hold current player body
    objPos tempFood; // Temporary object to hold current food item
    objPos foodComp; // Temporary object to compare food position


    // Check if there is valid space for displaying 5 food items
    // If not 5 spots are not available: create max possible food items
    int available = ((mainGameMechsRef->getBoardSizeX())*(mainGameMechsRef->getBoardSizeY())) - (blockOff->getSize());
    if (available < 5){
        tempFood.setObjPos(0, 0, 'o');
        for (int i = 0; i < 5; i++){
            foodBucket->removeTail();
        }
        for (int i = 0; i < available; i++){
            foodBucket->insertHead(tempFood);
        }
    }
    
    // For each food item in bucket, get and set valid random coordinates
    for (int i = 0; i < foodBucket->getSize(); i++){
        foodBucket->getElement(tempFood, i);
        while (true){
            unique = true;
            xrand = rand() % (mainGameMechsRef->getBoardSizeX()); // Get random number excluding border in x axis
            yrand = rand() % (mainGameMechsRef->getBoardSizeY()); // Get random number excluding border in y axis
            // Check if coodinates are valid compared to player body
            for (int k = 0; k < blockOff->getSize(); k++){
                blockOff->getElement(tempBody, k);
                if ((tempBody.x == xrand)&&(tempBody.y == yrand)){
                    unique = false;
                    break;
                }
            }
            // Check if coordinates are valid compared to the other food items
            for (int k = 0; k < i; k++){
                foodBucket->getElement(foodComp, k);
                if ((foodComp.x == xrand)&&(foodComp.y == yrand)){
                    unique = false;
                    break;
                }
            }
            // If passes the above checks, set temporary object to these new coordinates
            if (unique == true){
                tempFood.x = xrand;
                tempFood.y = yrand;
                // Set two items to special food characters
                if (i == 0 || i == 1)
                    tempFood.symbol = '$';
                break;
            }
        }
        // Add the temporary food item to the item list and remove the refrence item
        foodBucket->insertHead(tempFood);
        foodBucket->removeTail();
    }
}

objPosArrayList* Food::getFoodPos()
{
    // return the reference to the foodBucket array list
    return foodBucket;
}