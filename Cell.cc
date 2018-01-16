#include "Cell.h"
#include "Block.h"

void Cell::set(Block *aBlock){
    this->parentBlock = aBlock;
    this->notifyObservers();
}



void Cell::unset(){
    if (this->parentBlock != nullptr){
        this->parentBlock->minusNumCells();
        if (this->parentBlock->getNumCells() == 0){
            delete this->parentBlock;
        }
        this->parentBlock = nullptr;
    }
    this->notifyObservers();
}


Coordinate Cell::getCoord(){
    Coordinate toReturn{this->r, this->c};
    return toReturn;
}


Block *Cell::getParent() {
    return this->parentBlock;
}



Cell::Cell(int r, int c):r(r),c(c){
    parentBlock = nullptr;
}

Cell::~Cell(){ // useful when restart, observers must be notified of the change
   if (this->parentBlock != nullptr){
        this->parentBlock->minusNumCells();
        if (this->getParent()->getNumCells() == 0){
            delete this->parentBlock;
            this->parentBlock = nullptr;
        }
    }
}
