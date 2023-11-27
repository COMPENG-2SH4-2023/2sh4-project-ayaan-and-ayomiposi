#include "objPosArrayList.h"
#include "objPos.h"

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP]; //200 elements on the heap
    arrayCapacity = ARRAY_MAX_CAP;
    listSize = 0; //list is empty when starting
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList; //delete entire array 
}

int objPosArrayList::getSize()
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if (listSize == arrayCapacity){
       // full list
       //cout << "[WARNING] List is Full, No Insertion Allowed." << endl;
       return;
    } 
    else{
    for(int i = listSize; i >0; i--)
        {
            aList[i].setObjPos(aList[i-1]);     
        }
    aList[0].setObjPos(thisPos);
    listSize++;
    }   
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if (listSize == arrayCapacity){
       //cout << "[WARNING] List is Full, No Insertion Allowed." << endl;
       return;  
    } 
    else{
        //aList[listSize++].setObjPos(thisPos);
        aList[listSize++] = thisPos;
    }
}

void objPosArrayList::removeHead()
{
    if (listSize <= 0){
        //cout << "[WARNING] List is Empty, No Insertion Allowed." << endl;
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
    if (listSize == 0 ){
        //cout << "[WARNING] List is Empty, No Insertion Allowed." << endl;
       return;
    } 
    else {
    listSize--; }
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[0]);
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[listSize-1]);
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    if(listSize == 0 || index < 0 || index >= listSize){
        //cout << "[WARNING] Index Out of Bound, No Element Retrieval Allowed." << endl;
        return;
    }
    returnPos.setObjPos(aList[index]);
}