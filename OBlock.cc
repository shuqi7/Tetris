#include "OBlock.h"
#include "gameInterface.h"

void OBlock::clockwise(){
    // check heavy block;
    if (this->isHeavy){
        this->heavyDown();
    }
}

void OBlock::counterclockwise(){
    // check heavy block;
    if (this->isHeavy){
        this->heavyDown();
    }
}

OBlock::OBlock(int level, gameInterface *theInterface):Block(level, theInterface){ 
    type = 'O';
    for (int i = 0; i <=3; i++){ // place the first three cells
        if (i <= 1) {
            Coordinate coord{0,i};
            Cell * cellPtr = theInterface->getCell(coord);
            cellPtr->set(this);
            cells.emplace_back(cellPtr);
        } else {
            Coordinate coord{1,(i-2)};
            Cell * cellPtr = theInterface->getCell(coord);
            cellPtr->set(this);
            cells.emplace_back(cellPtr);
        }
    }
}


OBlock::~OBlock(){
    theInterface->addScore((this->level+1)*(this->level+1));
};
