#include "objPosArrayList.h"
#include "objPos.h"

objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP]; // 256 elements on the heap
    arrayCapacity = ARRAY_MAX_CAP;
    listSize = 0; // List is empty when starting
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList; // Delete entire array 
}

int objPosArrayList::getSize()
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    // Space is full, nothing can be added
    if (listSize == arrayCapacity){
       return;
    } 
    else{
    // There is room in the array, add head
    for(int i = listSize; i >0; i--)
        {
            aList[i].setObjPos(aList[i-1]);     
        }
    aList[0].setObjPos(thisPos);
    // Increase size since 1 segment added
    listSize++;
    }   
}

void objPosArrayList::insertTail(objPos thisPos)
{
    // Insert tail if there is room in the max array.
    if (listSize == arrayCapacity){
       return;  
    } 
    else{
        aList[listSize++] = thisPos;
    }
}

void objPosArrayList::removeHead()
{
    // Remove first item as long as it exists.
    if (listSize <= 0){
       return;
    }
    else {
        for(int i = 0; i<listSize-1; i++){
                aList[i] = aList[i+1];
            }
        listSize--;
    }
}

void objPosArrayList::removeTail()
{
    // Remove last segment (tail) and decrease list size by 1. 
    if (listSize == 0 ){
       return;
    } 
    else {
    listSize--; }
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[0]); // Get 1st segment
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[listSize-1]); // Get last element
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    // Return specific element in list
    if(listSize == 0 || index < 0 || index >= listSize){
        return;
    }
    returnPos.setObjPos(aList[index]);
}